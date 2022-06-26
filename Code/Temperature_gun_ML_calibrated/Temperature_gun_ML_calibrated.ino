#include <Arduino.h>
#include <U8g2lib.h>
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
#include <Wire.h>
//#include <movingAvg.h>



#define MSG_DEBUG
#define home_page_width 128
#define home_page_height 64

#define normal_tempF_max  99.5
#define mild_tempF_max    101


//#define MovReadings 10
#define avgReadings 8

//amb. temp >83 & < 91  avg offset 3.23

#define m1   1.02751
#define c1  -0.34754

//amb. temp >91  avg offset 3.23
#define m2   1.03983
#define c2  -0.66635

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

IRTherm therm; // Create an IRTherm object to interact with throughout
//movingAvg TEMP(MovReadings);

static const unsigned char splash_120x63_bits[] U8X8_PROGMEM = {
  //enter here splash screen .xbm code
};

static const unsigned char welcome_120x36_bits[] U8X8_PROGMEM = {
  //enter here welcome screen .xbm code
};

static const unsigned char cool_28x28_bits[] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x64, 0x02, 0x00,
  0x00, 0x68, 0x01, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x40, 0x60, 0x20, 0x00,
  0x40, 0x60, 0x20, 0x00, 0x4c, 0x60, 0x20, 0x03, 0x78, 0x60, 0xe0, 0x01,
  0xe0, 0x60, 0x70, 0x00, 0xf8, 0x61, 0xf8, 0x01, 0x0c, 0x66, 0x06, 0x03,
  0x00, 0xfc, 0x03, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00,
  0x00, 0x7c, 0x03, 0x00, 0x0c, 0x66, 0x06, 0x03, 0xf8, 0x61, 0xf8, 0x01,
  0xe0, 0x60, 0x70, 0x00, 0x78, 0x60, 0xe0, 0x01, 0x4c, 0x60, 0x20, 0x03,
  0x40, 0x60, 0x20, 0x00, 0x60, 0x60, 0x60, 0x00, 0x00, 0xf0, 0x00, 0x00,
  0x00, 0x68, 0x01, 0x00, 0x00, 0x64, 0x02, 0x00, 0x00, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

static const unsigned char hot_28x28_bits[] U8X8_PROGMEM = {
  0x00, 0x10, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00,
  0x00, 0x88, 0x01, 0x00, 0x00, 0x08, 0x03, 0x00, 0x00, 0x04, 0x04, 0x00,
  0x00, 0x06, 0x08, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x01, 0x30, 0x00,
  0x80, 0xc0, 0x60, 0x00, 0xc0, 0xc0, 0x41, 0x00, 0x60, 0x40, 0x81, 0x00,
  0x20, 0x40, 0x82, 0x00, 0x10, 0x40, 0x06, 0x01, 0x18, 0x40, 0x04, 0x01,
  0x08, 0x46, 0x04, 0x01, 0x08, 0x6e, 0x08, 0x03, 0x0c, 0x31, 0x08, 0x02,
  0x04, 0x01, 0x08, 0x02, 0x04, 0x01, 0x0c, 0x02, 0x04, 0x01, 0x04, 0x01,
  0x08, 0x03, 0x04, 0x01, 0x08, 0x06, 0x02, 0x01, 0x18, 0x00, 0x80, 0x00,
  0x30, 0x00, 0xc0, 0x00, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x01, 0x30, 0x00,
  0x00, 0x07, 0x18, 0x00
};

