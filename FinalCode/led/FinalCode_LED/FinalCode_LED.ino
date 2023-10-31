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
