#include <Adafruit_NeoPixel.h>;
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10

unsigned long time = 0;
int state = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB);

//Used to manage the states accross the different motors
class Motor {
  private:
    int pin1, pin2;
    int currentSpeed;
    String status;

  public:
    Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2)
    {
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      currentSpeed = 0;
      status = "STOPPED";
    }

    void stop() {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      status = "STOPPED"
    }

    String status() {
      return status;
    }
    
    void setSpeed(int speed) {
      //Implementation Needed
    }

    void forward(int speed) {
      //Implementation Needed
    }

    void forward(int speed) {
      //Implementation Needed
    }
}

void setup() {
  Serial.begin(9600);

  //Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}


void loop() {
  time = millis() / 1000;

  //Example of time based activity
  if(time % 5 == 0)
    if(state == 1)
      state = 0;
    else
      state = 1;

  traffic(state);
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

