# Experiment 2: Interfacing IR and Ultrasonic Sensors with Arduino UNO

## Aim

To interface an **Infrared (IR) Sensor** and an **Ultrasonic Sensor (HC-SR04)** with the Arduino UNO and observe their operation using LEDs and the Serial Monitor for object detection and distance measurement.

---

# Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| IR Obstacle Sensor | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| LED | 2 |
| 220Ω Resistors | 2 |
| Breadboard | 1 |
| Jumper Wires | As required |
| USB Cable | 1 |

---

# Software Required

- Arduino IDE (Latest Version)

---

# Theory

## Arduino UNO

The Arduino UNO is an open-source microcontroller development board based on the **ATmega328P** microcontroller. It provides digital and analog input/output pins that can be used to interface various sensors and actuators.

### Features

- ATmega328P Microcontroller
- Operating Voltage: **5V**
- 14 Digital I/O Pins
- 6 Analog Input Pins
- USB Programming Interface
- UART, SPI and I2C Communication

---

## Infrared (IR) Obstacle Sensor

An Infrared (IR) sensor detects nearby objects by transmitting infrared light and receiving the reflected signal. When an object comes within the sensing range, the sensor output changes state.

### Applications

- Obstacle detection
- Line following robots
- Automatic doors
- Robot navigation
- Industrial automation

### Working Principle

The IR sensor consists of:

- IR LED (Transmitter)
- Photodiode (Receiver)
- Comparator Circuit

When infrared light strikes an object, it is reflected back to the receiver. The comparator detects this reflected signal and changes the output accordingly.

---

### Figure 1: IR Obstacle Sensor

<img width="600" height="400" alt="image" src="https://github.com/user-attachments/assets/1a9d8f18-bb1d-47bf-aa73-1347b4495599" />


---

## Ultrasonic Sensor (HC-SR04)

The HC-SR04 measures the distance to an object using ultrasonic sound waves.

### Applications

- Distance measurement
- Obstacle avoidance robots
- Automatic parking systems
- Robot navigation
- Water level measurement

### Working Principle

The ultrasonic sensor has four pins:

- VCC
- TRIG
- ECHO
- GND

The Arduino sends a **10 µs pulse** to the TRIG pin.

The sensor transmits an ultrasonic wave (40 kHz).

After striking an object, the wave returns to the sensor.

The ECHO pin remains HIGH for the duration of the sound wave's travel.

The Arduino calculates the distance using:

```text
Distance = (Time × Speed of Sound) / 2
```

where

- Speed of Sound = **343 m/s**

---

### Figure 2: HC-SR04 Ultrasonic Sensor

<img width="600" height="400" alt="image" src="https://github.com/user-attachments/assets/4f1bfc42-2cdc-472d-9314-0394f4eda30d" />


---

## Serial Monitor

The Serial Monitor displays:

- IR sensor status
- Measured distance
- Debugging information

---

# Circuit Connections

## IR Sensor

| IR Sensor | Arduino UNO |
|------------|-------------|
| VCC | 5V |
| GND | GND |
| OUT | D2 |

---

## Ultrasonic Sensor

| HC-SR04 | Arduino UNO |
|----------|-------------|
| VCC | 5V |
| GND | GND |
| TRIG | D9 |
| ECHO | D10 |

---

## LEDs

### IR Indicator LED

| Arduino | Component |
|----------|-----------|
| D12 | 220Ω Resistor → LED Anode |
| LED Cathode | GND |

### Ultrasonic Indicator LED

| Arduino | Component |
|----------|-----------|
| D13 | 220Ω Resistor → LED Anode |
| LED Cathode | GND |

---

### Figure 3: Complete Circuit Diagram

<p align="center">
<img src="images/circuit_diagram.png" width="750">
</p>

---

# Arduino Program

Save the Arduino sketch inside:

```text
code/Experiment2.ino
```

---

# Arduino Program

```cpp
const int irPin = 2;
const int trigPin = 9;
const int echoPin = 10;

const int irLED = 12;
const int usLED = 13;

long duration;
float distance;

void setup()
{
  pinMode(irPin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(irLED, OUTPUT);
  pinMode(usLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // ---------- IR SENSOR ----------
  if (digitalRead(irPin) == LOW)
  {
    digitalWrite(irLED, HIGH);
    Serial.println("IR Sensor : Obstacle Detected");
  }
  else
  {
    digitalWrite(irLED, LOW);
    Serial.println("IR Sensor : No Obstacle");
  }

  // ---------- ULTRASONIC SENSOR ----------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.0343 / 2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 15)
      digitalWrite(usLED, HIGH);
  else
      digitalWrite(usLED, LOW);

  Serial.println("---------------------------");

  delay(1000);
}
```

