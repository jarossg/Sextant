Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void printCompass()
{
  sensors_event_t event;
  mag.getEvent(&event);
  /*
    Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  "); Serial.println("uT");
  */
}
