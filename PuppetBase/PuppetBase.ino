#include <Adafruit_NeoPixel.h>
volatile bool lightsOff = false;
Adafruit_NeoPixel strip(251, 6, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin(); strip.show();
  pinMode(9, OUTPUT); pinMode(10, OUTPUT); pinMode(11, OUTPUT);
  pinMode(2, INPUT); // Interrupt pin
  attachInterrupt(digitalPinToInterrupt(2), turnLightsOff, RISING);
}
void turnLightsOff() {
  if (digitalRead(2) == HIGH) {
    lightsOff = true;
    detachInterrupt(digitalPinToInterrupt(2));
  }
}

// Check if interrupt pin is LOW for 10 seconds, then restart LEDs
void checkInterruptReset() {
  static unsigned long lowStart = 0;
  if (digitalRead(2) == LOW) {
    if (lowStart == 0) lowStart = millis();
    if (millis() - lowStart >= 1000UL && lightsOff) {
      lightsOff = false;
      lowStart = 0;
      attachInterrupt(digitalPinToInterrupt(2), turnLightsOff, RISING);
    }
  } else {
    lowStart = 0;
  }
}
void loop() {
  checkInterruptReset();
  if (lightsOff) {
    strip.clear();
    strip.show();
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
  } else {
    // Rainbow cylon with fade tail of 30 LEDs
    static int pos = 0;
    static int dir = 1;
    const int tailLen = 30;
    int numPixels = strip.numPixels();
    strip.clear();
    // Head: full brightness, rainbow color
    uint32_t headColor = strip.ColorHSV((pos * 65536L) / numPixels, 255, 255);
    strip.setPixelColor(pos, headColor);
    // Tail: fade out, same hue
    for (int t = 1; t <= tailLen; t++) {
      int tailPos = pos - t * dir;
      if (tailPos < 0 || tailPos >= numPixels) continue;
      uint8_t fade = map(t, 1, tailLen, 180, 0); // fade from 180 to 0
      uint32_t tailColor = strip.ColorHSV((pos * 65536L) / numPixels, 255, fade);
      strip.setPixelColor(tailPos, tailColor);
    }
    strip.show();
    // Analog outputs follow head brightness
    analogWrite(9, 255);
    analogWrite(10, 128);
    analogWrite(11, 0);
    pos += dir;
    if (pos <= 0 || pos >= numPixels - 1) {
      dir = -dir;
    }
    delay(15);
  }
}
