#pragma once

#include "Constants.h"
#include <Adafruit_NeoPixel.h>

class LEDPattern;

class LEDStrip 
{
  private:
    LEDPattern* currentPattern;
    Adafruit_NeoPixel strip;
  
  public:
    int redColor;
    int greenColor;
    int blueColor;
    int brightPatt;

    LEDStrip();
    ~LEDStrip();
    void begin();
    void setBrightness(int brightness);
    int Color(int r, int g, int b);
    void setPixelColor(int pixel, int colour);
    void show();
    void clear();
    void setPattern(LEDPattern* newPattern);
    void executeCurrentPattern();
    void colorRandom();
};
