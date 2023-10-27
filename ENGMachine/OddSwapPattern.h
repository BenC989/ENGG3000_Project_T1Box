#include "LEDPattern.h"
#include "Constants.h"

class OddSwapPattern : public LEDPattern
{
  private:
    int oddSwapCount = 0;
  
  public:
    OddSwapPattern(LEDStrip& ledStripRef) : LEDPattern(ledStripRef) {}
    void executePattern() override
    {
      if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
      {
        oddSwapCount % 2 == 0 ? fillStrip(0) : fillStrip(1);

        strip.show();
        led_Patt_Lasttriggered = time;

        oddSwapCount++;
        adjustBrightness();
      }
      strip.clear();
    }

    void fillStrip(int start) 
    {
      for (int i = start; i < NUM_LEDS + 2; i += 2)
        strip.setPixelColor(start, strip.Color(strip.redColor, strip.greenColor, strip.blueColor));   
    }
};
