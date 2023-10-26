#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "Motor.h"
#include "LEDStrip.h"
#include "LEDPattern.h"

#include "IncrementPattern.h"
#include "BackForthPattern.h"
#include "LoopSinglePattern.h"
#include "OddSwapPattern.h"
#include "RandomPattern.h"
#include "TetrisPattern.h"

// Declare and initialise the two motors to be used
Motor m1(3, 500);
Motor m2(4, 500);
LEDStrip strip;

// Function to initialise components
void setup()
{  
  // Configure the LED strip
  strip.begin();
  strip.setBrightness(125);

  m1.setSpeed(255);
  m2.setSpeed(255);

  m1.forward();
  m2.forward();
}

// Function to continually execute the code
void loop()
{
  time = millis();
  
  ledStart(4);
}

//Select LED Behaviour
void ledStart(int patt) 
{
  if(patt == 0) 
  {
    LEDRandom(); //Include all of the pattern which changes in intervals
    return;
  }

  switch(patt) 
  {
    case 1: //Shows Increment Pattern
      incrementPatt();
      break;
    case 2: //Shows Back Forth Pattern
      backForth(5);
      break;
    case 3:
      oddSwap(); //Shows Odd Swap Pattern
      break;
    case 4:
      stackMult(1); //Shows Multi-Stack Pattern
      break;
    case 5:
      loopSingle(); //Shows Single Pixel Loop
      break;
  }
  
  colorRandom(); 
  strip.setBrightness(brightPatt);
}


