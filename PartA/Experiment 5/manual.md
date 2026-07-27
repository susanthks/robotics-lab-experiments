# Experiment: Mobile Robot Assembly

## Aim

To assemble a two-wheel differential drive mobile robot using Arduino Uno, DC geared motors, motor driver, battery, and robot chassis.

---

## Apparatus Required

- Arduino Uno
- Robot Chassis
- 2 × DC Geared Motors
- 2 × Robot Wheels
- Caster Wheel
- L298N Motor Driver Module
- Battery Pack 12V
- Jumper Wires
- Nuts and Bolts
- Screwdriver Set
- USB Cable

---

## Theory

A **mobile robot** is a robot capable of moving from one location to another. In this experiment, a **two-wheel differential drive robot** is assembled.

The robot consists of:

- Robot chassis
- Two DC geared motors
- Two wheels
- One caster wheel
- Arduino Uno
- L298N motor driver
- Battery pack

The Arduino sends control signals to the motor driver, and the motor driver powers the motors. By controlling both motors independently, the robot can move in different directions.

---


## Components

| Component | Description |
|-----------|-------------|
| Arduino Uno | Main controller |
| L298N Motor Driver | Controls both DC motors |
| DC Geared Motors | Provide robot movement |
| Wheels | Robot locomotion |
| Caster Wheel | Supports the front of the robot |
| Battery Pack | Power source |
| Chassis | Base structure |

---

### Figure 1

---

## Robot Assembly

### Step 1

Fix both DC motors onto the chassis using the motor brackets.

---

### Step 2

Attach the two wheels to the motor shafts.

---

### Step 3

Fix the caster wheel at the front of the chassis.

---

### Step 4

Mount the Arduino Uno using spacers.

---

### Step 5

Mount the L298N Motor Driver on the chassis.

---

### Step 6

Fix the battery Pack securely.

---

### Step 7

Complete all wiring connections.

---

## Circuit Connections

### Arduino ↔ L298N

| Arduino | L298N |
|----------|--------|
| D5 | ENA |
| D8 | IN1 |
| D9 | IN2 |
| D10 | IN3 |
| D11 | IN4 |
| D6 | ENB |
| GND | GND |

---

### Motor Connections

| L298N | Motor |
|--------|-------|
| OUT1 | Left Motor |
| OUT2 | Left Motor |
| OUT3 | Right Motor |
| OUT4 | Right Motor |

---

### Power Connections

Battery (+) → 12V (VIN)

Battery (-) → GND

Arduino GND → L298N GND

---

## 💻 Arduino Program

```cpp
// L298N Motor Driver Connections
#define ENA 5
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENB 6

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {

  // Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3000);

  // Stop
  stopRobot();
  delay(1000);

  // Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(3000);

  stopRobot();
  delay(1000);

  // Left Turn
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  stopRobot();
  delay(1000);

  // Right Turn
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);

  stopRobot();
  delay(1000);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

```

---

## Procedure

1. Assemble the robot chassis.
2. Mount both DC motors.
3. Attach the wheels.
4. Fix the caster wheel.
5. Install the Arduino Uno.
6. Mount the L298N motor driver.
7. Connect both motors to the motor driver.
8. Connect the Arduino to the motor driver.
9. Connect the battery pack.
10. Verify all wiring connections.
11. Upload the motor testing program.
12. Observe the robot movement.

---

## Observation

| Test | Observation |
|------|-------------|
| Forward | ✔ |
| Backward | ✔ |
| Left Turn | ✔ |
| Right Turn | ✔ |
| Stop | ✔ |

---

## Result

The mobile robot was successfully assembled and tested. The robot moved correctly in all directions.

---

## Conclusion

In this experiment, a two-wheel differential drive mobile robot was successfully assembled by integrating the mechanical chassis, DC geared motors, Arduino Uno, L298N motor driver, and power supply. The assembled robot was tested and demonstrated correct forward, backward, left, and right movements. This experiment provided practical experience in robot assembly, wiring, and basic motion control, forming the foundation for future robotics applications such as line following, obstacle avoidance, and autonomous navigation.

---

## Precautions

- Switch OFF power before wiring.
- Check battery polarity.
- Tighten all screws properly.
- Ensure all GND connections are common.
- Keep wires away from the wheels.

---

## Viva Questions

1. What is a mobile robot?
2. What is a differential drive robot?
3. Why is an L298N motor driver used?
4. What is the function of the caster wheel?
5. Why is Arduino used in the robot?
6. What happens if the motor terminals are interchanged?
7. Why should all grounds be connected together?
8. What is the purpose of the chassis?
9. What are the applications of mobile robots?
10. Name two sensors that can be added to this robot.

---


