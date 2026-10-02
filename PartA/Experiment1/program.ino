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
