#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "Motor.h"
#include "LEDStrip.h"
#include "Patterns.h"

int pattCycle = 0;
unsigned long time = 0;

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

void ledStart(int patt) {
    if(patt == 0) {
        LEDRandom();  // Includes all of the pattern which changes a intervals
        return;
    }
    
    strip.setPattern(getPattern(patt));
    strip.colorRandom(); 
    strip.setBrightness(strip.brightPatt);
}

void LEDRandom() {
  int pattNum = random(1, 5);
  strip.setPattern(getPattern(pattNum));
  strip.colorRandom(); 
  strip.setBrightness(strip.brightPatt); 
  Serial.println(pattNum);

  if (pattCycle % 500 == 0) // Change patterns every 500 cycles   
    pattNum = random(1, 5);
  
  pattCycle++;
}

LEDPattern* getPattern(int patt) 
{
  switch(patt) 
  {
    case 1: // Shows Increment Pattern
      return new IncrementPattern(strip);
    case 2: // Shows Back Forth Pattern
      return new BackForthPattern(strip);
    case 3: // Shows Odd Swap Pattern
      return new OddSwapPattern(strip); 
    case 4: // Shows Multi-Stack Pattern
      return new TetrisPattern(strip); 
    case 5: // Shows Single Pixel Loop
      return new LoopSinglePattern(strip); 
    default:
      return nullptr;
  }
}



