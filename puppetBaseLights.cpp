#include <Adafruit_NeoPixel.h>
volatile bool lightsOff = false;
Adafruit_NeoPixel strip(30, 6, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin(); strip.show();
  pinMode(9, OUTPUT); pinMode(10, OUTPUT); pinMode(11, OUTPUT);
  pinMode(2, INPUT); // Interrupt pin
  attachInterrupt(digitalPinToInterrupt(2), turnLightsOff, RISING);
}
void turnLightsOff() {
  lightsOff = true;
}
void loop() {
  if (lightsOff) {
    strip.clear();
    strip.show();
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
  } else {
    strip.setPixelColor(0, strip.Color(0, 50, 0)); // one green pixel
    strip.show();
    analogWrite(9, 255);  // R
    analogWrite(10, 128); // G
    analogWrite(11, 0);   // B
  }
}
