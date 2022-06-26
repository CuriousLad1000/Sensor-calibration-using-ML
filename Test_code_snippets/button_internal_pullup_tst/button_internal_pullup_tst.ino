int OK = 2; // A0 damaged
int dat;
void setup()
{
  Serial.begin(115200);
  pinMode(OK, INPUT);
  digitalWrite(OK, 1);
}

void loop()
{
  dat = digitalRead(OK);
  delay(10);
  if (dat == 0)
  {
    Serial.println("button pressed");
  }
}
