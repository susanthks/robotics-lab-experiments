# Experiment 1: Familiarisation of Arduino IDE and Arduino I/O Interfacing (LED, LCD and Serial Monitor)

## Aim

To familiarize students with the Arduino IDE and perform basic input/output interfacing using an LED, a 16×2 I2C LCD display, and the Serial Monitor.

---

# Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| LED | 1 |
| 220Ω Resistor | 1 |
| 16×2 LCD Display | 1 |
| I2C Module | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |

---

# Software Required

- Arduino IDE (Latest Version)
- LiquidCrystal_I2C Library
- Wire Library

---

# Theory

## Arduino UNO

The Arduino UNO is an open-source microcontroller development board based on the **ATmega328P** microcontroller.

### Features

- ATmega328P MCU
- Operating Voltage: **5V**
- 14 Digital Input/Output Pins
- 6 Analog Input Pins
- 6 PWM Output Pins
- USB Programming Interface
- UART, SPI and I2C Communication Support

---

## Arduino IDE

The Arduino Integrated Development Environment (IDE) is used for:

- Writing Arduino sketches
- Compiling programs
- Uploading code to Arduino boards
- Serial communication
- Debugging Arduino programs

---

## LED Interfacing

An LED (Light Emitting Diode) is a semiconductor device that emits light when electric current passes through it.

### Applications

- Status indication
- Fault indication
- Power indication
- Debugging embedded systems

### Figure 1: LED Connection

<img width="800" height="600" alt="Screenshot from 2026-07-02 19-55-52" src="https://github.com/user-attachments/assets/47441330-76f5-4720-bfb3-3544b30b055d" />


---

## LCD Display (I2C)

A **16×2 LCD Display** is capable of displaying:

- Characters
- Sensor values
- Messages
- System status
- Menu options

Using an **I2C module** reduces the number of Arduino pins required from six to only two communication lines (SDA and SCL).

### Figure 2: 16×2 LCD with I2C Module

<img width="500" height="400" alt="image" src="https://github.com/user-attachments/assets/5bdda1a9-514d-4fcd-a465-6faeeaac14db" />


---

## Serial Monitor

The Serial Monitor is a built-in debugging tool available in the Arduino IDE.

### Applications

- Debugging programs
- Displaying sensor values
- Monitoring program execution
- Sending commands to Arduino

---

# Circuit Connections

## LED Connection

| Arduino UNO | Component |
|--------------|-----------|
| D13 | 220Ω Resistor |
| Resistor | LED Anode (+) |
| LED Cathode (-) | GND |

---

## LCD Connection (I2C)

| LCD Pin | Arduino UNO |
|----------|-------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

### Figure 3: Complete Circuit Diagram

<img width="600" height="400" alt="Screenshot from 2026-07-02 20-14-40" src="https://github.com/user-attachments/assets/f19d3a4a-8a30-4090-8774-bca22adb6b5c" />


---

# Arduino Program

Save the Arduino sketch inside:

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
  
  lcd.print("Robotics Lab");
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

# Working Principle

1. Arduino initializes the Serial Monitor.
2. The I2C LCD is initialized.
3. The LCD displays **Robotics Lab**.
4. The LED connected to digital pin **D13** turns ON.
5. The Serial Monitor displays **LED ON**.
6. After one second, the LED turns OFF.
7. The Serial Monitor displays **LED OFF**.
8. Steps 4–7 repeat continuously.

---

# Procedure

1. Install the Arduino IDE.
2. Connect the Arduino UNO to the computer using a USB cable.
3. Select **Tools → Board → Arduino UNO**.
4. Select the correct COM Port.
5. Assemble the LED and LCD circuit as shown in the circuit diagram.
6. Open the Arduino sketch.
7. Verify (compile) the program.
8. Upload the program to the Arduino UNO.
9. Open the Serial Monitor.
10. Observe the LCD display and LED blinking.

---

# Expected Output

## LCD Display

```text
Robotics Lab
```

---

## Serial Monitor

```text
Experiment 1 Started

LED ON

LED OFF

LED ON

LED OFF

...
```

---

## LED Output

The LED continuously blinks with a delay of one second between ON and OFF states.

---

# Observations

| Sl. No. | Observation | Result |
|----------|-------------|--------|
| 1 | Arduino IDE Installed | Successful |
| 2 | Program Compilation | Successful |
| 3 | Program Upload | Successful |
| 4 | LCD Display | Robotics Lab |
| 5 | Serial Monitor Output | LED ON / LED OFF |
| 6 | LED Operation | Blinking |

---

# Result

The Arduino IDE was successfully used to develop, compile, and upload an Arduino program. Basic input/output interfacing using an LED, an I2C LCD display, and the Serial Monitor was successfully demonstrated.

---

# Conclusion

This experiment introduced the Arduino development environment and demonstrated basic input/output interfacing using an LED, a 16×2 I2C LCD display, and the Serial Monitor. It provides a strong foundation for future embedded systems, robotics, and IoT laboratory experiments.

---

# Precautions

- Verify all wiring before powering the circuit.
- Always use a **220Ω current-limiting resistor** with the LED.
- Ensure the correct I2C address (**0x27** or **0x3F**) is used.
- Select the correct Arduino board and COM Port before uploading.
- Ensure all jumper wire connections are secure.
- Avoid short circuits while assembling the circuit.

---

# Applications

- Robotics
- Embedded Systems
- Industrial Automation
- Sensor Monitoring Systems
- Internet of Things (IoT)
- Smart Home Applications

---

# Viva Questions

1. What is Arduino UNO?
2. Which microcontroller is used in Arduino UNO?
3. What is the function of the Arduino IDE?
4. Why is a resistor connected in series with an LED?
5. What is the purpose of the Serial Monitor?
6. What is UART communication?
7. What communication protocols are supported by Arduino UNO?
8. What is I2C communication?
9. Why is an I2C module used with a 16×2 LCD display?
10. What is the operating voltage of Arduino UNO?
11. How many digital input/output pins are available on Arduino UNO?
12. What is PWM?
13. What is the purpose of `pinMode()`?
14. What is the function of `Serial.begin(9600)`?
15. What is the difference between `digitalWrite()` and `analogWrite()`?

---
