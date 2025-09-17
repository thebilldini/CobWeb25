#include <Adafruit_NeoPixel.h>
volatile bool lightsOff = false;
Adafruit_NeoPixel strip(251, 6, NEO_GRB + NEO_KHZ800);

enum EffectType { EFFECT_CYLON, EFFECT_RAINBOW, EFFECT_WIPE, EFFECT_THEATER, EFFECT_COUNT };
EffectType currentEffect = EFFECT_CYLON;

// Effect state variables
int pos = 0, dir = 1;            // For effectCylon
uint16_t firstPixelHue = 0;      // For effectRainbow
int wipePos = 0; bool forward = true; // For effectWipe
int offset = 0;                  // For effectTheater

void setup() {
  strip.begin();
  clearAllPixels(); // Ensure all NeoPixels are off at startup
  pinMode(2, INPUT); // Interrupt pin
  attachInterrupt(digitalPinToInterrupt(2), turnLightsOff, RISING);
}

void resetEffects() {
  pos = 0; dir = 1;
  firstPixelHue = 0;
  wipePos = 0; forward = true;
  offset = 0;
}

// Guarantee all pixels are off
void clearAllPixels() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); // Set to black/off
  }
  strip.show();
}

void turnLightsOff() {
  if (digitalRead(2) == HIGH) {
    lightsOff = true;
    clearAllPixels();   // Only clear once when button is pushed
    resetEffects();
    detachInterrupt(digitalPinToInterrupt(2));
  }
}

// Only clear pixels ONCE when lightsOff becomes true
void loop() {
  checkInterruptReset();

  static bool lastLightsOff = false;
  if (lightsOff) {
    if (!lastLightsOff) {
      clearAllPixels();
      lastLightsOff = true;
    }
  } else {
    lastLightsOff = false;
    switch (currentEffect) {
      case EFFECT_CYLON:   effectCylon();   break;
      case EFFECT_RAINBOW: effectRainbow(); break;
      case EFFECT_WIPE:    effectWipe();    break;
      case EFFECT_THEATER: effectTheater(); break;
    }
  }
}

// Check if interrupt pin is LOW for 1 second, then restart LEDs and change effect
void checkInterruptReset() {
  static unsigned long lowStart = 0;
  if (digitalRead(2) == LOW) {
    if (lowStart == 0) lowStart = millis();
    if (millis() - lowStart >= 1000UL && lightsOff) {
      lightsOff = false;
      lowStart = 0;
      clearAllPixels(); // Turn off all NeoPixels every time lights are triggered back on
      currentEffect = static_cast<EffectType>((currentEffect + 1) % EFFECT_COUNT);
      attachInterrupt(digitalPinToInterrupt(2), turnLightsOff, RISING);
    }
  } else {
    lowStart = 0;
  }
}

// --- EFFECTS ---

void effectCylon() {
  const int tailLen = 30;
  int numPixels = strip.numPixels();
  strip.clear();
  uint32_t headColor = strip.ColorHSV((pos * 65536L) / numPixels, 255, 255);
  strip.setPixelColor(pos, headColor);
  for (int t = 1; t <= tailLen; t++) {
    int tailPos = pos - t * dir;
    if (tailPos < 0 || tailPos >= numPixels) continue;
    uint8_t fade = map(t, 1, tailLen, 180, 0);
    uint32_t tailColor = strip.ColorHSV((pos * 65536L) / numPixels, 255, fade);
    strip.setPixelColor(tailPos, tailColor);
  }
  strip.show();
  pos += dir;
  if (pos <= 0 || pos >= numPixels - 1) dir = -dir;
  delay(15);
}

void effectRainbow() {
  int numPixels = strip.numPixels();
  for (int i = 0; i < numPixels; i++) {
    int pixelHue = firstPixelHue + (i * 65536L / numPixels);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  firstPixelHue += 256;
  delay(20);
}

void effectWipe() {
  int numPixels = strip.numPixels();
  uint32_t color = strip.Color(0, 255, 64); // teal
  strip.clear();
  for (int i = 0; i <= wipePos; i++) {
    strip.setPixelColor(forward ? i : numPixels - 1 - i, color);
  }
  strip.show();
  wipePos++;
  if (wipePos >= numPixels) {
    wipePos = 0;
    forward = !forward;
  }
  delay(10);
}

void effectTheater() {
  int numPixels = strip.numPixels();
  strip.clear();
  for (int i = 0; i < numPixels; i++) {
    if ((i + offset) % 5 == 0) {
      strip.setPixelColor(i, strip.Color(255, 32, 128)); // pinkish
    }
  }
  strip.show();
  offset = (offset + 1) % 5;
  delay(60);
}
