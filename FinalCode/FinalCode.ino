#include <Adafruit_NeoPixel.h>;
#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10


int high = 0; //This variable is not used

unsigned long time = 0; //Time used to create a event-driven code

int state = 0; //States used in the traffic light function

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB); 

//Used to manage the states accross the different motors

//Motor class to instantiate the motors and set multiple attributes that are embeded in the class
class Motor {
  private:
    int motorNumber; 
    int speed; 
    String status; // Status of the current motor (e.g. STOPPED, MOVING)
    AF_DCMotor motor;

  public:
    Motor(int motorNumber) : motorNumber(motorNumber), motor(motorNumber)
    {
      speed = 0;
      stop();
    }

    //Stops motor 
    void stop() { 
      motor.run(RELEASE);
      status = "STOPPED";
    }

    //Retreive and prints the motor's status
    String getStatus() { 
      Serial.println(status);
      return status;
    }

    //Set motor speed
    void setSpeed(int speed) { 
      motor.setSpeed(speed);
    }

    //Run the motor in a forward motion manner
    void forward() { 
        motor.run(FORWARD);
        status = "MOVING";
    }

    //Run the motor in a backward motion manner
    void backward() { 
        motor.run(BACKWARD);
        status = "MOVING";
    }
};

//Instantiate Motors
Motor m1 (1);
Motor m2 (4);

void setup() {

  //Configure Motors
  m1.setSpeed(100);
  m2.setSpeed(100);

  //Opens serial port and sets data rate to 9600 bits per second
  Serial.begin(9600); 

  //Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}

void loop() {

  //Mutate the time to be seconds instead of milliseconds
  time = millis() / 1000; 
  
  //Run the motors in a forward manner
  m1.forward();
  m2.forward();
  
  //Example of time based activity
  if(time % 2) //Every 2 seconds checks for state
    if(state == 1) {
      state = 0;
    }
    else {
      state = 1;
    }
  delay(1000);
  if(time % 2000) {
    Serial.println(analogRead(0));
    Serial.println(analogRead(2));
  }

  traffic(state);
  //Serial.println(time);
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

