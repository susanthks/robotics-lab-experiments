# Experiment 12: Implementing a Weather Station Using Raspberry Pi

## 1. Aim

To implement a basic weather station using Raspberry Pi to measure and display environmental parameters such as temperature, humidity, and atmospheric pressure.

## 2. Hardware Required

| Sl. No. | Component | Quantity |
|---|---|---:|
| 1 | Raspberry Pi | 1 |
| 2 | DHT11/DHT22 Temperature & Humidity Sensor | 1 |
| 3 | BMP280/BME280 Pressure Sensor | 1 |
| 4 | Breadboard | 1 |
| 5 | Jumper Wires | As required |
| 6 | Raspberry Pi Power Supply | 1 |

> **Note:** DHT11 can be used for basic temperature and humidity measurement. BME280 can additionally provide atmospheric pressure.

## 3. Theory

A weather station is a system used to measure environmental conditions.

In this experiment, Raspberry Pi acts as the main processing unit and receives sensor data through its GPIO and I2C interfaces.

### Parameters Measured

- **Temperature** – measured in °C
- **Humidity** – measured in %RH
- **Atmospheric Pressure** – measured in hPa

### Block Diagram

```text
       DHT11 / DHT22
       Temperature
        Humidity
           │
           │ GPIO
           ▼
    ┌──────────────┐
    │ Raspberry Pi │
    └──────┬───────┘
           │ I2C
           ▼
        BMP280
        Pressure
           │
           ▼
     Display / Terminal
```

## 4. Pin Connections

### DHT11 to Raspberry Pi

| DHT11 Pin | Raspberry Pi |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

### BMP280 to Raspberry Pi — I2C

| BMP280 Pin | Raspberry Pi |
|---|---|
| VIN/VCC | 3.3V |
| GND | GND |
| SDA | GPIO 2 (SDA) |
| SCL | GPIO 3 (SCL) |

> Check the sensor module's voltage requirements before connecting it.

## 5. Software Requirements

- Raspberry Pi OS
- Python 3
- GPIO/I2C support
- Required Python sensor libraries

Enable I2C using:

```bash
sudo raspi-config
```

Then select:

```text
Interface Options → I2C → Enable
```

Install required libraries according to the sensor modules being used.

For example:

```bash
pip install adafruit-circuitpython-dht
pip install adafruit-circuitpython-bmp280
```

## 6. Algorithm

1. Initialize Raspberry Pi and sensors.
2. Read temperature and humidity from DHT11/DHT22.
3. Read atmospheric pressure from BMP280/BME280.
4. Display the measured values.
5. Repeat the measurement at regular intervals.

## 7. Python Program

```python
weather_station.py
```

> **Note:** If a DHT22 is used, replace `adafruit_dht.DHT11` with `adafruit_dht.DHT22`.

## 8. Procedure

1. Connect the DHT11/DHT22 and BMP280/BME280 to the Raspberry Pi.
2. Enable the I2C interface.
3. Install the required Python libraries.
4. Create and save the Python program.
5. Run the program from the terminal.
6. Observe temperature, humidity, and pressure readings.
7. Compare the readings under different environmental conditions.

## 9. Expected Output

```text
Raspberry Pi Weather Station
----------------------------
Temperature : 28.4 °C
Humidity    : 72.0 %
Pressure    : 1008.6 hPa
----------------------------
Temperature : 28.5 °C
Humidity    : 71.8 %
Pressure    : 1008.5 hPa
----------------------------
```

## 10. Observation

| Trial | Temperature (°C) | Humidity (%) | Pressure (hPa) |
|---:|---:|---:|---:|
| 1 | | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |

## 11. Result

A basic weather station was successfully implemented using Raspberry Pi. The system measured and displayed temperature, humidity, and atmospheric pressure using connected environmental sensors.

## 12. Precautions

- Use **3.3 V logic** with Raspberry Pi GPIO.
- Do not connect 5 V signals directly to Raspberry Pi GPIO pins.
- Check the sensor pin configuration before powering the circuit.
- Keep the temperature/humidity sensor away from direct heat sources.
- Ensure proper I2C connections for BMP280/BME280.
- Do not short Raspberry Pi GPIO pins.

## 13. Viva Questions

1. What is a weather station?
2. Why is Raspberry Pi used in this experiment?
3. What parameters can be measured using a DHT11?
4. What is the difference between DHT11 and DHT22?
5. What is atmospheric pressure?
6. What is the unit of atmospheric pressure?
7. What is I2C?
8. Which GPIO pins are used for I2C on Raspberry Pi?
9. What is the function of SDA and SCL?
10. Why should Raspberry Pi GPIO pins not be connected directly to 5 V signals?
11. How can the weather station data be stored?
12. How can this system be extended to IoT-based remote weather monitoring?