static const unsigned char warm_28x28_bits[] U8X8_PROGMEM = {
  0x18, 0x30, 0x60, 0x00, 0x78, 0xf0, 0xe0, 0x01, 0x18, 0x30, 0x70, 0x00,
  0x24, 0x68, 0xd0, 0x00, 0x20, 0x40, 0x80, 0x00, 0x40, 0xc0, 0x80, 0x01,
  0x40, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01,
  0x40, 0x80, 0x00, 0x01, 0x20, 0x40, 0x80, 0x00, 0x20, 0x40, 0x80, 0x00,
  0x30, 0x20, 0x40, 0x00, 0x10, 0x20, 0x40, 0x00, 0x10, 0x20, 0x40, 0x00,
  0x10, 0x20, 0x40, 0x00, 0x30, 0x60, 0xc0, 0x00, 0x20, 0x40, 0x80, 0x00,
  0x60, 0xc0, 0x80, 0x01, 0x40, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01,
  0x40, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01, 0x60, 0xc0, 0x80, 0x00,
  0x20, 0x40, 0x80, 0x00, 0x30, 0x20, 0x40, 0x00, 0x10, 0x20, 0x40, 0x00,
  0x18, 0x10, 0x20, 0x00
};

#define buzz_pin 3
#define laser_pin 4

const byte LED_PIN = 8; // Optional LED attached to pin 8 (active low)

//float newEmissivity = 0.97;
//float newEmissivity = 0.95;
float Temp_Celcius;
float Temp_Farenheit;
float Temp_AmbientF;

void setup()
{
  therm.begin(); // Initialize thermal IR sensor
  therm.setUnit(TEMP_F); // Set the library's units to Farenheit
  //therm.setUnit(TEMP_C); // Set the library's units to Farenheit
  //therm.setEmissivity(newEmissivity);
  pinMode(buzz_pin, OUTPUT);
  pinMode(laser_pin, OUTPUT);
#ifdef MSG_DEBUG
  Serial.begin(115200);
#endif

  u8g2.begin();
  disp_splash();
  //TEMP.begin();

  Serial.println("======================== START =============================");

  Serial.print("Emissivity set at: ");
  Serial.print(therm.readEmissivity());

  therm.readRange();//Read minimum and maximum ranges of temperature set in sensor's eeprom
  Serial.print(" Min T: ");
  Serial.print(therm.minimum());
  Serial.print(" Max T: ");
  Serial.println(therm.maximum());

}

float readTEMP()
{
  float AVGread = 0;
  Temp_AmbientF = 0;
  float Regr_Read = 0;
  for (int i = 1; i <= avgReadings; i++)
  {
    if (therm.read()) // On success, read() will return 1, on fail 0.
    {
      AVGread = AVGread + therm.object();
      Temp_AmbientF = Temp_AmbientF + therm.ambient();
    }
    else
      return -1;
    delay(120);
  }
  AVGread = AVGread / avgReadings;
  Temp_AmbientF = Temp_AmbientF / avgReadings;

  if (Temp_AmbientF < 92)
  {
    Regr_Read = (m1 * AVGread) + c1; //Add Primary Linear Regression model here... anbient temp is between 83 to 90 F when temp. rises from 94 to 108
  }
  else
  {
    Regr_Read = (m2 * AVGread) + c2; //Add Secondary model here... 
  }

#ifdef MSG_DEBUG
  Serial.print("Cal. Temp.: ");
  Serial.print(Regr_Read);
  Serial.print("   Average Temp.: ");
  Serial.print(AVGread);
  Serial.print("   Ambient Temp.: ");
  Serial.print(Temp_AmbientF);
  Serial.println(" F ");

#endif

  return Regr_Read; //values without corrections added to it
}


void loop()
{
  //delay(500);
  //idle_UI();
  //delay(500);
  //digitalWrite(laser_pin, HIGH);

  //Temp_Farenheit = Move_TEMP();
  Temp_Farenheit = readTEMP();

  //Temp_Celcius = (Temp_Farenheit - 32) * .5556;

  if (Temp_Farenheit <= normal_tempF_max) //Temp less than 99.6 temperature is normal
  {
    UI(Temp_Farenheit, Temp_Celcius, 0); //normal
    //beep(0);
  }
  else if ((Temp_Farenheit > normal_tempF_max) && (Temp_Farenheit <= mild_tempF_max)) //temp between 99.6 and 101 then  mild fever
  {
    UI(Temp_Farenheit, Temp_Celcius, 1); //MILD Fever
    //beep(1);
  }
  else if (Temp_Farenheit > mild_tempF_max) //temp greater than 101.00 then high fever
  {
    UI(Temp_Farenheit, Temp_Celcius, 2); //HIGH Fever
    //beep(2);
  }
  delay(500);
  //while (1);
}


