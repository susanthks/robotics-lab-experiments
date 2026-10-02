import time
import board
import adafruit_dht
import adafruit_bmp280

# DHT sensor
dht = adafruit_dht.DHT22(board.D4)

# BMP280 sensor using I2C
i2c = board.I2C()
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)

print("Raspberry Pi Weather Station")
print("----------------------------")

try:
    while True:
        try:
            temperature = dht.temperature
            humidity = dht.humidity
            pressure = bmp280.pressure

            print(f"Temperature : {temperature:.1f} °C")
            print(f"Humidity    : {humidity:.1f} %")
            print(f"Pressure    : {pressure:.1f} hPa")
            print("----------------------------")

        except RuntimeError as error:
            print("Sensor reading error:", error)

        time.sleep(2)

except KeyboardInterrupt:
    print("\nWeather station stopped.")

finally:
    dht.exit()
