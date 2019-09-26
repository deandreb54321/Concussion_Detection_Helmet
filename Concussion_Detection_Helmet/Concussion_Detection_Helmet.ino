#include <Wire.h>
#include "ADXL345lib.h"

Accelerometer acc;
bool fail;
int redPin = 13;
int bluePin = 12;
int greenPin = 11;
int red = 0;
int blue = 0;
int green = 0;
int s = 0;
int max_g = 6;
int med_g = 4;
int counter = 0;
int sound = 0;
int r = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    tone(4, 4000, 1000);

    if (acc.begin(OSEPP_ACC_SW_ON) != 0)
    {
        Serial.println("Error connecting to accelerometer");
        fail = true;
        return;
    }

    acc.setSensitivity(ADXL345_RANGE_PM4G);
}

void loop()
{
    if (fail)
      return;

    double x, y, z;
    double g;
   
    if (acc.readGs(&x, &y, &z) != 0)
    {
      Serial.println("Failed to read accelerometer");
      return;
    }

    g = sqrt(x*x + y*y + z*z);
    
    Serial.print(" G: ");
    Serial.println(g);

    if((g < max_g) && (s == 0))
    {
      red = 0;
      blue = 0;
      green = 255;
      s = 1;
    }
    else if(g > med_g)
    {
      s =1;
      if((counter == 0) && (g < max_g))
      {
        red = 170;
        blue = 0;
        green = 255;
        sound = 1;
      }
      else if (g > max_g)
      {
        red = 255;
        blue = 0;
        green = 0;
        counter = 1;
        sound = 2;
        r = 1;
        tone(4, 1000);
      }
    }
    else if ( sound == 1)
    {
        tone(4, 2000);
        delay(50);
        noTone(4);
        delay(25);
    }
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  delay(50);
}
