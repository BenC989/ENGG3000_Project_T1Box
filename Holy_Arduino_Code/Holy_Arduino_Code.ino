#include <FastLED.h>
#include <AFMotor.h>

//Roof
#define DATA_PIND 2
#define NUM_LEDSD 23

unsigned long time = 0;
int index = 0;
boolean forwards = true;

CRGB ledsD[NUM_LEDSD]; 

class Motor {
private:
  int motorNumber;
  int speed;
  String status;
  AF_DCMotor motor;
  int triggerOffset;

public:
  int lastTriggerTime;
  int nextTriggerTime;
  int triggerTime;

  Motor(int motorNumber, int triggerTime) : motorNumber(motorNumber), motor(motorNumber), triggerTime(triggerTime)
  {
    speed = 0;
    stop();
  }

  // Function to stop a specified motor
  void stop()
  {
    motor.run(RELEASE);
    status = "STOPPED";
  }

  // Function to get the status of a specified motor
  String getStatus()
  {
    return status;
  }

  // Function to set the speed of a a specified motor
  void setSpeed(int speed)
  {
    motor.setSpeed(speed);
  }

  // Function to set a specified motor to rotate forwards at a specified speed
  void forward()
  {
    motor.run(FORWARD);
    status = "MOVING";
  }

  // Function to set a specified motor to rotate backwards at a specified speed
  void backward()
  {
    motor.run(BACKWARD);
    status = "MOVING";
  }

  // Function to get the trigger offset value of a specified motor
  int offset()
  {
    return triggerOffset;
  }

  // Function to calculate the next trigger time of a specified motor
  void calcNextTriggerTime(int lastTriggerTime)
  {
    nextTriggerTime = lastTriggerTime + triggerOffset;
  }

  int getMotorNumber()
  {
    return motorNumber;
  }
};

class LEDStrip {
public:
  LEDStrip(int dataPin, int numLeds, CRGB* led) : dataPin(dataPin), numLeds(numLeds) {
    leds = led;
  }

  void incrementPattern() {
    if (time >= led_Patt_Lasttriggered + 75) {
    leds[led_Patt_IncrementPattIndex] = CRGB(random(25, 100), random(175, 220), random(25, 100));
    FastLED.show();
    if(led_Patt_IncrementPattIndex == numLeds-1){
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      led_Patt_IncrementPattIndex = -1;
    }
    led_Patt_IncrementPattIndex++;
    led_Patt_Lasttriggered = time;
    }
  }

   void forth(int pix) {
    if (time >= led_Patt_Lasttriggered + 75) {
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      for(int i =0 + led_Patt_IncrementPattIndex ; i < pix + led_Patt_IncrementPattIndex; i++){
        leds[(led_Patt_IncrementPattIndex+i)%10] = CRGB(random(25, 200), random(25, 200), random(25, 200));
      }
      if(led_Patt_IncrementPattIndex == numLeds-1){
        fill_solid(leds, numLeds,  CRGB(0, 0,0));
        led_Patt_IncrementPattIndex = -1;
      }
      led_Patt_IncrementPattIndex++;
      led_Patt_Lasttriggered = time;
    }
  }

   void incrementReversePattern() {
    if (time >= led_Patt_Lasttriggered + 75) {
      leds[numLeds-1-led_Patt_IncrementPattIndex] = CRGB(random(25, 200), random(25, 200), random(25, 200));
      FastLED.show();
      if(led_Patt_IncrementPattIndex == numLeds-1){
        fill_solid(leds, numLeds,  CRGB(0, 0,0));
        led_Patt_IncrementPattIndex = -1;
      }
      led_Patt_IncrementPattIndex++;
      led_Patt_Lasttriggered = time;
    }
  }



 void oddSwap(){
    if (time >= led_Patt_Lasttriggered + 500) {
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      if(oddSwapFlag){
        for(int i =0; i < numLeds ; i += 2){
            leds[i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
        }
        FastLED.show();
        oddSwapFlag = false;
      }
      else if(!oddSwapFlag){
        for(int i =1; i < numLeds ; i += 2){
            leds[i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
        }
        FastLED.show();
        oddSwapFlag = true;
      }
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
        forwards = false;
      }
      else if (hasReachStartBF(pix)){
        forwards = true;
      }
      if (forwards == true) {
        led_Patt_IncrementPattIndex++;
      }
      else {
        led_Patt_IncrementPattIndex--;
      }
    }
  }

  void backForthTest(int pix){
    if (time >= led_Patt_Lasttriggered + 100) {
      fill_solid(leds, numLeds, CRGB(0, 0,0));
      for(int i =0 ; i < pix; i++){
        leds[led_Patt_IncrementPattIndex+i] = CRGB(random(25, 200), random(25, 200), random(25, 200));
      }
      FastLED.show();
      led_Patt_Lasttriggered = time;
      if(hasReachEndBF(pix)){
        forwards = false;
      }
    }
  }

  bool hasReachEndBF(int pix){
    if(led_Patt_IncrementPattIndex == (numLeds - pix)){
      return true;
    }
    else {
      return false;
    }
  }

  bool hasReachStartBF(int pix){
    if(led_Patt_IncrementPattIndex == 0){
      return true;
    }
    else {
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
  unsigned long LEDLastTrigger = 0;
};

LEDStrip stripD(0, NUM_LEDSD, ledsD);

Motor m1(1, 500);
Motor m2(2, 500);


void setup() {
  Serial.begin(9600);
  index = 0;
  FastLED.addLeds<WS2812, DATA_PIND, GRB>(ledsD, NUM_LEDSD);

  FastLED.setBrightness(100);
  FastLED.setMaxPowerInVoltsAndMilliamps(2, 200);

  m1.setSpeed(100);
  m1.forward();

  m2.setSpeed(100);
  m2.backward();
}

void loop() {
  time = millis();
  
  stripD.incrementPattern();
}