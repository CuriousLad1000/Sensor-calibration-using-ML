const int sensor = A1; // Assigning analog pin A0 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius

void setup()
{
  pinMode(sensor, INPUT); // Configuring pin A0 as input
  Serial.begin(115200);
}

void loop()
{
  tempc = analogRead(sensor);
  tempc = (tempc * 500) / 1023;
  Serial.print("DegreeC: ");
  Serial.print("\t");
  Serial.println(tempc);
  delay(500); //Delay of 500ms second for ease of viewing
}
