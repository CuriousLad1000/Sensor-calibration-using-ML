
#include "OneButton.h"

OneButton button(7, true);

#define pot A0
#define heat 10
int dat;

void setup()
{
  Serial.begin(115200);
  button.attachDoubleClick(doubleclick);
  button.attachClick(clik);
  pinMode(heat, OUTPUT);
}

void loop()
{
  button.tick();
  dat = analogRead(pot);
  Serial.print("Pot: ");
  Serial.print(dat);
  dat = map(dat, 0, 1023, 0, 255);
  Serial.print(" Heater_PWM: ");
  Serial.println(dat);
  analogWrite(heat, dat);
  delay(10);
}

void doubleclick()
{

} // doubleclick

void clik()
{

} //click
