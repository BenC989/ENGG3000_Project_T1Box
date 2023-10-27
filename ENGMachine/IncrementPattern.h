#include "LEDPattern.h"
#include "Constants.h"

class IncrementPattern : public LEDPattern
{
  public:
    IncrementPattern(LEDStrip& ledStripRef) : LEDPattern(ledStripRef) {}
    void executePattern() override
    {
      if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
      {   
        strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(strip.redColor, strip.greenColor, strip.blueColor));
        strip.show();

        led_Patt_Lasttriggered = time;

        if (led_Patt_IncrementPattIndex == NUM_LEDS - 1)
        {
          strip.clear();
          led_Patt_IncrementPattIndex = -1;
        }

        led_Patt_IncrementPattIndex++;

        adjustBrightness();
      }
    }
};
