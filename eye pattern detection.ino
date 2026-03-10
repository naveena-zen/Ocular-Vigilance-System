#include <WiFi.h>
#include <HTTPClient.h>

/* ---------------- WiFi ---------------- */
const char* ssid = "Harish";
const char* password = " ";

/* -------------- Telegram -------------- */
String botToken = " ";
String chatID   = " ";   

/* ---------------- Pins ---------------- */
#define IR_SENSOR_PIN     18   // Eye sensor
#define TOUCH_SENSOR_PIN   4   // Touch sensor
#define BUZZER_PIN        19   // Buzzer

/* -------------- Timing --------------- */
#define EYE_CLOSE_TIME   10000   // 10 seconds
#define BUZZER_TIME       5000   // 5 seconds
#define TONE_INTERVAL      150   // beep interval

/* -------------- Buzzer PWM ----------- */
#define BUZZER_CHANNEL 0
#define BUZZER_FREQ    2000
#define BUZZER_RES     8

/* -------------- States --------------- */
enum State {
  MONITORING,
  EYE_CLOSED_TIMING,
  BUZZER_ACTIVE
};

State currentState = MONITORING;

/* -------------- Timers --------------- */
unsigned long eyeCloseStart = 0;
unsigned long buzzerStart   = 0;
unsigned long lastToneToggle = 0;
bool buzzerToneState = false;

/* ===================================== */

void setup() {
  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);

  /* Setup PWM for buzzer */
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  ledcWrite(BUZZER_CHANNEL, 0);   // buzzer OFF

  /* WiFi */
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  Serial.println("System ready: Monitoring eye status");
}

/* ===================================== */

void loop() {
  int eyeClosed = digitalRead(IR_SENSOR_PIN);
  int touch     = digitalRead(TOUCH_SENSOR_PIN);

  switch (currentState) {

    /* ---------- MONITORING ---------- */
    case MONITORING:
      if (eyeClosed == LOW) {   // eye closed detected
        eyeCloseStart = millis();
        currentState = EYE_CLOSED_TIMING;
        Serial.println("Eye closed detected");
      }
      break;

    /* ------ EYE CLOSED TIMING ------- */
    case EYE_CLOSED_TIMING:
      if (eyeClosed == HIGH) {  // eye reopened
        currentState = MONITORING;
        Serial.println("Eye reopened");
      }
      else if (millis() - eyeCloseStart >= EYE_CLOSE_TIME) {
        buzzerStart = millis();
        lastToneToggle = millis();
        buzzerToneState = false;
        currentState = BUZZER_ACTIVE;
        Serial.println("Eye closed 10s → Buzzer ON");
      }
      break;

    /* -------- BUZZER ACTIVE -------- */
    case BUZZER_ACTIVE:

      /* Beep-beep pattern */
      if (millis() - lastToneToggle >= TONE_INTERVAL) {
        lastToneToggle = millis();
        buzzerToneState = !buzzerToneState;

        if (buzzerToneState)
          ledcWrite(BUZZER_CHANNEL, 128); // buzzer ON
        else
          ledcWrite(BUZZER_CHANNEL, 0);   // buzzer OFF
      }

      /* Touch acknowledged */
      if (touch == HIGH) {
        ledcWrite(BUZZER_CHANNEL, 0);
        buzzerToneState = false;
        currentState = MONITORING;
        Serial.println("Touch detected → Reset");
      }

      /* No response → Telegram */
      else if (millis() - buzzerStart >= BUZZER_TIME) {
        ledcWrite(BUZZER_CHANNEL, 0);
        buzzerToneState = false;
        Serial.println("No response → Telegram alert");
        sendTelegram("ALERT eye closed");
        currentState = MONITORING;
      }
      break;
  }
}

/* ========== TELEGRAM FUNCTION ========= */

void sendTelegram(String message) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = "https://api.telegram.org/bot" + botToken + "/sendMessage";

  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String payload = "chat_id=" + chatID + "&text=" + message;

  int httpCode = http.POST(payload);

  if (httpCode == 200)
    Serial.println("Telegram alert delivered");
  else {
    Serial.print("Telegram error: ");
    Serial.println(httpCode);
  }

  http.end();
}
