# Experiment 1: Familiarisation of Arduino IDE and Arduino I/O Interfacing (LED, LCD, Serial Monitor)

## Aim

To familiarize students with the Arduino IDE and basic input/output interfacing using LEDs, LCD displays, and Serial Monitor.

---

## Components Required

| Component        | Quantity    |
| ---------------- | ----------- |
| Arduino UNO      | 1           |
| LED              | 1           |
| 220Ω Resistor    | 1           |
| 16×2 LCD Display | 1           |
| I2C Module       | 1           |
| Breadboard       | 1           |
| Jumper Wires     | As Required |

---

## Theory

### Arduino UNO

Arduino UNO is a popular microcontroller development board based on the **ATmega328P** microcontroller. It provides:

* 14 Digital Input/Output Pins
* 6 Analog Input Pins
* USB Interface for Programming
* UART Serial Communication
* PWM Output Support
* Easy Integration with Sensors and Actuators

### Arduino IDE

The Arduino Integrated Development Environment (IDE) is used to:

* Write Arduino programs (Sketches)
* Compile source code
* Upload programs to Arduino boards
* Monitor serial communication through the Serial Monitor

### LED Interfacing

An LED (Light Emitting Diode) is an electronic component used as a visual indicator.
##### Figure 3: LED Circuit
<img width="725" height="453" alt="image" src="https://github.com/user-attachments/assets/ab282b65-8596-42d8-beeb-d5a092464d39" />

Applications:

* Status indication
* Fault indication
* Signal monitoring
* Debugging embedded systems

### LCD Interfacing

A 16×2 LCD Display is capable of displaying:

* Text messages
* Numerical values
* Sensor readings
* System status information

##### Figure 4: 16×2 LCD Display
<img width="750" height="750" alt="image" src="https://github.com/user-attachments/assets/3139cdf7-1c8f-4989-acf1-01bc9793f7e9" />

### Serial Monitor

The Serial Monitor is a built-in debugging tool in Arduino IDE.

Applications:

* Displaying sensor values
* Monitoring program execution
* Sending commands to Arduino
* Troubleshooting and debugging

---
## Circuit Connections

### LED Connection

| Arduino Pin | Component                             |
| ----------- | ------------------------------------- |
| D13         | LED Anode (+)                         |
| GND         | LED Cathode (-) through 220Ω resistor |

### LCD Connection (4-bit Mode)

| LCD with I2C Pin | Arduino Pin |
| ------- | ----------- |
| SDA      | A0         |
| SCL      | A1         |
| GND     | GND         |
| VCC     | 5V          |

---

## Arduino Program

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Note: Some modules use 0x3F if 0x27 does not work.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  lcd.init();          // Initialize the I2C LCD module
  lcd.backlight();     // Turn on the LCD backlight
  
  lcd.print("Arduino Lab");
  Serial.println("Experiment 1 Started");
}

void loop() {
  digitalWrite(13, HIGH);
  Serial.println("LED ON");
  delay(1000);
  
  digitalWrite(13, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

```

---

## Procedure

1. Open Arduino IDE.
2. Connect Arduino UNO to the computer using a USB cable.
3. Select the appropriate Board and COM Port.
4. Assemble the LED and LCD circuit as per the connection diagram.
5. Create a new sketch and enter the program.
6. Verify the program for syntax errors.
7. Upload the program to Arduino UNO.
8. Open the Serial Monitor.
9. Observe the LED blinking and LCD displaying the message.
10. Record the observations.

---

## Expected Output

### LCD Display

```text
Arduino Lab
```

### Serial Monitor

```text
Experiment 1 Started
LED ON
LED OFF
LED ON
LED OFF
...
```

### LED

The LED continuously blinks at an interval of 1 second.

---

## Observation

| Sl.No | Activity              | Observation         |
| ----- | --------------------- | ------------------- |
| 1     | IDE Installation      | Successful          |
| 2     | Program Compilation   | Successful          |
| 3     | Program Upload        | Successful          |
| 4     | LCD Display           | Arduino Lab         |
| 5     | Serial Monitor Output | LED ON/OFF Messages |
| 6     | LED Operation         | Blinking            |

---

## Result

The Arduino IDE was successfully familiarized, and basic input/output interfacing using an LED, LCD display, and Serial Monitor was implemented successfully.

---

## Conclusion

This experiment introduced the Arduino development environment and demonstrated basic input/output interfacing using an LED, LCD display, and Serial Monitor. The experiment provides a foundation for further embedded systems and robotics laboratory exercises.

---

## Precautions

* Ensure correct polarity of the LED.
* Use a current-limiting resistor with the LED.
* Verify all LCD connections before powering the circuit.
* Select the correct COM port in Arduino IDE.
* Avoid loose jumper wire connections.

---

## Applications

* Embedded system prototyping
* Industrial automation
* Robotics applications
* Sensor monitoring systems
* IoT device development

---

## Viva Questions

1. What is Arduino UNO?
2. Which microcontroller is used in Arduino UNO?
3. What is the purpose of Arduino IDE?
4. Why is a resistor used with an LED?
5. What is the function of the Serial Monitor?
6. What is UART communication?
7. How many digital pins are available in Arduino UNO?
8. What is the operating voltage of Arduino UNO?
9. What is the function of an LCD display?
10. What is the difference between analog and digital pins?
