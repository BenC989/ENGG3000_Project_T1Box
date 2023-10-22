// Define libraries to be included
#include <Adafruit_NeoPixel.h>;
#include <CytronMotorDriver.h>

// Define pins for the regular LED strip
#define LED_PIN 6
#define NUM_LEDS 12

// Define pins for error strip ****TO CHANGE****
#define ERROR_LED_PIN 2
#define ERROR_NUM_LEDS 4

// Define max RGB values
#define MAX_RGB 255
#define MIN_RGB 0

// Declare the two RGB strips
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB);
Adafruit_NeoPixel errorStrip = Adafruit_NeoPixel(ERROR_NUM_LEDS, ERROR_LED_PIN, NEO_GRB);

// Define variables
int high = 0;
unsigned long time = 0;
int state = 0;

// Define variables to be used for LED patterns
unsigned long led_Patt_Lasttriggered = 0;
unsigned long led_Patt_IncrementPattIndex = 0;
unsigned long led_Patt_Offset = 500;
int numPixPat = 0;
int LED_Patt_cycleCount = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int pattNum = random(0, 3);
int pattCycle = 1;
int cycleCount = 0;
int brightCycle = 0;
int oddSwapCount = 0;
int brightPatt = 10;

// Define variables for traffic light module
unsigned int red;
unsigned int green;
unsigned int blue;

/*
 * This is a class intended to be used to manage the states across the
 * two motors.
 */
class Motor
{
private:
  int motorNumber;
  int PWMNumber;
  int speed;
  String status;
  CytronMD motor;
  int triggerOffset;

public:
  int lastTriggerTime;
  int nextTriggerTime;
  int triggerTime;

  Motor(int motorNumber, int PWMNumber, int triggerTime) : motorNumber(motorNumber), PWMNumber(PWMNumber), motor(PWM_PWM, motorNumber, PWMNumber), triggerTime(triggerTime)
  {
    speed = 0;
    stop();
  }

  // Function to stop a specified motor
  void stop()
  {
    motor.setSpeed(0);
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
  void forward(int speed)
  {
    motor.setSpeed(speed);
    status = "MOVING";
  }

  // Function to set a specified motor to rotate backwards at a specified speed
  void backward(int speed)
  {
    motor.setSpeed(speed);
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

  void getMotorNumber()
  {
    return motorNumber;
  }
};

/*
 * Everything beyond this point is the main class
 */

// Declare and initialise the two motors to be used
Motor m1(1, 9, 500);
Motor m2(2, 11, 500);

// Function to initialise components
void setup()
{
  Serial.begin(9600);

  // Configure the LED strip
  strip.begin();
  strip.setBrightness(125);
}

// Function to continually execute the code
void loop()
{
  time = millis();
  m1.forward(50);
  m2.forward(50);
  // setError();

  // Calculate the next trigger time
  if (time >= m1.nextTriggerTime)
  {
    m1.calcNextTriggerTime(time);
    traffic(1);
  }

  // Run a new random pattern
  stagePatt(pattNum);
  colorRandom(); // Sets random color
  strip.setBrightness(brightPatt); // Sets new brightness
  if (pattCycle % 500 == 0) // Change patterns every 500 cycles
  {
    pattNum = random(0, 3);
  }
  pattCycle++; // Track amount of cycles
}

// Function to visually indicate an error in the state of a motor (not rotating)
void traffic(int state)
{

  // Clear the LED strip to recieve new information
  strip.clear();
  uint32_t colour = 0;

  // If something is blocking the sensor the strip will be set to red, green if sensor is not blocked
  if (state == 1)
  {
    colour = strip.Color(255, 0, 0);
  }
  else if (state == 0)
  {
    colour = strip.Color(0, 255, 0);
  }

  strip.fill(colour, 0, NUM_LEDS - 1);
  strip.show();
}

/*
 * The following code is used for error detection. It is based on
 * analog read.
 * TODO: need driver to test. Do it in STGA!
 */

// Function to detect if there is an error with the motor
bool detectMotorError(Motor m)
{
  int errorValue = analogRead(m.getMotorNumber());
  return errorValue > 300;
}

// Function to set all LEDs on the error LED strip to red
void setRed()
{
  red = MAX_RGB;
  green = MIN_RGB;
  blue = MIN_RGB;
}

// Function to set all LEDs on the error LED strip to green
void setGreen()
{
  red = MIN_RGB;
  green = MAX_RGB;
  blue = MIN_RGB;
}

// Function to set all LEDs on the error LED strip to red if an error occurs, otherwise green
void setError()
{
  if (detectMotorError(m1) || detectMotorError(m2))
  {
    setRed();
  }
  else
  {
    setGreen();
  }
  errorStrip.fill(errorStrip.Color(red, green, blue), 0, ERROR_NUM_LEDS - 1);
  errorStrip.show();
}

/*
 * <===========================The following code contains all the LED patterns.===========================>
 */

// Pattern that increments each led
void incrementPatt()
{
  if (time >= led_Patt_Lasttriggered + led_Patt_Offset)
  {
    strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(redColor, greenColor, blueColor));
    strip.show();
    led_Patt_Lasttriggered = time;
    if (led_Patt_IncrementPattIndex == numPixPat - 1)
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
    if (led_Patt_IncrementPattIndex >= NUMstrip)
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
  }
}
