// Import Libraries
#include <Servo.h>
#include <Adafruit_Neopixel.h>

// Initialise Variables

// Setup Function
void setup(){
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

}

// Ferris Wheel Motor Function (RUMETH)
void ferrisWheelMotor(){

}

// Staircase Lights Function (VIKIL)
void staircaseLights(){

}

// Staircase Motor Function (THOMAS)
void staircaseMotor(){

}