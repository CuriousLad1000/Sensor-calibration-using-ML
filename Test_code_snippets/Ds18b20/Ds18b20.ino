
#include <OneWire.h>
#include <DallasTemperature.h>

int Temp_sens_pin = A1;    //declare a variable to store Temperature sensor pin value

OneWire  oneWire(Temp_sens_pin); //create an instance to use OneWire library
DallasTemperature sensors(&oneWire); // Create an instance to use DallasTemperature library

void setup()
{
  Serial.begin(115200);           //start serial comm. at 9600 baud rate
  sensors.begin();
}

void loop()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float Res = sensors.getTempCByIndex(0); // You can have more than one IC on the same bus.  // 0 refers to the first IC on the wire
  Serial.print("Temperature is "); // print the message on serial monitor.
  Serial.print(Res);               // print the message on serial monitor.
  Serial.println(" *Celsius");     // print the message on serial monitor.

}
