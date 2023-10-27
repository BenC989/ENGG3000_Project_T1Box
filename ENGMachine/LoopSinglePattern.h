#include "LEDPattern.h"
#include "Constants.h"

class LoopSinglePattern : public LEDPattern
{
  public:
    LoopSinglePattern(LEDStrip& ledStripRef) : LEDPattern(ledStripRef) {}
    void executePattern() override
    {
      if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
      {
        strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(0, 255, 0));
        strip.setPixelColor(led_Patt_IncrementPattIndex - 1, strip.Color(0, 0, 0));

        strip.show();
        led_Patt_Lasttriggered = time;
        led_Patt_IncrementPattIndex++;
      }

      if (led_Patt_IncrementPattIndex >= NUM_LEDS)
        led_Patt_IncrementPattIndex = -1;
    }
};
