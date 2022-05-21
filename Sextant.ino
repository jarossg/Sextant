#include <Arduino.h>
#include <Arduino_LSM6DS3.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <MadgwickAHRS.h>
#include <Math.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "RTClib.h"


#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include "deklination.h"
#include "uv.h"
#include "winkel.h"
#include "zeit.h"
#include "kompass.h"
#include "berechnung.h"

float uvMax = 0;
float Winkel = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  /*   Wire.beginTransmission(VEML6070_ADDR); */
  initTime();

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
  filter.begin(104.00);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Test");

  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  float outputVoltage = getUVLevel();
  float pitch = getAngle();
  
  if (outputVoltage > uvMax)
  {
    uvMax = outputVoltage;
    Winkel = pitch;
    Serial.println("neuer Winkel: " + String(Winkel));
  }
}
