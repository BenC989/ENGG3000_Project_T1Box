#include "LEDPattern.h"
#include "Constants.h"

class TetrisPattern : public LEDPattern
{
  private:
    int numPixPat = 0;
    int pix = 0;
  
  public:
    TetrisPattern(LEDStrip& ledStripRef) : LEDPattern(ledStripRef) {}
    void executePattern() override
    {
      if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
      {
        strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(strip.redColor, strip.greenColor, strip.blueColor));
        strip.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));

        strip.show();
        led_Patt_Lasttriggered = time;
        led_Patt_IncrementPattIndex++;

        if (led_Patt_IncrementPattIndex >= numPixPat)
        {
          led_Patt_IncrementPattIndex = -1;
          numPixPat -= pix;

          if (numPixPat <= 0)
            numPixPat = NUM_LEDS + pix;
        }

        adjustBrightness(); 
      }
    }
};
