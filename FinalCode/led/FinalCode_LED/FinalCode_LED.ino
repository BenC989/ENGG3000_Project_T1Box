#include <Adafruit_NeoPixel.h>;
#define LED_PIN 2
#define NUM_LEDS 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 4, NEO_GRB); //TOP
Adafruit_NeoPixel fStrip = Adafruit_NeoPixel(NUM_LEDS, 3, NEO_GRB); //Ferris Wheel
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, 2, NEO_GRB); // staircase
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, 1, NEO_GRB); // track

// Time variable
unsigned long time = 0;

// LED pattern variables
unsigned long led_Patt_Lasttriggered = 0;
unsigned long led_Patt_IncrementPattIndex = 0;
unsigned long led_Patt_Offset = 10;

int numPixPat = 0;
int LED_Patt_cycleCount = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int pattNum = random(0, 4);
int brightPatt = 10;

//Important
int pattCycle = 1;
int cycleCount = 0;
int brightCycle = 0; 
int oddSwapCount = 0;


int numPixPatF = 0;

int stairsCycleCount = 0


void setup()
{
  strip.begin();
  strip.setBrightness(125);
  Serial.begin(9600);

  fStrip.begin();
  fStrip.setBrightness(125);

  strip2.begin();
  strip2.setBrightness(125);

  strip3.begin();
  strip3.setBrightness(125);
}

void loop()
{
  time = millis();
  
  //Top LED Start
  ledStart(3);

  //Track LED Start
  trackPatt()
  colorRandom();
  strip.setBrightness(brightPatt);

  //Staircase LED Start
  stPatt(2)
  colorRandom();
  strip.setBrightness(brightPatt);

  //Ferris Wheel LED Start
  fTetris(2);
  colorRandom();
  strip.setBrightness(brightPatt);
}

// Choose what behaviour the
void ledStart(int patt)
{
  switch (patt)
  {
  case 0: // Include all of the pattern which changes in intervals
    LEDRandom();
    break;
  case 1: // Shows Increment Pattern
    incrementPatt();
    colorRandom();
    strip.setBrightness(brightPatt);
    break;
  case 2: // Shows Back Forth Pattern
    backForth(5);
    colorRandom();
    strip.setBrightness(brightPatt);
    break;
  case 3:
    oddSwap(); // Shows Odd Swap Pattern
    colorRandom();
    strip.setBrightness(brightPatt);
    break;
  case 4:
    stackMult(1); // Shows Multi-Stack Pattern
    colorRandom();
    strip.setBrightness(brightPatt);
    break;
  case 5:
    loopSingle(); // Shows Single Pixel Loop
    colorRandom();
    strip.setBrightness(brightPatt);
    break;
  }
}

// Implements all of the LED pattern and randomizes
void LEDRandom()
{
  stagePatt(pattNum);
  colorRandom();
  strip.setBrightness(brightPatt);
  Serial.println(pattNum);
  if (pattCycle % 500 == 0) // Change patterns every 500 cycles
  {
    pattNum = random(0, 4);
  }
  pattCycle++;
}

// Pattern that increments each led
void incrementPatt()
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
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

// Back forth LED pattern (pix is a parameter that sets the number of pixel in the block of LED thats going to follow the pattern)
void backForth(int pix)
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    if (cycleCount % 2 != 0)
    {
      strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(redColor, greenColor, blueColor));
      strip.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));
      led_Patt_Lasttriggered = time;
    }
    else
    {
      strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(redColor, greenColor, blueColor));
      strip.setPixelColor(led_Patt_IncrementPattIndex + pix, strip.Color(0, 0, 0));
      led_Patt_Lasttriggered = time;
    }
    strip.show();
    led_Patt_Lasttriggered = time;
    if (led_Patt_IncrementPattIndex % 2 == 0)
    {
      strip.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));
    }
    if (cycleCount % 2 != 0)
      led_Patt_IncrementPattIndex++;
    if (cycleCount % 2 == 0)
      led_Patt_IncrementPattIndex--;
    if (led_Patt_IncrementPattIndex >= NUM_LEDS)
      cycleCount++;
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

