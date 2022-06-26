#include <PID_v1.h>
#include <PreciseLM35.h>
#include "OneButton.h"

#define TempSens_pin  A1
#define PWM_Heater_PIN 10
#define Dbug       1


const float measuredVsReadArefRatio = 0.9936; // enter here your ratio between measured and expected AREF
PreciseLM35 lm35(TempSens_pin, INTERNAL, measuredVsReadArefRatio);

OneButton button1(2, true);    // Setup a new OneButton on pin A1.
OneButton button2(3, true);    // Setup a new OneButton on pin A2.

double Setpoint_Temp = 40.0, Actual_Temp, Output_Heater_PWM, Temp;

unsigned long lastMilliPrint = 0;
unsigned long lastMilliPrint2 = 0;

int counter;  //To count button press.


//Specify the links and initial tuning parameters
double Kp = 1.5, Ki = 2, Kd = 5;
PID myPID(&Actual_Temp, &Output_Heater_PWM, &Setpoint_Temp, Kp, Ki, Kd, DIRECT);

void setup()
{
  pinMode(PWM_Heater_PIN, OUTPUT);

  Actual_Temp = lm35.readCelsius();
  //Setpoint_Temp = 50;  //Temp. to reach

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  Serial.begin(115200);
  button1.attachClick(Increase);
  button2.attachClick(Decrease);

}

void loop()
{
  button1.tick();
  button2.tick();
  Temp = lm35.readCelsius();
  Actual_Temp = Temp;

  myPID.Compute();
  analogWrite(PWM_Heater_PIN, Output_Heater_PWM);


  if ((millis() - lastMilliPrint2) >= 500)
  {
    lastMilliPrint2 = millis();
    //lcdPrint2();
  }

  if (Dbug == 1)  printTempInfo();    // display data
}

void printTempInfo()
{ // display data
  if ((millis() - lastMilliPrint) >= 150)
  {
    lastMilliPrint = millis();

    Serial.print(Setpoint_Temp); //SETPOINT LEFT
    Serial.print(",");
    Serial.print(Temp);   // CURRENT Temp. APPROACHING SETPOINT
    Serial.print(",");
    Serial.print(Output_Heater_PWM);   // PWM VALUE
    Serial.print(",");
    Serial.println(Setpoint_Temp-Temp);   // CURRENT Temp. APPROACHING SETPOINT

  }
}

void Increase()
{
  Setpoint_Temp = Setpoint_Temp + 5;
  Setpoint_Temp = constrain(Setpoint_Temp, 40, 65);
}

void Decrease()
{
  Setpoint_Temp = Setpoint_Temp - 5;
  Setpoint_Temp = constrain(Setpoint_Temp, 40, 65);
}


void lcdPrint2()
{
  Serial.print(" SetPt(C): ");
  Serial.print(Setpoint_Temp);
  Serial.print(" Now_Temp(C): ");
  Serial.print(Actual_Temp);
}
