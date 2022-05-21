float getUVLevel()
{

  float outputVoltage = 3.3 / analogRead(A2) * analogRead(A3);

  //float uvLevel = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);
  //Serial.println(uvLevel);
  return outputVoltage;
}



float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
