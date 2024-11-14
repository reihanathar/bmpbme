#include <Arduino.h>
#include "BME280.h"

float dataBMEFunc();
BME bme;

float bmpBasePressure, pres;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  bme.begin();
  bme.getTemperature();
  Serial.println(bme.getPressure()); // debug
  bme.setCurrentPressure();
  while(bme.getPressure()) // wait for the sensor to get a reading
  {
    if(bme.getPressure() != 0)
    {
      bmpBasePressure = bme.getPressure() / 100.0F;
      break;
    }
  }
  Serial.println(bmpBasePressure); // debug
}

void loop()
{
  dataBMEFunc();
  pres = bme.getPressure();

  if(millis() % 1000 == 0)
  {
    Serial.println(dataBMEFunc());
  }
}

float dataBMEFunc()
{
    return (44300 * (1 - pow( (bme.getPressure())/100.0F / bmpBasePressure, (1 / 5.255)))) + 0.2;
}