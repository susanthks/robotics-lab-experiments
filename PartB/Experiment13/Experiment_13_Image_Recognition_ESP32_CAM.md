# Experiment 13: Image Recognition Using ESP32-CAM Module

## Aim

To interface an **ESP32-CAM module** with a computer/mobile device and perform basic image recognition using the onboard camera.

## Requirements

### Hardware
- ESP32-CAM (AI-Thinker)
- FTDI/USB-to-TTL programmer
- USB cable
- 5 V power supply
- Jumper wires

### Software
- Arduino IDE
- ESP32 board package
- ESP32-CAM CameraWebServer example

## Principle

The ESP32-CAM is a Wi-Fi-enabled microcontroller board with an OV2640 camera.

The camera captures an image, and the ESP32 processes the captured frames. The CameraWebServer example provides a browser-based interface through which the camera stream can be viewed.

For image recognition, the ESP32-CAM can perform tasks such as:

- Face detection
- Face recognition
- Image capture
- Real-time camera streaming

### Basic Flow

```text
        Camera
           ↓
      Image Capture
           ↓
     Image Processing
           ↓
   Face/Object Detection
           ↓
       Recognition
           ↓
    Result on Web Browser
```

## ESP32-CAM Pin Connections

For programming using an FTDI programmer:

| ESP32-CAM | FTDI |
|---|---|
| U0R / GPIO3 | TX |
| U0T / GPIO1 | RX |
| GND | GND |
| 5V | 5V |

<img width="1023" height="552" alt="image" src="https://github.com/user-attachments/assets/2bddd4ca-21c3-48df-ac37-7707d783b7e9" />


**Important:** Connect **GPIO0 to GND only during programming**. Remove the GPIO0-GND connection before normal operation.

## Procedure

### 1. Install ESP32 Board Support

1. Open Arduino IDE.
2. Go to **File → Preferences**.
3. Add the ESP32 board-manager URL.
4. Open **Tools → Board → Boards Manager**.
5. Search for **ESP32**.
6. Install the ESP32 board package.

### 2. Open CameraWebServer Example

Go to:

**File → Examples → ESP32 → Camera → CameraWebServer**

Select the camera model in the program:

```cpp
#define CAMERA_MODEL_AI_THINKER
```

Make sure other camera-model definitions are commented out.

### 3. Enter Wi-Fi Credentials

Modify:

```cpp
const char *ssid = "YOUR_WIFI_NAME";
const char *password = "YOUR_WIFI_PASSWORD";
```

Enter the Wi-Fi network name and password.

### 4. Upload the Program

1. Connect GPIO0 to GND.
2. Connect the FTDI programmer.
3. Select the appropriate ESP32-CAM board.
4. Select the correct COM/USB port.
5. Click **Upload**.
6. If required, press the **RST** button when uploading starts.
7. After uploading, disconnect GPIO0 from GND.
8. Press **RST** again.

### 5. Open the Camera Web Interface

Open the Serial Monitor.

Set the baud rate to:

```text
115200
```

The ESP32-CAM will connect to the Wi-Fi network and display an IP address.

Example:

```text
Camera Ready! Use 'http://192.168.1.105' to connect
```

Enter the displayed IP address in a web browser.

### 6. Perform Image Recognition

In the CameraWebServer interface:

1. Select an appropriate frame size.
2. Start the camera stream.
3. Enable face detection if available.
4. Use the recognition option when supported.
5. Observe the detected face/recognition result.

## Important Notes

- Use a stable **5 V supply** for the ESP32-CAM.
- Do not connect the FTDI 5 V and another external 5 V supply simultaneously unless the wiring is specifically designed for it.
- GPIO0 must be connected to GND only while entering programming mode.
- Face recognition availability depends on the ESP32 board package and example version.
- For reliable recognition, use good lighting and keep the face clearly visible.

## Expected Output

The ESP32-CAM connects to Wi-Fi and provides a live camera stream through a web browser.

When image/face recognition is enabled, the system detects the target face and displays the recognition/detection result.

```text
ESP32-CAM
    ↓
Wi-Fi Connection
    ↓
Camera Stream
    ↓
Image Processing
    ↓
Face Detection / Recognition
    ↓
Result Display
```

## Result

**Image recognition using the ESP32-CAM module was successfully implemented. The camera captured images and the recognition/detection result was observed through the web interface.**

## Viva Questions

1. What is an ESP32-CAM?
2. Which camera sensor is commonly used with ESP32-CAM?
3. What is the function of GPIO0 during programming?
4. Why is Wi-Fi useful in ESP32-CAM applications?
5. What is the difference between image classification, object detection, and face recognition?
6. What is face detection?
7. What is face recognition?
8. Why is adequate lighting important for image recognition?
9. What is the purpose of the CameraWebServer example?
10. Why is a stable power supply required for ESP32-CAM?

## Applications

- Face detection and recognition
- Smart surveillance
- Home security systems
- Attendance systems
- Object monitoring
- IoT camera systems
- Robotics vision
- Remote image monitoring
