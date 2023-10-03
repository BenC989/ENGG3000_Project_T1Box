#include <Adafruit_NeoPixel.h>;
#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10

//define pins for error strip TO CHANGE
#define ERROR_LED_PIN  2
#define ERROR_NUM_LEDS 4

//define max RGB values
#define MAX_RGB 255
#define MIN_RGB 0

int high = 0;

unsigned long time = 0;
int state = 0;

//below variables used for LED patterns 
unsigned long led_Patt_Lasttriggered = 0;
unsigned long led_Patt_IncrementPattIndex = 0;
unsigned long led_Patt_Offset = 500;

//rgb strip declaration
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB);
Adafruit_NeoPixel errorStrip = Adafruit_NeoPixel(ERROR_NUM_LEDS,ERROR_LED_PIN, NEO_GRB);

//simple var declaration for traffic light module
unsigned int red;
unsigned int green;
unsigned int blue;

//Used to manage the states accross the different motors
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

    void stop() {
      motor.run(RELEASE);
      status = "STOPPED";
    }

    String getStatus() {
      return status;
    }
    
    void setSpeed(int speed) {
      motor.setSpeed(speed);
    }

    void forward() {
        motor.run(FORWARD);
        status = "MOVING";
    }

    void backward() {
        motor.run(BACKWARD);
        status = "MOVING";
    }

    int offset() {
      return triggerOffset;
    }

    void calcNextTriggerTime(int lastTriggerTime) {
      nextTriggerTime = lastTriggerTime + triggerOffset;
    }
};

Motor m1 (1, 500);
Motor m2 (2, 500);

void setup() {
  m1.setSpeed(50);
  m2.setSpeed(50);
  Serial.begin(9600);

  //Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}

void loop() {
  time = millis();
  m1.forward();
  m2.forward();
  //setError();
  
  if(time >= m1.nextTriggerTime) {
    m1.calcNextTriggerTime(time);
    traffic(1);
  }
}


void traffic(int state) {
  //clear strip to recieve new information
  strip.clear();
  uint32_t colour = 0;
  //If something is blocking the sensor the strip will be set to red, green if sensor is not blocked
  if(state == 1) {
    colour = strip.Color(255, 0, 0); 
  }
  else if(state == 0) {
    colour = strip.Color(0, 255, 0);
  }

  strip.fill(colour, 0, NUM_LEDS - 1);
  strip.show();
}

//motor error detection based on analog read
//TODO: need driver to test. Do it in STGA!
//bool detectMotorError(Motor m){
//  int errorValue = analogRead(m.getMotorNumber());
//  return errorValue > 300;
//}

//set error light vals red
// void setRed(){
//   red = MAX_RGB;
//   green = MIN_RGB;
//   blue = MIN_RGB;
// }

// //set error light vals green
// void setGreen(){
//   red = MIN_RGB;
//   green = MAX_RGB;
//   blue = MIN_RGB;
// }

// //set error light red if there's an error, green if there isn't
// void setError(){
//   if(detectMotorError(m1) || detectMotorError(m2)){
//     setRed();
//   }
//   else{
//     setGreen();
//   }
//   errorStrip.fill(errorStrip.Color(red, green, blue), 0, ERROR_NUM_LEDS - 1);
//   errorStrip.show();
// }

//pattern that increments each led - need to be called in loop()
void incrementPatt(){
  if(time >= led_Patt_Lasttriggered + led_Patt_Offset){
    strip.setPixelColor(led_Patt_IncrementPattIndex, strip.Color(0, 255, 0));
    strip.show();
    led_Patt_Lasttriggered = time;
    if(led_Patt_IncrementPattIndex = NUM_LEDS-1){
      strip.clear();
      led_Patt_IncrementPattIndex = -1;
    }
    led_Patt_IncrementPattIndex++;
  }
}