---

# Working Principle

1. Arduino initializes the IR and Ultrasonic sensors.
2. The IR sensor continuously checks for nearby obstacles.
3. When an obstacle is detected, the IR LED turns ON.
4. The ultrasonic sensor measures the distance to the object.
5. If the object is closer than **15 cm**, the ultrasonic LED turns ON.
6. Sensor status and distance are displayed on the Serial Monitor.
7. The process repeats continuously.

---

# Procedure

1. Open the Arduino IDE.
2. Connect the Arduino UNO to the computer.
3. Assemble the circuit according to the circuit diagram.
4. Connect the IR sensor.
5. Connect the HC-SR04 sensor.
6. Connect both LEDs.
7. Open the Arduino sketch.
8. Verify the program.
9. Upload the program.
10. Open the Serial Monitor.
11. Bring an object near the sensors.
12. Observe the LEDs and measured distance.

---

# Expected Output

## Serial Monitor

```text
IR Sensor : No Obstacle
Distance : 48.3 cm

-----------------------

IR Sensor : Obstacle Detected
Distance : 12.8 cm

-----------------------
```

---

## IR LED

- Turns ON when an obstacle is detected.

---

## Ultrasonic LED

- Turns ON when the measured distance is less than **15 cm**.

---

# Observations

| Sl. No. | Observation | Result |
|----------|-------------|--------|
| 1 | Program Compilation | Successful |
| 2 | Program Upload | Successful |
| 3 | IR Sensor Detection | Working |
| 4 | Ultrasonic Distance Measurement | Working |
| 5 | Serial Monitor Output | Correct |
| 6 | LEDs | Working Properly |

---

# Result

The IR sensor and HC-SR04 ultrasonic sensor were successfully interfaced with the Arduino UNO. The IR sensor detected nearby obstacles, while the ultrasonic sensor accurately measured the distance to the object. The measured values and sensor status were successfully displayed on the Serial Monitor.

---

# Conclusion

This experiment demonstrated the interfacing of two commonly used robotic sensors with the Arduino UNO. Students learned the principles of obstacle detection using an IR sensor and distance measurement using an ultrasonic sensor, providing a foundation for developing autonomous robots, obstacle avoidance systems, and smart automation projects.

---

# Precautions

- Verify all sensor connections before powering the circuit.
- Connect the TRIG and ECHO pins correctly.
- Do not place obstacles too close to the ultrasonic sensor (less than 2 cm).
- Ensure proper alignment of the IR sensor.
- Select the correct Arduino board and COM port before uploading.
- Avoid loose jumper wire connections.

---

# Applications

- Obstacle Avoidance Robots
- Line Following Robots
- Automatic Parking Systems
- Water Level Measurement
- Smart Vehicles
- Robot Navigation
- Industrial Automation
- Security Systems

---

# Viva Questions

1. What is an IR sensor?
2. What is the working principle of an IR sensor?
3. What is the operating voltage of the HC-SR04 sensor?
4. Name the four pins of the HC-SR04 sensor.
5. What is the purpose of the TRIG pin?
6. What is the function of the ECHO pin?
7. What is the speed of sound used in distance calculation?
8. Why is the measured time divided by two?
9. What are the applications of ultrasonic sensors?
10. What is the sensing range of the HC-SR04?
11. What is the difference between an IR sensor and an ultrasonic sensor?
12. Which sensor is more suitable for distance measurement?
13. What is the purpose of the Serial Monitor in this experiment?
14. How can this experiment be used in robotics?
15. Name two real-world applications where both IR and ultrasonic sensors are used together.

---

# Repository Structure

```text
Experiment-2/
│
├── README.md
├── code/
│   └── Experiment2.ino
│
├── images/
│   ├── ir_sensor.png
│   ├── hcsr04.png
│   ├── circuit_diagram.png
│   ├── serial_monitor_output.png
│   └── experimental_setup.jpg
│
└── docs/
    └── Experiment2.pdf
```
