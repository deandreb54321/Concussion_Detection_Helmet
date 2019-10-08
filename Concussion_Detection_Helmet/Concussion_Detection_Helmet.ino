/*
 * Author: Deandre Baker
 * Description: Source code for the concussion detection helmet project
 */

// Includes the following libraries
#include <Wire.h>
#include "ADXL345lib.h"

// Pins
const int redPin = 13;
const int bluePin = 12;
const int greenPin = 11;

// Global variables
Accelerometer acc;
double x, y, z, g; 
int red = 0;
int blue = 0;
int green = 0;
bool minorDetected = false;
bool majorDetected = false;
const int max_g = 6;
const int med_g = 4;

void setup()
{

  // Initializes pins
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Plays a tone to indicate that the device is powered on
  tone(4, 4000, 1000);

  // Stops program if accelerometer fails to be initialized
  if (acc.begin(OSEPP_ACC_SW_ON) != 0)
  {
      while(1);
  }

  // Sets the accelerometer range to 8 g
  acc.setSensitivity(ADXL345_RANGE_PM8G);
}

void loop()
{

  // Reads acceleration values from accelerometer and assigns them to the corresponding variables
  if (acc.readGs(&x, &y, &z) != 0)
  {
    return;
  }

  // Calculates the magnitude of the net acceleration using the quadratic sum of the acceleration components
  g = sqrt(x*x + y*y + z*z);

  // Shows a green light indicating no brain injury if a minor or major accident is not detected
  if((g < med_g) && (minorDetected == false && majorDetected == false))
  {
    red = 0;
    blue = 0;
    green = 255;
  }

  // Shows a red light if a major accident is detected
  else if(g >= max_g){
    red = 255;
    blue = 0;
    green = 0;
    majorDetected = true;
  }

  // Shows an amber light if a minor accident is detected
  else{
    red = 170;
    blue = 0;
    green = 255;
    minorDetected = true;
  }

  // Produces a low tone if a major accident is detected
  if (majorDetected == true)
  {
    tone(4, 1000);
  }

  // Produces a beeping sound if a minor accident is detected
  else if(minorDetected == true)
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
