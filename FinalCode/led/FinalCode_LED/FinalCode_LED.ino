//================================Brief Rundown================================
/*This code impliments a class for every strip of LED instead. The class contains
necessary attributes to indipendently run a pattern itself. The patterns MUST be only called
in loop() with the {className}.{patternName} format.

================================HOW TO USE================================
Step-by-Step how to how to use:

1. Define necessary variables like pin number and number of leds in the strip

2. Initialise the LEDarray strip OUTSIDE LOOP() and SETUP() (e.g. CRGB {nameOfArrayLED}[{numberOfLED}];)

3. Initialise the LEDStrip Class with the parameter:
    * int dataPin = in what pin number is the strip plugged to
    * int numLeds = the number of LEDs in the strip
    * CRGB* led = a pointer that takes in the led array
   Example: LEDStrip stripA(DATA_PINA, NUM_LEDSA, ledsA);

4. Add LEDs to the FastLED library component IN SETUP() (e.g. FastLED.addLeds<WS2812,{dataPin}, GRB>({LEDarray},{numberOfLEDs});)

5. IN LOOP() call the method in the format of {className}.{patternName}
===========================================================================

*/

#include <FastLED.h>

#define DATA_PINA 8
#define NUM_LEDSA 15

#define DATA_PINB 7
#define NUM_LEDSB 15

#define DATA_PINC 6
#define NUM_LEDSC 15

#define DATA_PIND 5
#define NUM_LEDSD 15

unsigned long time = 0;

CRGB ledsA[NUM_LEDS]; //Roof?
CRGB ledsB[NUM_LEDS]; //Track?
CRGB ledsC[NUM_LEDS]; //Ferris Wheel?
CRGB ledsD[NUM_LEDS]; //???

class LEDStrip {
public:
  LEDStrip(int dataPin, int numLeds, CRGB* led) : dataPin(dataPin), numLeds(numLeds) {
    leds = led;
  }

  void incrementPattern() {
    if (time >= led_Patt_Lasttriggered + 50) {
    leds[led_Patt_IncrementPattIndex] = CRGB(random(25, 200), random(25, 200), random(25, 200));
    FastLED.show();
    if(led_Patt_IncrementPattIndex == numLeds-1){
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      led_Patt_IncrementPattIndex = -1;
    }
    led_Patt_IncrementPattIndex++;
    led_Patt_Lasttriggered = time;
    }
  }

 void oddSwap(){
    if (time >= led_Patt_Lasttriggered + 100) {
      if(oddSwapFlag){
        for(int i =0; i < numLeds ; i += 2){
            leds[i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
        }
        FastLED.show();
        oddSwapFlag = false;
      }else if(!oddSwapFlag){
        for(int i =0; i + 1 < numLeds ; i += 2){
            leds[i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
        }
        FastLED.show();
        oddSwapFlag = true;
      }
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      led_Patt_Lasttriggered = time;
    }
  }

  void backForth(int pix){
    if (time >= led_Patt_Lasttriggered + 100) {
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      for(int i =0 ; i < pix; i++){
        leds[led_Patt_IncrementPattIndex+i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
      }
      FastLED.show();
      led_Patt_Lasttriggered = time;
      if(hasReachEndBF(pix)){
        led_Patt_IncrementPattIndex--;
      }else{
        led_Patt_IncrementPattIndex++;
      }
    }
  }

  bool hasReachEndBF(int pix){
    if(led_Patt_IncrementPattIndex == numLeds -pix){
      return true;
    }else if(led_Patt_IncrementPattIndex <= 0){
      return false;
    }
  }

private:
  int dataPin;
  int numLeds;
  int cycleCount;
  bool oddSwapFlag = false;
  CRGB* leds;
  unsigned long led_Patt_Lasttriggered = 0;
  unsigned long led_Patt_IncrementPattIndex = 0;
};

LEDStrip stripA(DATA_PINA, NUM_LEDSA, ledsA);
LEDStrip stripB(DATA_PINA, NUM_LEDSB, ledsB);
LEDStrip stripC(DATA_PINA, NUM_LEDSC, ledsC);
LEDStrip stripD(DATA_PINA, NUM_LEDSD, ledsD);

void setup() {
  FastLED.addLeds<WS2812, DATA_PINA, GRB>(ledsA, NUM_LEDSA);
  FastLED.addLeds<WS2812, DATA_PINB, GRB>(ledsB, NUM_LEDSB);
  FastLED.addLeds<WS2812, DATA_PINC, GRB>(ledsC, NUM_LEDSC);
  FastLED.addLeds<WS2812, DATA_PIND, GRB>(ledsD, NUM_LEDSD);
}

void loop() {
  time = millis();
  stripA.incrementPattern();
  stripB.backForth(2);
  stripC.oddSwap();
  stripD.incrementPattern();
}
