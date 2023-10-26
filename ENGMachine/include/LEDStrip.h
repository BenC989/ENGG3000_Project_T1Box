#include "LEDPattern.h"
#include "Constants.h"

class LEDStrip 
{
    private:
        LEDPattern* currentPattern;
        Adafruit_NeoPixel strip;
        
    public:
        LEDStrip() : strip(NUM_LEDS, LED_PIN, NEO_GRB);
        void setPattern(LEDPattern* newPattern) {
            currentPattern = newPattern;
        }

        void executeCurrentPattern() {
            if (currentPattern) 
                currentPattern->executePattern();
        }
};
