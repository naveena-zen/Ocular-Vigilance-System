# Ocular Sentinel System for Pre-Incident Recognition of Transient and Critical Alertness Events

## Overview
The Ocular Sentinel System is a visor-mounted embedded safety solution designed to detect early signs of transient drowsiness, dizziness, and critical reductions in consciousness through real-time eye-blink analysis. The system operates using blink duration and eye-closure pattern metrics to identify abnormal vigilance states before potential safety incidents occur.

## Objective
To develop a compact, embedded monitoring system that performs continuous ocular state analysis and triggers autonomous alerts upon detection of abnormal blink behavior associated with pre-incident physiological conditions.

## System Description
The system is integrated into a transparent visor module positioned in front of the user’s eyes. It captures eye-blink activity and processes blink intervals, closure duration, and frequency using threshold-based computational logic.

When blink parameters exceed predefined safety thresholds, the system activates an alert mechanism for immediate user awareness.

## Core Functional Components
- Ocular sensing module (IR/optical sensor or camera-based input)
- Embedded processing unit (microcontroller-based)
- Blink duration and frequency analysis engine
- Threshold evaluation logic
- Autonomous alert activation module (buzzer/vibration)

## Working Principle
1. Continuous acquisition of eye-blink data.
2. Real-time extraction of blink duration and closure intervals.
3. Comparison of measured parameters against calibrated threshold limits.
4. Detection of transient drowsiness or abnormal ocular inactivity.
5. Immediate activation of alert output upon anomaly recognition.

## Key Features
- Real-time blink duration monitoring
- Threshold-driven anomaly detection
- Low-latency embedded execution
- Compact visor-mounted configuration
- Autonomous alert response

## Applications
- Rider safety systems
- Industrial operator monitoring
- Fatigue-sensitive task environments
- Personal alertness monitoring

## Technology Stack

### Hardware Components
- ESP32 Development Board
- IR Eye Blink Sensor
- Touch Sensor (TTP223)
- GSM Module (SIM800L)
- Buzzer
- Li-ion Rechargeable Battery
- Jumper Wires
- Breadboard / PCB

### Software Components
- Arduino IDE
- Embedded C / C++
- ESP32 Board Support Package (BSP)
- Serial Communication (UART) for GSM module

### System Approach
- Real-time eye blink detection
- Threshold-based logic for abnormal blink duration
- Automatic buzzer alert
- SMS alert via GSM module

## Future Scope
- Adaptive threshold calibration
- Machine learning-based blink pattern modeling
- Data logging and performance analytics
- Wireless notification integration

## License
This project is developed as part of a college mini project.
