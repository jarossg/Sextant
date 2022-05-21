float pitchAlt = 0;


Madgwick filter;

float getAngle()
{
  float gx, gy, gz; //Gyro Werte
  float ax, ay, az; //Beschleunigungswerte
  float pitch;

  IMU.readGyroscope(gx, gy, gz);
  IMU.readAcceleration(ax, ay, az);

  //Serial.println("X: " + String(x) + ", Y: " + String(y) + ", Z: " + z);

  filter.updateIMU(gx, gy, gz, ax, ay, az);
  pitch = filter.getPitch();

  pitch = 0.1 * pitch + 0.9 * pitchAlt;
  pitchAlt = pitch;

  return pitch;
}
