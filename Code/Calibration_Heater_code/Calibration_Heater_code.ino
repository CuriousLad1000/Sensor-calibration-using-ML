//#include <PreciseLM35.h>
#include "OneButton.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <PID_v1.h>

OneButton button(3, true);


#define avgReadings 50
#define pinLM35 A1
#define Temp_sens_pin 6    //declare a variable to store Temperature sensor pin value
#define buzz 7
#define pot A0
#define PWM_Heater_PIN 10
int dat;

unsigned long lastMilliPrint = 0;
double Setpoint_Temp, Actual_Temp, Output_Heater_PWM, Temp;
const float measuredVsReadArefRatio = 0.9936; // enter here your ratio between measured and expected AREF
bool flag;

//double Kp = 1.5, Ki = 2.5, Kd = 4.5; //Specify the links and initial tuning parameters

//PreciseLM35 lm35(pinLM35, INTERNAL, measuredVsReadArefRatio);
OneWire  oneWire(Temp_sens_pin); //create an instance to use OneWire library
DallasTemperature sensors(&oneWire); // Create an instance to use DallasTemperature library
//PID myPID(&Actual_Temp, &Output_Heater_PWM, &Setpoint_Temp, Kp, Ki, Kd, DIRECT);


float Read = 0;
float DS_TMP = 0;

void setup()
{

  //Actual_Temp = lm35.readCelsius();
  pinMode(buzz, OUTPUT);

  Setpoint_Temp = 94.0;  //Temp. to reach
  Serial.begin(115200);
  button.attachDoubleClick(doubleclick);
  button.attachClick(clik);
  pinMode(PWM_Heater_PIN, OUTPUT);
  sensors.begin();

//  myPID.SetMode(AUTOMATIC);  //turn the PID on
}

void loop()
{
  //button.tick();
  dat = analogRead(pot);

  //Serial.print("Pot: ");
  //Serial.print(dat);

  dat = map(dat, 0, 1023, 0, 255);
  analogWrite(PWM_Heater_PIN, dat);

  //Temp = lm35.readCelsius();
  //  Temp = AVG_TEMP();
  //  Actual_Temp = Temp;

  do
  {
    sensors.requestTemperatures(); // Send the command to get temperatures
    //DS_TMP = sensors.getTempCByIndex(0); // You can have more than one IC on the same bus.  // 0 refers to the first IC on the wire
    DS_TMP = sensors.getTempFByIndex(0); // You can have more than one IC on the same bus.  // 0 refers to the first IC on the wire
  } while (DS_TMP == -196.60);

  Temp = DS_TMP;
  Actual_Temp = Temp;

  // Serial.print(" Glass_temp(C): ");
  // Serial.print(DS_TMP);

  //Serial.println();

 // myPID.Compute();
  //analogWrite(PWM_Heater_PIN, Output_Heater_PWM);
  printTempInfo();    // display data
}



float AVG_TEMP()
{
  float AVGread = 0;

  for (int i = 0; i < avgReadings; i++)
  {
    button.tick();
    //AVGread = AVGread + lm35.readCelsius();
    //AVGread = AVGread + lm35.readFahrenheit();
    delay(10);
  }
  AVGread = AVGread / avgReadings;
  return AVGread;
}


void printTempInfo()
{ // display data
  if ((millis() - lastMilliPrint) >= 150)
  {
    lastMilliPrint = millis();
    Serial.print("Water_Temp.:");
    Serial.print(Temp);   // CURRENT Temp. APPROACHING SETPOINT
  //  Serial.print(", SP:");
   // Serial.print(Setpoint_Temp); //SETPOINT LEFT
    //Serial.print(", DIFF:");
   // Serial.print(Setpoint_Temp - Temp); // CURRENT Temp. APPROACHING SETPOINT

    Serial.print(",   PWM:");
    //Serial.print(Output_Heater_PWM);   // PWM VALUE
    Serial.print(dat);   // PWM VALUE

    // Serial.print(",");
    // Serial.print(DS_TMP);  //DS_18b20_Temp
    // Serial.print(",");
    // Serial.print(Output_Heater_PWM);   // PWM VALUE

    Serial.println();

    /*  if (Setpoint_Temp - Temp <= 0.2 && (Setpoint_Temp - Temp > -0.2))
      {
        flag = 1;
        beep();
      }
      else
        flag = 0;
      beep();  */
  }

}

void beep()
{
  if (flag == 1)
  {
    digitalWrite(buzz, HIGH);
    //flag = 0;
  }
  else
  {
    digitalWrite(buzz, LOW);
    //flag = 1;
  }

}


void doubleclick()
{
  Setpoint_Temp = Setpoint_Temp - 0.20; //Temp. to reach
} // doubleclick

void clik()
{
  Setpoint_Temp = Setpoint_Temp + 0.20; //Temp. to reach
} //click
