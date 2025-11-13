# Arduino-Based Mechatronic Control & Instrumentation Toolkit

Designed and developed a comprehensive toolkit of microcontroller-based systems to demonstrate the interfacing, control, and integration of diverse sensors, actuators, and displays — forming a practical foundation for mechatronic experimentation and real-world automation prototypes.

![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-00979D?logo=arduino&logoColor=white)

## 🎯 Core Objective

To build hands-on expertise in bridging digital control (Arduino microcontroller) with physical systems (sensors and actuators) using standard electronic interfaces, C++ programming, and circuit design.

## 🧰 Toolkit Modules

This repository is a collection of distinct mechatronic projects, each demonstrating a key component or integrated system.

### 1. Sensor Integration (Input)

* **Analog Sensors:**
    * [cite_start]**LM35 Temperature Sensor:** Measures ambient temperature by reading a linear analog voltage[cite: 1765, 1787].
    * [cite_start]**Light Dependent Resistor (LDR):** Measures light intensity using a voltage divider circuit[cite: 1765, 1778].
    * [cite_start]**Potentiometer:** Provides a variable analog input for user control (e.g., setting motor speed)[cite: 1015, 1031].

* **Digital & Event Sensors:**
    * **Push Button:** Detects user input for event-driven logic (e.g., counting, changing motor direction).
    * [cite_start]**CNY70 IR Proximity Sensor:** Detects the presence of a reflective object [cite: 914, 1925, 1929-1930].
    * **HC-SR04 Ultrasonic Sensor:** Measures distance by timing an ultrasonic pulse (`trigger`/`echo`).
    * **PIR Motion Sensors:** Detects motion in the environment (used in `Experiment 7.ino`).

* **Advanced Sensors (I2C / SPI):**
    * **ADXL345 Accelerometer:** Measures 3-axis acceleration and detects "jolts" via I2C (`Wire.h`).
    * **RC522 RFID Reader:** Reads unique identifiers from RFID cards via SPI (`RFID.h`).

### 2. Actuator Control (Output)

* **DC Motor Control (L293D):**
    * [cite_start]Implements bidirectional (Clockwise/Counter-Clockwise) control of a DC motor using an L293D H-Bridge driver[cite: 1015, 1035, 3057].
    * [cite_start]Uses Pulse Width Modulation (PWM) (`analogWrite`) to achieve variable speed control based on potentiometer input[cite: 1033, 1689].

* **Stepper Motor Control (ULN2003):**
    * Drives a 28BYJ-48 unipolar stepper motor for precise angular control.
    * [cite_start]Uses a ULN2003 Darlington Array to provide sufficient current to the motor coils [cite: 914, 1925, 1956-1957, 3035].
    * Leverages the `AccelStepper` library for smooth acceleration and position-based commands.

* **LED & Audio Output:**
    * Drives single and multiple LEDs for status indication and user feedback (e.g., a "reaction game" in `Experiment 6.ino`).
    * Generates audible frequencies for alerts using the `toneAC` library.

> **[Image: Schematic of DC Motor control with L293D driver]**
>
> *(**Developer Note:** Place your schematic from `Experiment 3.pdf` here.)*

### 3. Data Display (Feedback)

* **7-Segment Display:**
    * Manages a common-cathode 7-segment display to show numeric output.
    * [cite_start]`Experiment 1` implements a 0-9 counter based on push-button presses [cite: 3071, 3088-3090, 3292].

* **16x2 LCD Display:**
    * [cite_start]Uses the `LiquidCrystal` library to display real-time sensor data (temperature, light level) and system status (motor direction, speed) [cite: 898-902, 1765, 1769].

> **[Image: Schematic of Stepper Motor control with ULN2003 driver]**
>
> [cite_start]*(**Developer Note:** Place your schematic from `Experiment 4.pdf` here.)*

### 4. Integrated Systems

Several experiments combine these modules into a complete system:

* [cite_start]**Motor Feedback System (Exp. 3):** Links a potentiometer (input) and a push button (input) to a DC motor (output), displaying the live speed and direction on an LCD (feedback)[cite: 1015, 1638].
* [cite_start]**Sensor-Triggered Actuator (Exp. 4):** A closed-loop system where an IR sensor (input) detecting an object triggers a stepper motor (output) to perform a full rotation and return [cite: 914, 1925, 1963-1964].
* **Serial-Controlled Robot (Exp. 8):** A prototype robot base that takes commands via Serial monitor to control a DC motor and stepper motor, while using an ultrasonic sensor as an emergency brake.

---

## 🛠️ Technology Stack

### Hardware & Components
* **Microcontroller:** Arduino Uno
* **Driver ICs:** L293D H-Bridge, ULN2003 Darlington Array
* **Actuators:** DC Motor, 28BYJ-48 Unipolar Stepper Motor, LEDs
* **Displays:** 16x2 LCD, 7-Segment Display (Common Cathode)
* **Sensors:** LM35, LDR, Potentiometers, CNY70 IR, HC-SR04 Ultrasonic, ADXL345, RC522 RFID, PIR, Push Buttons

### Software & Libraries
* Arduino C/C++
* `LiquidCrystal.h` (for LCD)
* `AccelStepper.h` (for stepper motor)
* `RFID.h` & `SPI.h` (for RFID reader)
* `Wire.h` (for I2C communication)
* `toneAC.h` (for audio)