# Experiment 3: Interfacing DC Motors with Arduino UNO Speed and Direction Control

## Aim

To interface a **DC motor** with the **Arduino UNO** using the **L298N Motor Driver Module** and control its **speed** using Pulse Width Modulation (PWM) and **direction** using digital output pins.

---

# Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| L298N Motor Driver Module | 1 |
| DC Motor (6V–12V) | 1 |
| External Power Supply (9V/12V Battery or Adapter) | 1 |
| Jumper Wires | As required |
| USB Cable | 1 |

---

# Software Required

- Arduino IDE (Latest Version)

---

# Theory

## Arduino UNO

The Arduino UNO is an open-source microcontroller development board based on the **ATmega328P** microcontroller. It can generate PWM signals and digital outputs, making it suitable for controlling DC motors through a motor driver.

### Features

- ATmega328P Microcontroller
- Operating Voltage: **5V**
- 14 Digital I/O Pins
- 6 Analog Input Pins
- 6 PWM Output Pins
- USB Programming Interface
- UART, SPI and I2C Communication

---

## DC Motor

A DC (Direct Current) motor converts electrical energy into mechanical rotational motion. The direction of rotation depends on the polarity of the applied voltage, while the speed depends on the applied voltage or PWM signal.

### Applications

- Mobile robots
- Conveyor systems
- Robotic arms
- Automatic doors
- Electric vehicles
- Industrial automation

---

### Figure 1: DC Motor

<img width="204" height="192" alt="image" src="https://github.com/user-attachments/assets/0fb8c9f9-09a0-49f9-9fcf-e60b3f4fad6c" />


---

## L298N Motor Driver Module

The **L298N** is a dual H-Bridge motor driver capable of driving two DC motors independently. Since an Arduino pin cannot supply sufficient current to drive a motor directly, a motor driver is required.

### Features

- Dual H-Bridge Driver
- Operating Voltage: 5V–35V
- Motor Current up to 2A (Peak)
- PWM Speed Control
- Bidirectional Motor Control
- Overheating Protection

---

### Figure 2: L298N Motor Driver Module

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/365e5c39-7719-419b-8429-a34bd17d98c8" />


---

## PWM (Pulse Width Modulation)

PWM controls the average voltage supplied to the motor by rapidly switching the output ON and OFF.

- PWM Value = **0** → Motor OFF
- PWM Value = **255** → Maximum Speed
- Intermediate values produce proportional motor speeds.

---

## Direction Control

The direction of the motor depends on the logic applied to the IN1 and IN2 pins.

| IN1 | IN2 | Motor Direction |
|-----|-----|-----------------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop |
| HIGH | HIGH | Brake |

---

# Circuit Connections

## Arduino UNO to L298N

| Arduino UNO | L298N Module |
|--------------|--------------|
| D9 (PWM) | ENA |
| D8 | IN1 |
| D7 | IN2 |
| GND | GND |

---

## Motor Connections

| L298N | Component |
|--------|-----------|
| OUT1 | DC Motor Terminal 1 |
| OUT2 | DC Motor Terminal 2 |

---

## Power Connections

| Power Supply | L298N |
|---------------|-------|
| +9V / +12V | +12V |
| GND | GND |

> **Note:** Connect the Arduino GND and L298N GND together to establish a common ground.

---

### Figure 3: Complete Circuit Diagram

<img width="1512" height="1998" alt="image" src="https://github.com/user-attachments/assets/252199ce-88cf-4576-9be6-4a0ae43efc95" />


---

# Arduino Program

Save the Arduino sketch inside:

```text
code/Experiment3.ino
```

---

# Arduino Program

```cpp
const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // Forward Direction
  Serial.println("Motor Forward");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  for(int speed = 0; speed <= 255; speed += 25)
  {
    analogWrite(ENA, speed);
    Serial.print("Speed : ");
    Serial.println(speed);
    delay(500);
  }

  delay(2000);

  // Stop Motor
  analogWrite(ENA, 0);
  delay(1000);

  // Reverse Direction
  Serial.println("Motor Reverse");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  for(int speed = 0; speed <= 255; speed += 25)
  {
    analogWrite(ENA, speed);
    Serial.print("Speed : ");
    Serial.println(speed);
    delay(500);
  }

  delay(2000);

  analogWrite(ENA, 0);
  delay(2000);
}
```

---

# Working Principle

1. Arduino initializes the motor driver pins.
2. The L298N driver receives control signals from the Arduino.
3. The ENA pin receives a PWM signal to control motor speed.
4. IN1 and IN2 determine the direction of motor rotation.
5. The motor first rotates in the forward direction with gradually increasing speed.
6. The motor stops.
7. The motor rotates in the reverse direction with gradually increasing speed.
8. Motor status and speed values are displayed on the Serial Monitor.

---

# Procedure

1. Open the Arduino IDE.
2. Connect the Arduino UNO to the computer.
3. Connect the L298N motor driver module to the Arduino.
4. Connect the DC motor to the L298N output terminals.
5. Connect the external power supply to the motor driver.
6. Verify all wiring connections.
7. Open the Arduino sketch.
8. Verify (compile) the program.
9. Upload the program to the Arduino UNO.
10. Open the Serial Monitor.
11. Observe the motor speed and direction changes.

---

# Expected Output

## Serial Monitor

```text
Motor Forward
Speed : 0
Speed : 25
Speed : 50
...
Speed : 255

Motor Reverse
Speed : 0
Speed : 25
...
Speed : 255
```

---

## Motor Operation

- Motor rotates in the forward direction.
- Speed gradually increases.
- Motor stops.
- Motor rotates in the reverse direction.
- Speed gradually increases again.

---

# Observations

| Sl. No. | Observation | Result |
|----------|-------------|--------|
| 1 | Program Compilation | Successful |
| 2 | Program Upload | Successful |
| 3 | Forward Rotation | Working |
| 4 | Reverse Rotation | Working |
| 5 | Speed Control using PWM | Working |
| 6 | Serial Monitor Output | Correct |

---

# Result

The DC motor was successfully interfaced with the Arduino UNO through the L298N motor driver module. The motor speed was controlled using PWM signals, and the direction of rotation was successfully changed using digital control signals.

---

# Conclusion

This experiment demonstrated the interfacing of a DC motor with the Arduino UNO using the L298N motor driver. Students learned how to control motor speed using PWM and motor direction using digital outputs, providing the foundation for developing mobile robots, robotic arms, and automation systems.

---

# Precautions

- Never connect a DC motor directly to an Arduino pin.
- Always use a motor driver to drive the motor.
- Use an external power supply for the motor.
- Connect Arduino GND and motor driver GND together.
- Verify all wiring before powering the circuit.
- Avoid short circuits.
- Do not exceed the rated voltage of the motor.

---

# Applications

- Mobile Robots
- Robotic Arms
- Automatic Doors
- Conveyor Belt Systems
- Smart Wheelchairs
- Electric Vehicles
- Industrial Automation
- Warehouse Robots

---

# Viva Questions

1. What is a DC motor?
2. Why is a motor driver required?
3. What is the function of the L298N motor driver?
4. What is an H-Bridge?
5. What is PWM?
6. Which Arduino pins support PWM?
7. How is motor speed controlled?
8. How is motor direction changed?
9. What is the function of the ENA pin?
10. What are the functions of IN1 and IN2?
11. Why is an external power supply used?
12. Why should the Arduino and motor driver share a common ground?
13. What happens when PWM value is 0?
14. What happens when PWM value is 255?
15. Name two applications of DC motor speed and direction control.

---

