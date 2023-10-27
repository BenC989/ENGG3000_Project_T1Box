#include "LEDPattern.h"
#include "Constants.h"

class BackForthPattern : public LEDPattern
{
  private:
    unsigned long pix = 0;
    int cycleCount = 0;

  public:
    BackForthPattern(LEDStrip& ledStripRef) : LEDPattern(ledStripRef) {}
    void executePattern() override
    {
      if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
      {
        unsigned long offset = cycleCount % 2 != 0 ? led_Patt_IncrementPattIndex - pix : led_Patt_IncrementPattIndex + pix;

        strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(strip.redColor, strip.greenColor, strip.blueColor));
        strip.setPixelColor(offset, strip.Color(0, 0, 0));
        led_Patt_Lasttriggered = time;

        strip.show();
        led_Patt_Lasttriggered = time;

        if (led_Patt_IncrementPattIndex % 2 == 0)
        strip.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));


        led_Patt_IncrementPattIndex += cycleCount % 2 != 0 ? 1 : -1;

        if (led_Patt_IncrementPattIndex >= NUM_LEDS)
        cycleCount++;

        adjustBrightness();
      }
    }
};
