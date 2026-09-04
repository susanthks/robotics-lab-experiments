# Experiment 6: Networking with Arduino using Bluetooth Low Energy (BLE)

## Aim

To interface an Arduino with a Bluetooth Low Energy (BLE) module and establish wireless communication with a smartphone for transmitting and receiving data.

---


# Apparatus Required

| Sl. No. | Component | Quantity |
|---------|-----------|----------|
| 1 | Arduino Uno | 1 |
| 2 | HM-10 BLE Module *(or compatible BLE module)* | 1 |
| 3 | Breadboard | 1 |
| 4 | Jumper Wires | As Required |
| 5 | USB Cable | 1 |
| 6 | Smartphone (Android/iOS) | 1 |
| 7 | BLE Terminal Application | 1 |
| 8 | Computer with Arduino IDE | 1 |

---

# Theory

**Bluetooth Low Energy (BLE)** is a wireless communication technology designed for low-power and short-range data exchange. It is widely used in Internet of Things (IoT), wearable devices, healthcare systems, industrial automation, and robotics.

Unlike classic Bluetooth, BLE consumes significantly less power while maintaining reliable communication.

In this experiment, the Arduino communicates with an HM-10 BLE module through UART (Serial Communication). A smartphone running a BLE terminal application sends commands to the Arduino and receives responses wirelessly.

The communication flow is shown below:

```
Smartphone
      │
 Bluetooth Low Energy
      │
      ▼
 HM-10 BLE Module
      │
 UART Communication
      │
      ▼
 Arduino Uno
```

The BLE module acts as a bridge between the smartphone and the Arduino.

---

# Components Used

| Component | Description |
|-----------|-------------|
| Arduino Uno | Main microcontroller |
| HM-10 BLE Module | Wireless communication module |
| Smartphone | Sends and receives BLE data |
| Jumper Wires | Electrical connections |
| Breadboard | Prototype circuit |

---

# Figure 1

**Bluetooth Low Energy Communication System**

<img width="1200" height="630" alt="image" src="https://github.com/user-attachments/assets/f40a717d-9579-40a3-8b7e-3d9e16f6c641" />


---

# Working Principle

The Arduino continuously listens for incoming serial data from the BLE module.

When a command is sent from the smartphone:

1. The smartphone transmits data via BLE.
2. The HM-10 receives the data.
3. The HM-10 forwards the data to the Arduino through UART.
4. The Arduino processes the received command.
5. The Arduino can transmit data back to the smartphone through the BLE module.

---

# Circuit Diagram

## Figure 2

**Arduino Uno – HM-10 BLE Module Connection**

<img width="1500" height="1267" alt="image" src="https://github.com/user-attachments/assets/24ff38a3-28e4-4469-9bf3-15814d3a1354" />


---

# Circuit Connections

| Arduino Uno | HM-10 BLE Module |
|--------------|------------------|
| 5V | VCC |
| GND | GND |
| D2 (RX) | TXD |
| D3 (TX) | RXD *(Use voltage divider if required)* |

> **Note:** Some BLE modules operate at **3.3V logic levels**. Ensure the module specifications are checked before connecting the TX pin directly.

---

# Arduino Program

```cpp
#include <SoftwareSerial.h>

SoftwareSerial BLE(2, 3);   // RX, TX

void setup() {

  Serial.begin(9600);
  BLE.begin(9600);

  Serial.println("BLE Communication Started");
}

void loop() {

  // Receive from Smartphone
  if (BLE.available()) {
    char data = BLE.read();
    Serial.print("Received: ");
    Serial.println(data);

    // Send acknowledgement
    BLE.print("Received: ");
    BLE.println(data);
  }

  // Send from Serial Monitor
  if (Serial.available()) {
    BLE.write(Serial.read());
  }
}
```

---

# Procedure

1. Connect the BLE module to the Arduino.
2. Verify all wiring connections.
3. Open the Arduino IDE.
4. Upload the program to the Arduino.
5. Install a BLE Terminal application on the smartphone.
6. Enable Bluetooth on the smartphone.
7. Scan for nearby BLE devices.
8. Connect to the HM-10 BLE module.
9. Send characters or text from the smartphone.
10. Observe the received data in the Arduino Serial Monitor.
11. Send data from the Serial Monitor and observe it on the smartphone.

---

# Observation

| Test | Observation |
|------|-------------|
| BLE Device Detected | ✔ |
| Connection Established | ✔ |
| Data Sent from Smartphone | ✔ |
| Data Received by Arduino | ✔ |
| Arduino Response Received | ✔ |

---

# Result

Wireless communication between the Arduino Uno and the smartphone was successfully established using Bluetooth Low Energy (BLE). Data transmission and reception were verified successfully.

---

# Conclusion

In this experiment, Bluetooth Low Energy (BLE) communication was successfully established between an Arduino Uno and a smartphone using an HM-10 BLE module. The Arduino received commands from the smartphone and transmitted responses wirelessly. This experiment demonstrates the fundamentals of BLE-based wireless networking and serves as the foundation for developing IoT devices, wireless robotic control systems, smart home automation, and remote monitoring applications.

---

# Applications

- Mobile robot control
- IoT devices
- Smart home automation
- Wireless sensor networks
- Healthcare monitoring
- Industrial automation
- Home security systems
- Remote data acquisition

---

# Precautions

- Verify the BLE module operating voltage before connecting.
- Ensure common ground between Arduino and BLE module.
- Upload the program before making final BLE connections if serial conflicts occur.
- Keep the BLE module within its communication range.
- Pair only with trusted devices.
- Disconnect power before changing wiring.

---

# Viva Questions

1. What is Bluetooth Low Energy (BLE)?
2. How is BLE different from Classic Bluetooth?
3. Why is BLE preferred in IoT applications?
4. What is the function of the HM-10 module?
5. Which communication protocol is used between Arduino and the HM-10?
6. Why is SoftwareSerial used in this experiment?
7. What is the default baud rate of the HM-10 module?
8. Why should some BLE modules use a voltage divider on the RX pin?
9. Mention four applications of BLE.
10. What is the communication range of BLE?
11. What is the difference between BLE Peripheral and Central devices?
12. How can this experiment be extended to control a mobile robot?

---

