#include <Adafruit_NeoPixel.h>;
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10

unsigned long time = 0;
int state = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB);

// CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  //Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}


void loop() {
  time = millis() / 1000;

  //If marble passes sensor set LEDs Red 
  if(time % 5 == 0)
    if(state == 1)
      state = 0;
    else
      state = 1;

  traffic(state);
  //Serial.println(distance1);
  Serial.println(time);
}


void traffic(int state) {
  //clear strip to recieve new information
  strip.clear();
  uint32_t colour = 0;
  //If something is blocking the sensor the strip will be set to red, green if sensor is not blocked
  if(state == 1) 
    colour = strip.Color(255, 0, 0);
  else if(state == 0)
    colour = strip.Color(0, 255, 0);

  strip.fill(colour, 0, NUM_LEDS - 1);
  strip.show();
}

