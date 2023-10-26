#include "LEDPattern.h"
#include "Constants.h"

class IncrementPattern : public LEDPattern{
    public:
        void executePattern() override
        {
            if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
            {
                strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(redColor, greenColor, blueColor));
                strip.show();
                
                led_Patt_Lasttriggered = time;

                if (led_Patt_IncrementPattIndex == NUM_LEDS - 1)
                {
                    strip.clear();
                    led_Patt_IncrementPattIndex = -1;
                }
                
                led_Patt_IncrementPattIndex++;

                brightPatt += brightCycle % 2 == 0 ? 5 : -5;
                
                if (brightPatt == 255)
                {
                    brightCycle++;
                }
                else if (brightPatt == 5)
                {
                    brightCycle--;
                }
            }
        }
};
