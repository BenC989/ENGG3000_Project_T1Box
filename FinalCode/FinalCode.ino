#include <Adafruit_NeoPixel.h>;
#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10

int high = 0;

unsigned long time = 0;
int state = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB);

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
Motor m2 (4, 500);

void setup() {
  m1.setSpeed(255);
  m2.setSpeed(100);
  Serial.begin(9600);

  //Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}

void loop() {
  time = millis();
  m1.forward();
  m2.forward();
  
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

bool detectMotorError(Motor m){
  int errorValue = analogRead(m.getMotorNumber());
  return errorValue > 300;
}

