#include <Adafruit_NeoPixel.h>;
#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN  6
#define NUM_LEDS 10

int high = 0; // This variable is not used

unsigned long time = 0; // Time used to implement event-driven code

int state = 0; // States used in the traffic light function

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB); 

// Used to manage the states accross the different motors
// Motor class to instantiate the motors and set multiple attributes that are embeded in the class
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

    // Function to stop motor 
    void stop() { 
      motor.run(RELEASE);
      status = "STOPPED";
    }

    // Function to retreive and print the motor's current status
    String getStatus() { 
      Serial.println(status);
      return status;
    }

    // Function to set the motor speed
    void setSpeed(int speed) { 
      motor.setSpeed(speed);
    }

    // Function to run the motor in a forward motion manner
    void forward() { 
        motor.run(FORWARD);
        status = "MOVING";
    }

    // Function to run the motor in a backward motion manner
    void backward() { 
        motor.run(BACKWARD);
        status = "MOVING";
    }
};

// Instantiate the motors
Motor m1 (1);
Motor m2 (4);

// Setup function
void setup() {

  // Configure the motors
  m1.setSpeed(100);
  m2.setSpeed(100);

  // Open serial port and set data rate to 9600 bits per second
  Serial.begin(9600); 

  // Configure LED strip
  strip.begin();
  strip.setBrightness(125);
}

// Loop function
void loop() {

  // Mutate the time to be seconds instead of milliseconds
  time = millis() / 1000; 
  
  // Run the motors in a forward manner
  m1.forward();
  m2.forward();
  
  // Example of time based activity
  if(time % 2) // Check for the state every two seconds
    if(state == 1) {
      state = 0;
    }
    else {
      state = 1;
    }
  delay(1000); // --- Note: We shouldn't be using delays, remember what Rex said
  
  if(time % 2000) {
    Serial.println(analogRead(0));
    Serial.println(analogRead(2));
  }

  traffic(state);
  //Serial.println(time);
}


void traffic(int state) {
  
  // Clear strip to recieve new information
  strip.clear();
  uint32_t colour = 0;
  
  // If something is blocking the sensor the strip will be set to red, green if sensor is not blocked
  if(state == 1) {
    colour = strip.Color(255, 0, 0); 
  }
  else if(state == 0) {
    colour = strip.Color(0, 255, 0);
  }

  strip.fill(colour, 0, NUM_LEDS - 1);
  strip.show();
}

// A basic pattern function - not being used at the moment
void LEDPattern1() {
  
  // Every two seconds, display a new colour on the LED strip
  if((time % 2) == 0){
    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);
  }
  colour = strip.Color(r, g, b);
  strip.fill(colour, 0, (NUM_LEDS - 1));
  strip.show();
}
