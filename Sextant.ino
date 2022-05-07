#include <Arduino_LSM6DS3.h>
#include <Wire.h>
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "Adafruit_VEML6070.h"
Adafruit_VEML6070 uv = Adafruit_VEML6070();

#include "RTClib.h"
RTC_DS3231 rtc;

#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("RTC starten");
  while (!rtc.begin())
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("UV-Sensor starten");
  uv.begin(VEML6070_1_T);//Integrationszeit übergeben

  Serial.println("aktuelle Zeit setzen");
  if (rtc.lostPower())
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!mag.begin())
  {
    Serial.println("Kein Magnetsensor gefunden");
    while (1);
  }

  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU");
    while (1);
  }

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Test");

  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.dayOfTheWeek());
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  // sprintf(outstring,"%d:%02d:%02d",hour,min,sec);
}

void loop() {
  sensors_event_t event;
  mag.getEvent(&event);
  /*
    Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  "); Serial.println("uT");
  */
  float x, y, z;

  IMU.readGyroscope(x, y, z);
  if (millis() % 1000)
  {
    Serial.println(uv.readUV());
  }
}
