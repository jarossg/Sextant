#include <Arduino_LSM6DS3.h>
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  Serial.begin(9600);

  if(!IMU.begin())
  {
    Serial.println("Failed to initialize IMU");
    while(1);
  }

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Test");
}

void loop() {
  float x,y,z;

  IMU.readGyroscope(x,y,z);
}
