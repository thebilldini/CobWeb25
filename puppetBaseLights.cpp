#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(30, 6, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin(); strip.show();
  pinMode(9, OUTPUT); pinMode(10, OUTPUT); pinMode(11, OUTPUT);
}
void loop() {
  strip.setPixelColor(0, strip.Color(0, 50, 0)); // one green pixel
  strip.show();
  analogWrite(9, 255);  // R
  analogWrite(10, 128); // G
  analogWrite(11, 0);   // B
}
