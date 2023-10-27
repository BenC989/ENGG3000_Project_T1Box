#pragma once

#include "LEDStrip.h"

class LEDPattern 
{
  protected:
    LEDStrip& strip; 
    unsigned long led_Patt_Lasttriggered = 0;
    unsigned long led_Patt_IncrementPattIndex = 0;
    int brightCycle = 0;

  public:
    LEDPattern(LEDStrip& stripRef) : strip(stripRef) {}
    virtual void executePattern() = 0;  

    void adjustBrightness() 
    {
      strip.brightPatt += brightCycle % 2 == 0 ? 5 : -5;

      if (strip.brightPatt == 255) 
        brightCycle++;
      else if (strip.brightPatt == 5) 
        brightCycle--;
    }
    
};