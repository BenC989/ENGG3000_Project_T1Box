#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>

#define LED_PIN_STRIP_1     2 //ferris?
#define NUM_LEDS_STRIP_1    100 //21
#define LED_PIN_STRIP_2     3 //track
#define NUM_LEDS_STRIP_2    100 //10
#define LED_PIN_STRIP_4     5 //roof?
#define NUM_LEDS_STRIP_4    100

CRGB leds_1[NUM_LEDS_STRIP_1];
CRGB leds_2[NUM_LEDS_STRIP_2];
CRGB leds_4[NUM_LEDS_STRIP_4];

unsigned int LEDLastTrigger = 0;
int index = 0;
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN_STRIP_1, GRB>(leds_1, NUM_LEDS_STRIP_1);
  FastLED.addLeds<WS2812, LED_PIN_STRIP_2, GRB>(leds_2, NUM_LEDS_STRIP_2);
  FastLED.addLeds<WS2812, LED_PIN_STRIP_4, GRB>(leds_4, NUM_LEDS_STRIP_4);
  
}

void loop() {
  unsigned long time = millis();
  
  if(time > LEDLastTrigger + 300){
    func(index);
    LEDLastTrigger = time;
    index++;

    /* 
     * Maybe print out the index and see if it stays stuck at that value
     * or if it does something else unexpected
     * 
     * see if it's using too much power? lower brightness
    */

    if(index == 100){
      index = 0;
      off();
    }
  }
  else {
    Serial.println("not working");
  }
  // off();
}

void func(int i){
    leds_1[i] = CRGB(255, 0, 0);
    leds_2[i] = CRGB(255, 0, 0);
    leds_4[i] = CRGB(255, 0, 0);
    FastLED.show();
}

void off(){
  for(int i = 0; i < 100; i++){
    leds_1[i] = CRGB(0, 0, 0);
    leds_2[i] = CRGB(0, 0, 0);
    leds_4[i] = CRGB(0, 0, 0);
    FastLED.show();
  }
}