void UI(float TF, float TC, uint8_t flag)
{
  u8g2.firstPage();
  do
  {
    u8g2.drawFrame(0,  0,  home_page_width,  home_page_height);
    u8g2.drawHLine(0, 45, 128);
    u8g2.drawVLine(92, 0, 45);

    u8g2.setFont(u8g2_font_luIS14_tf);  //u8g2_font_luIS14_tr  u8g2_font_fur14_tf  u8g2_font_ncenB14_tr
    u8g2.setCursor(0, 18);
    u8g2.print(TF);
    u8g2.setCursor(0, 40);
    u8g2.print(TC);
    u8g2.drawGlyph(70, 18, 0x00b0);
    u8g2.drawGlyph(70, 40, 0x00b0);
    u8g2.setFont(u8g2_font_luIS12_tr);  //u8g2_font_luIS14_tr  u8g2_font_fur14_tf  u8g2_font_ncenB14_tr
    u8g2.drawStr(75, 18, "F");
    u8g2.drawStr(75, 40, "A");
    //u8g2.drawStr(75, 40, "C");

    if (flag == 0)
    {
      u8g2.drawStr(3, 60, "NORMAL");
      u8g2.drawXBMP(96, 8, 28, 28, cool_28x28_bits);
    }
    else if (flag == 1)
    {
      u8g2.drawStr(3, 60, "MILD FEVER");
      u8g2.drawXBMP(96, 8, 28, 28, warm_28x28_bits);
    }
    else if (flag == 2)
    {
      u8g2.drawStr(3, 60, "HIGH FEVER");
      u8g2.drawXBMP(96, 8, 28, 28, hot_28x28_bits);
    }
    else if (flag == 3)
    {
      u8g2.drawStr(3, 60, "ERROR");
    }
  } while ( u8g2.nextPage()); //will print data to screen until it turns false
}

void disp_splash()
{
  u8g2.firstPage();
  do
  {
    u8g2.drawXBMP(3, 1, 120, 63, splash_120x63_bits);
  } while ( u8g2.nextPage()); //will print data to screen until it turns false
}

void beep(uint8_t flag)
{
  if (flag == 0)
  {
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(buzz_pin, HIGH);
      delay(50);
      digitalWrite(buzz_pin, LOW);
      delay(50);
    }
  }
  else if (flag == 1)
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(buzz_pin, HIGH);
      delay(100);
      digitalWrite(buzz_pin, LOW);
      delay(100);
    }
  }
  else if (flag == 2)
  {
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
      delay(500);
    }
  }
}

void idle_UI()
{
  u8g2.firstPage();
  do
  {
    u8g2.drawFrame(0,  0,  home_page_width,  home_page_height);
    u8g2.drawHLine(0, 45, 128);
    u8g2.drawVLine(92, 0, 45);

    u8g2.setFont(u8g2_font_luIS14_tf);  //u8g2_font_luIS14_tr  u8g2_font_fur14_tf  u8g2_font_ncenB14_tr
    u8g2.setCursor(0, 18);
    u8g2.print("___.__");
    u8g2.setCursor(0, 40);
    u8g2.print("___.__");
    u8g2.drawGlyph(70, 18, 0x00b0);
    u8g2.drawGlyph(70, 40, 0x00b0);

    u8g2.setFont(u8g2_font_luIS12_tr);  //u8g2_font_luIS14_tr  u8g2_font_fur14_tf  u8g2_font_ncenB14_tr
    u8g2.drawStr(75, 18, "F");
    u8g2.drawStr(75, 40, "C");
    u8g2.drawStr(3, 60, "Press Trigger");

  } while ( u8g2.nextPage()); //will print data to screen until it turns false
}
