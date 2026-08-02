# Experiment 7: Familiarisation of Raspberry Pi and its I/O Interfacing

## Aim

To familiarize students with the Raspberry Pi hardware, operating system, GPIO pins, and basic input/output (I/O) interfacing by controlling an LED and reading the state of a push button using Python.

---

# Learning Outcomes

After completing this experiment, the student will be able to:

- Understand the architecture and features of the Raspberry Pi.
- Identify the Raspberry Pi GPIO pins and their functions.
- Install and use the Raspberry Pi OS.
- Interface input and output devices with GPIO.
- Write Python programs for GPIO control.
- Develop simple embedded and IoT applications using Raspberry Pi.

---

# Apparatus Required

| Sl. No. | Component | Quantity |
|---------|-----------|----------|
|1|Raspberry Pi 4 Model B (or Raspberry Pi 3)|1|
|2|MicroSD Card (16 GB or higher)|1|
|3|Power Adapter (5V, 3A)|1|
|4|Monitor with HDMI Cable|1|
|5|USB Keyboard|1|
|6|USB Mouse|1|
|7|Breadboard|1|
|8|LED|1|
|9|220 Ω Resistor|1|
|10|Push Button|1|
|11|10 kΩ Resistor|1|
|12|Jumper Wires|As Required|

---

# Theory

The **Raspberry Pi** is a low-cost, credit-card-sized single-board computer developed by the Raspberry Pi Foundation. It supports Linux-based operating systems and is widely used in embedded systems, robotics, IoT, automation, artificial intelligence, and computer vision.

Unlike Arduino, which is a microcontroller, the Raspberry Pi is a complete computer capable of multitasking, networking, multimedia processing, and executing complex applications.

The Raspberry Pi features a **40-pin GPIO (General Purpose Input/Output) header**, which allows interfacing with sensors, actuators, displays, motors, and communication modules.

In this experiment:

- An LED is connected as an output device.
- A push button is connected as an input device.
- Python is used to control the GPIO pins.

---

# Raspberry Pi Specifications

| Feature | Description |
|---------|-------------|
|Processor|Quad-Core ARM Cortex Processor|
|Operating System|Raspberry Pi OS (Linux)|
|GPIO Pins|40|
|USB Ports|2–4|
|HDMI|Micro HDMI / HDMI|
|Wi-Fi|Built-in|
|Bluetooth|Built-in|
|Ethernet|Available|
|Camera Interface|CSI Port|
|Display Interface|DSI Port|

---

# Components Used

| Component | Description |
|-----------|-------------|
|Raspberry Pi|Single-board computer|
|LED|Output device|
|Push Button|Input device|
|220 Ω Resistor|Limits LED current|
|10 kΩ Resistor|Pull-down resistor|
|Breadboard|Prototype circuit|
|Jumper Wires|Electrical connections|

---

# Figure 1

**Raspberry Pi 4 Board Layout**

<img width="1500" height="946" alt="image" src="https://github.com/user-attachments/assets/462b3d70-9b14-4fef-a43c-3101c9245021" />


---

# Figure 2

**40-Pin GPIO Pinout**

<img width="1000" height="873" alt="image" src="https://github.com/user-attachments/assets/3b8997af-0b9a-4049-9d2d-e3eaca954004" />


---

# Working Principle

The Raspberry Pi executes a Python program that continuously monitors the push button.

- When the button is pressed, the GPIO input becomes HIGH.
- The program detects this change.
- The Raspberry Pi turns ON the LED.
- When the button is released, the LED turns OFF.

This demonstrates basic GPIO input and output interfacing.

---

# Circuit Diagram

## Figure 3

**LED and Push Button Interfacing with Raspberry Pi**

<img width="1440" height="990" alt="image" src="https://github.com/user-attachments/assets/0a433723-ad1e-4f56-8fbc-2b171d20f1ff" />

<img width="656" height="500" alt="image" src="https://github.com/user-attachments/assets/3bff41d4-e317-4ad5-b4bd-b5c4e2711cbe" />

---

# Circuit Connections

## LED Connection

| Raspberry Pi GPIO | Component |
|-------------------|-----------|
|GPIO17 (Pin 11)|220 Ω Resistor|
|220 Ω Resistor|LED Anode|
|LED Cathode|GND|

---

## Push Button Connection

| Raspberry Pi GPIO | Component |
|-------------------|-----------|
|GPIO18 (Pin 12)|Push Button|
|Other Terminal|3.3V|
|GPIO18|10 kΩ Pull-down Resistor|
|Resistor|GND|

---

# Python Program

```python
import RPi.GPIO as GPIO
import time

LED = 17
BUTTON = 18

GPIO.setmode(GPIO.BCM)

GPIO.setup(LED, GPIO.OUT)
GPIO.setup(BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

print("Press Ctrl+C to Exit")

try:
    while True:
        if GPIO.input(BUTTON):
            GPIO.output(LED, GPIO.HIGH)
        else:
            GPIO.output(LED, GPIO.LOW)

except KeyboardInterrupt:
    GPIO.cleanup()
```

---

# Procedure

1. Assemble the LED circuit.
2. Connect the push button circuit.
3. Power ON the Raspberry Pi.
4. Open the Terminal.
5. Create a Python program.
6. Save the file.
7. Execute the program using:

```bash
python3 gpio_test.py
```

8. Press the push button.
9. Observe the LED.
10. Press **Ctrl + C** to terminate the program.

---

# Observation

| Test | Observation |
|------|-------------|
| Raspberry Pi Booted | ✔ |
| GPIO Configured | ✔ |
| Push Button Detected | ✔ |
| LED ON | ✔ |
| LED OFF | ✔ |

---

# Result

The Raspberry Pi GPIO interface was successfully studied. The LED was controlled using a push button through a Python program, demonstrating basic GPIO input/output interfacing.

---

# Conclusion

In this experiment, students became familiar with the Raspberry Pi hardware, Raspberry Pi OS, and GPIO architecture. By interfacing an LED and a push button, they learned how to configure GPIO pins for input and output using Python. This experiment forms the foundation for advanced Raspberry Pi applications in robotics, IoT, automation, computer vision, and embedded systems.

---

# Applications

- Home Automation
- IoT Systems
- Robotics
- Smart Agriculture
- Industrial Automation
- Surveillance Systems
- AI Applications
- Sensor Data Acquisition

---

# Precautions

- Power OFF the Raspberry Pi before making connections.
- Never connect 5V directly to GPIO pins.
- Use a current-limiting resistor with LEDs.
- Verify GPIO pin numbers before wiring.
- Avoid short circuits.
- Shut down the Raspberry Pi properly before disconnecting power.

---

# Viva Questions

1. What is Raspberry Pi?
2. What is the difference between Raspberry Pi and Arduino?
3. What operating system is used on Raspberry Pi?
4. How many GPIO pins are available on Raspberry Pi 4?
5. Why is a resistor used with an LED?
6. What is the purpose of a pull-down resistor?
7. Which programming language is commonly used with Raspberry Pi?
8. What is GPIO?
9. Name four applications of Raspberry Pi.
10. What is the difference between GPIO.BCM and GPIO.BOARD numbering?
11. What is Raspberry Pi OS?
12. Can Raspberry Pi run multiple applications simultaneously?

---

