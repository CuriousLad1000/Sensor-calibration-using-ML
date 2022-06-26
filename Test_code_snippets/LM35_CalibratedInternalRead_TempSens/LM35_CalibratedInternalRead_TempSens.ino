#include <PreciseLM35.h>

const int pinLM35 = A1;
const float measuredVsReadArefRatio = 0.9936; // enter here your ratio between measured and expected AREF
PreciseLM35 lm35(pinLM35, INTERNAL, measuredVsReadArefRatio);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println("Temp (C): " + String(lm35.readCelsius()));
  // Serial.println("Temp (F): " + String(lm35.readFahrenheit()));
  //Serial.println("AREF: " + String(lm35.readPreciseAref()));
  delay(500);
}