// Odd swap LED pattern
void oddSwap()
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    if (oddSwapCount % 2 == 0)
    {
      for (int i = 0; i < NUM_LEDS + 2; i += 2)
      {
        strip.setPixelColor(i, strip.Color(redColor, greenColor, blueColor));
      }
      strip.show();
      led_Patt_Lasttriggered = time;
    }
    else
    {
      for (int i = 1; i < NUM_LEDS + 2; i += 2)
      {
        strip.setPixelColor(i, strip.Color(redColor, greenColor, blueColor));
      }
      strip.show();
      led_Patt_Lasttriggered = time;
    }
    oddSwapCount++;
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
    if (brightPatt == 255)
    {
      brightCycle++;
    }
    else if (brightPatt == 5)
    {
      brightCycle--;
    }
  }
  strip.clear();
}

// Loop single LED pattern
void loopSingle()
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

// Stack mult (Tetris like pattern) LED pattern
void stackMult(int pix)
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(redColor, greenColor, blueColor));
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
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

//======================= Ferris Wheel =======================

void fTetris(int pix)
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    fStrip.setPixelColor(led_Patt_IncrementPattIndex, fStrip.Color(redColor, greenColor, blueColor));
    fStrip.setPixelColor(led_Patt_IncrementPattIndex - pix, fStrip.Color(0, 0, 0));
    fStrip.show();
    led_Patt_Lasttriggered = time;
    led_Patt_IncrementPattIndex++;
    if (led_Patt_IncrementPattIndex >= numPixPatF)
    {
      led_Patt_IncrementPattIndex = -1;
      numPixPatF -= pix;
      if (numPixPat <= 0)
        numPixPatF = NUM_LEDS + pix;
    }
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

//================Stairs LED================
void stPatt(int pix)
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    if (stairsCycleCount % 2 != 0)
    {
      strip2.setPixelColor(led_Patt_IncrementPattIndex, strip2.Color(redColor, greenColor, blueColor));
      strip2.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));
      led_Patt_Lasttriggered = time;
    }
    else
    {
      strip2.setPixelColor(led_Patt_IncrementPattIndex, strip2.Color(redColor, greenColor, blueColor));
      strip2.setPixelColor(led_Patt_IncrementPattIndex + pix, strip.Color(0, 0, 0));
      led_Patt_Lasttriggered = time;
    }
    strip2.show();
    led_Patt_Lasttriggered = time;
    if (led_Patt_IncrementPattIndex % 2 == 0)
    {
      strip2.setPixelColor(led_Patt_IncrementPattIndex - pix, strip.Color(0, 0, 0));
    }
    if (stairsCycleCount % 2 != 0)
      led_Patt_IncrementPattIndex++;
    if (stairsCycleCount % 2 == 0)
      led_Patt_IncrementPattIndex--;
    if (led_Patt_IncrementPattIndex >= NUM_LEDS)
      stairsCycleCount++;
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

//==============Track LED ===============
void trackPatt()
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    strip3.setPixelColor(led_Patt_IncrementPattIndex, strip3.Color(redColor, greenColor, blueColor));
    strip3.show();
    led_Patt_Lasttriggered = time;
    if (led_Patt_IncrementPattIndex == NUM_LEDS - 1)
    {
      strip.clear();
      led_Patt_IncrementPattIndex = -1;
    }
    led_Patt_IncrementPattIndex++;
    if (brightCycle % 2 == 0)
    {
      brightPatt += 5;
    }
    else if (brightCycle % 2 != 0)
    {
      brightPatt -= 5;
    }
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

// Generate a random colour for the LED
void colorRandom()
{
  redColor = random(0, 100);
  greenColor = random(0, 255);
  blueColor = random(0, 255);
}

// Determine which pattern to run when given a random number
void stagePatt(int patt)
{
  switch (patt)
  {
  case 0:
    incrementPatt();
    break;
  case 1:
    backForth(5);
    break;
  case 2:
    oddSwap();
    break;
  case 3:
    stackMult(1);
    break;
  case 4:
    loopSingle();
    break;
  }
}
