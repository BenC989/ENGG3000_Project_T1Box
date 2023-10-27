#include "LEDStrip.h"
#include "LEDPattern.h"

LEDStrip::LEDStrip() : strip(NUM_LEDS, LED_PIN, NEO_GRB), currentPattern(nullptr), redColor(0), greenColor(0), blueColor(0), brightPatt(10) {}

LEDStrip::~LEDStrip() {
  delete currentPattern;
}

void LEDStrip::begin() {
  strip.begin();
}

void LEDStrip::setBrightness(int brightness) {
  strip.setBrightness(brightness);
}

int LEDStrip::Color(int r, int g, int b) {
  return strip.Color(r, g, b);
}

void LEDStrip::setPixelColor(int pixel, int colour) {
  strip.setPixelColor(pixel, colour);
}

void LEDStrip::show() {
  strip.show();
}

void LEDStrip::clear() {
  strip.clear();
}

void LEDStrip::setPattern(LEDPattern* newPattern) {
  delete currentPattern;
  currentPattern = newPattern;
}

void LEDStrip::executeCurrentPattern() {
  if (currentPattern) 
    currentPattern->executePattern();
}

void LEDStrip::colorRandom() {
redColor = random(0, 100);
greenColor = random(0, 255);
blueColor = random(0, 255);
}
