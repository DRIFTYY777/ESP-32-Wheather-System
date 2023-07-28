#include <Arduino.h>
#include "writtenbyme.h"

void setup()
{
  Serial.begin(115200);
  main_parr kuk; // providing a name to class
  kuk.connection_windsepeed();
  kuk.under_setup1();
  kuk.under_setup2();
  kuk.firebase();
}

void loop()
{
  main_parr kuk; // providing a name to class 99Nigga
  // delay(10000);
  kuk.windspeed();
  kuk.wind_direction_fun();
  kuk.getTimeStamp();
  kuk.fucking_wifi();
  kuk.upload_data();
  WiFi.disconnect();
  // delay(10000);
  // delay(240000); //4+ minutes
  // ESP.restart();
}