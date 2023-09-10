// Import Libraries
#include <Servo.h>;
#include <Adafruit_NeoPixel.h>;
#include <ArduinoBLE.h>;

// Initialise Variables

// Pins Initialisation
#define ferrisWheelPIN *placeholder*;
#define stairsPIN *placeholder*;

// LED Strips Initialisation
    
// Creating LED objects with the following parrameters
// Parameter 1: The amount of pixels in each light (Takes in integers)
// Parameter 2: The location of used pin for the LED strips (Takes in integers)
// Parameter 3: The flag colors (Takes in variables from the //Adafruit_NeoPixel.h\\ library)

Adafruit_NeoPixel ferrisWheelLED = Adafruit_NeoPixel(120,ferrisWheelPIN,NEO_GRB);
Adafruit_NeoPixel stairsLED = Adafruit_NeoPixel(120,stairsPIN,NEO_GRB);

// LED Flags Initialisation
bool ferrisWheelMotorRunning = false; //Flag if the ferris wheel motor is running
bool stairsMotorRunning = false; //Flag if the stairs motor is running

// Setup Function
void setup(){
    
    // All LED initialisation
    setupLED();
}

// Loop Function
void loop(){

    // Run all the subsystems
    detectRemote();
    runFerrisWheel();
    runStaircase();
    runTrackSplitter();
}

// Detect Remote Function (BEN, QUOC)
void detectRemote(){
   
}

// Run Ferris Wheel 
void runFerrisWheel(){
    ferrisWheelLights();
    ferrisWheelMotor();
}

// Run Staircase Function
void runStaircase(){
    staircaseLights();
    staircaseMotor();
}

// Run Track Splitter Function (EUGENE)
void runTrackSplitter(){
}

// Ferris Wheel Lights Function (IRVIN)
void ferrisWheelLights(){
    if(ferrisWheelMotorRunning){ // If ferris wheel motor is functional turn the ferris wheel LED to green
        ferrisWheelLED.fill((0,255,0)); //Green
    }else if(!ferrisWheelMotorRunning){ // If ferris wheel motor is not functional turn the ferris wheel LED to red
        ferrisWheelLED.fill((255,0,0)); //Red
    }
}

// Ferris Wheel Motor Function (RUMETH)
void ferrisWheelMotor(){
    // Pseudocode (IRVIN)
    
        // runMotor(); *the function will include ferrisWheelMotorRunning = true*
        // if(motorSpeed <= *a small number close to zero to create buffer for errors*)
            // ferrisWheelMotorRunning = false;
            // killSwitch(); *turns off everything (e.g. motors, splitter)* 

}

// Staircase Lights Function (VIKIL)
void staircaseLights(){
    if(stairsMotorRunning){ // If stairs motor is functional turn the stairs LED to green
        stairsLED.fill((0,255,0)); //Green
    }else if(!stairsMotorRunning){ // If stairs motor is not functional turn the stairs LED to red
        stairsLED.fill((255,0,0)); //Red
    }
}

// Staircase Motor Function (THOMAS)
void staircaseMotor(){
    // Pseudocode (IRVIN)
    
        // runMotor(); *runMotor() will include stairsMotorRunning = true*
        // if(motorSpeed <= *a small number close to zero to create buffer for errors*)
            // stairsMotorRunning = false;
            // killSwitch(); *turns off everything (e.g. motors, splitter)*  
}

// All LED setups (IRVIN)
void setupLED(){
    ferrisWheelLED.begin();
    ferrisWheelLED.show();
    stairsLED.begin();
    stairsLED.show();
}
