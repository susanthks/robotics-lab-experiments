# Experiment 4: Interfacing Servo Motor with Arduino – Angle of Rotation Control

## Aim

To interface a Servo Motor and a 10kΩ Potentiometer with an Arduino UNO and control the angular position of the servo motor based on the potentiometer input.

---

# Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| SG90 Servo Motor | 1 |
| 10kΩ Potentiometer | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |
| USB Cable | 1 |

# Software Required

- Arduino IDE (Latest Version)
- Servo Library (Built-in Arduino Library)

---

# Theory

## Servo Motor

A **Servo Motor** is an electromechanical actuator designed to provide precise angular position control. Unlike a DC motor, which rotates continuously, a standard hobby servo rotates only to a specified angle, typically between **0° and 180°**.

Servo motors are widely used in robotics, automation, and embedded systems where accurate position control is required.

### Features

- Operating Voltage: **4.8V – 6V**
- Rotation Range: **0° to 180°**
- Built-in Position Feedback
- High Position Accuracy
- PWM Controlled

---

## Working Principle

A servo motor contains:

- DC Motor
- Gear Mechanism
- Position Sensor (Potentiometer)
- Control Circuit

The Arduino generates a **Pulse Width Modulation (PWM)** signal. Based on the pulse width received, the internal control circuit rotates the motor shaft to the desired angle and maintains its position using feedback from the potentiometer.

---

## Servo Motor Pin Description

| Wire Color | Function |
|------------|----------|
| Brown / Black | GND |
| Red | +5V |
| Orange / Yellow | PWM Signal |

---


## Figure 1: SG90 Servo Motor

> *(Insert image of SG90 Servo Motor here)*

---

## Figure 2: Servo Motor Internal Structure

> *(Insert labelled diagram showing DC Motor, Gearbox, Potentiometer and Control Circuit)*

---
## Potentiometer (10kΩ)

A **Potentiometer (POT)** is a three-terminal variable resistor that is commonly used to vary voltage manually. It acts as an analog input device for the Arduino. As the knob of the potentiometer is rotated, the output voltage changes from **0V to 5V**.

The Arduino reads this varying voltage using the `analogRead()` function, which returns values between **0 and 1023**. These values are then mapped to the servo motor's angular range (0°–180°), allowing the servo position to be controlled by rotating the potentiometer.

### Applications

- Servo Position Control
- Volume Control
- Brightness Adjustment
- User Input Devices
- Robotics and Automation

# Circuit Connections

## Servo Motor

| Servo Motor | Arduino UNO |
|--------------|-------------|
| Brown / Black | GND |
| Red | 5V |
| Orange / Yellow | D9 |

---

## Potentiometer

| Potentiometer Pin | Arduino UNO |
|-------------------|-------------|
| Left Terminal | 5V |
| Middle Terminal (Wiper) | A0 |
| Right Terminal | GND |

---

## Figure 3: Complete Circuit Diagram

> *(Insert circuit diagram showing Arduino UNO connected to the SG90 Servo Motor and the 10kΩ Potentiometer.)*

---

# Arduino Program
```cpp
#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int potPin = A0;

int potValue = 0;
int angle = 0;

void setup()
{
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop()
{
  potValue = analogRead(potPin);

  angle = map(potValue, 0, 1023, 0, 180);

  myServo.write(angle);

  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print("\tServo Angle: ");
  Serial.println(angle);

  delay(15);
}
```
---

# Working Principle

1. The Arduino initializes the Servo library and Serial Monitor.
2. The potentiometer provides a variable analog voltage to analog pin **A0**.
3. Arduino reads the analog value (0–1023) using `analogRead()`.
4. The `map()` function converts the analog value into an angle between **0° and 180°**.
5. Arduino generates a PWM signal on digital pin **D9**.
6. The servo motor rotates to the corresponding angle.
7. The potentiometer value and servo angle are displayed on the Serial Monitor.
8. Rotating the potentiometer changes the servo position continuously.

---

# Procedure

1. Open the Arduino IDE.
2. Connect the Arduino UNO to the computer using a USB cable.
3. Assemble the servo motor and potentiometer circuit as shown in the circuit diagram.
4. Select **Tools → Board → Arduino UNO**.
5. Select the correct COM Port.
6. Open the Arduino sketch.
7. Verify (compile) the program.
8. Upload the program to the Arduino UNO.
9. Open the Serial Monitor.
10. Rotate the potentiometer knob and observe the movement of the servo motor.

---

# Expected Output

## Servo Motor

The servo motor rotates smoothly from **0° to 180°** based on the position of the potentiometer.

---

## Serial Monitor

```text
Potentiometer: 0      Servo Angle: 0
Potentiometer: 256    Servo Angle: 45
Potentiometer: 512    Servo Angle: 90
Potentiometer: 768    Servo Angle: 135
Potentiometer: 1023   Servo Angle: 180
```

---

# Servo Position

| Angle | Servo Position |
|--------|----------------|
| 0° | Initial Position |
| 90° | Middle Position |
| 180° | Maximum Rotation |

---

# Observations

| Sl. No. | Observation | Result |
|----------|-------------|--------|
| 1 | Circuit Connections | Successful |
| 2 | Program Compilation | Successful |
| 3 | Program Upload | Successful |
| 4 | Potentiometer Reading | 0–1023 |
| 5 | Servo Rotation | 0°–180° |
| 6 | Serial Monitor Output | Successful |

---

# Result

The Servo Motor was successfully interfaced with the Arduino UNO. The angular position of the servo motor was controlled using a 10kΩ potentiometer, demonstrating analog input reading, PWM signal generation, and precise position control.

---

# Conclusion

This experiment demonstrated how an Arduino UNO can read analog input from a potentiometer and convert it into PWM signals to control the angular position of a servo motor. The experiment provides a practical understanding of analog input processing, servo motor interfacing, and position control, which are fundamental concepts in robotics and embedded systems.

---

# Precautions

- Ensure correct wiring before powering the circuit.
- Do not force the servo shaft manually.
- Use a stable 5V power supply.
- Avoid overloading the servo motor.
- Disconnect power before modifying the circuit.
- Ensure jumper wire connections are secure.

---

# Applications

- Robotic Arm Joint Control
- Pan-Tilt Camera Systems
- Robot Steering Mechanisms
- Pick and Place Robots
- CNC Machines
- Industrial Automation
- Position Control Systems
- Autonomous Mobile Robots

---

# Viva Questions

1. What is a servo motor?
2. How is a servo motor different from a DC motor?
3. What is the operating voltage of an SG90 servo motor?
4. Why is PWM used to control a servo motor?
5. What is the function of the Servo library?
6. What is the purpose of the `attach()` function?
7. What is the function of `write()`?
8. What is the typical rotation range of a hobby servo motor?
9. Which Arduino pin is used in this experiment?
10. What happens if the servo does not receive a PWM signal?
11. Name three applications of servo motors in robotics.
12. What is the purpose of the potentiometer inside a servo motor?
13. Can a standard servo rotate continuously? Explain.
14. What is the difference between a servo motor and a stepper motor?
15. Why are servo motors preferred in robotic arm applications?
16. 16. What is a potentiometer?
17. Why is the potentiometer connected to an analog pin?
18. What is the range of values returned by `analogRead()`?
19. What is the purpose of the `map()` function?
20. How does a potentiometer control the angular position of a servo motor?

---
