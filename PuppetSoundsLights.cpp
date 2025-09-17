// Required for Arduino functions and types
#include <Arduino.h>
#include "pitches.h"

#define REST 0

// === Pin Assignments ===
const int BTN1 = 2;    // Button 1 (to GND, use INPUT_PULLUP)
const int BTN2 = 3;    // Button 2 (to GND, use INPUT_PULLUP)
const int LED1 = 9;    // LED for button 1
const int LED2 = 10;   // LED for button 2
const int BUZZ = 8;    // Piezo/speaker
const int SIGNAL_PIN = 4; // Pin to signal puppetBaseLights (connect to its pin 2)

// === Light-Hearted Upbeat Melody (original, ~30s, not repeating) ===
const int upbeat_co_pilot[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_D5, NOTE_B4, NOTE_G4, NOTE_E4, NOTE_D4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4,
  NOTE_F4, NOTE_A4, NOTE_C5, NOTE_F5, NOTE_D5, NOTE_B4, NOTE_G4, NOTE_F4,
  NOTE_G4, NOTE_B4, NOTE_D5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A5, NOTE_F5, NOTE_D5, NOTE_B4, NOTE_A4,
  NOTE_B4, NOTE_D5, NOTE_F5, NOTE_B5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4,
  NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_D5, NOTE_C5,
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_D6, NOTE_B5, NOTE_G5, NOTE_E5, NOTE_D5,
  NOTE_E5, NOTE_G5, NOTE_B5, NOTE_E6, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5,
  NOTE_F5, NOTE_A5, NOTE_C6, NOTE_F6, NOTE_D6, NOTE_B5, NOTE_G5, NOTE_F5,
  NOTE_G5, NOTE_B5, NOTE_D6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_A5, NOTE_G5,
  NOTE_A5, NOTE_C6, NOTE_E6, NOTE_A6, NOTE_F6, NOTE_D6, NOTE_B5, NOTE_A5,
  NOTE_B5, NOTE_D6, NOTE_F6, NOTE_B6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_B5,
  NOTE_C6, NOTE_E6, NOTE_G6, NOTE_C7, NOTE_A6, NOTE_F6, NOTE_D6, NOTE_C6,
  NOTE_D6, NOTE_F6, NOTE_A6, NOTE_D7, NOTE_B6, NOTE_G6, NOTE_E6, NOTE_D6,
  NOTE_E6, NOTE_G6, NOTE_B6, NOTE_E7, NOTE_C7, NOTE_A6, NOTE_F6, NOTE_E6,
  NOTE_D6, NOTE_B5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_D4,
  NOTE_C4, REST
};
const int upbeat_co_pilot_len[] = {
  300, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  400, 300, 300, 600, 300, 300, 300, 300,
  1000, 1000
};
const int UPBEAT_COPILOT_LEN = sizeof(upbeat_co_pilot) / sizeof(upbeat_co_pilot[0]);

// === Spooky Melody (extended to ~30s, original Copilot creation) ===
const int spooky_co_pilot[] = {
  NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_F5, REST,
  NOTE_DS5, NOTE_F5, NOTE_A4, NOTE_G4, REST,
  NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_G4, REST,
  NOTE_DS5, NOTE_F5, NOTE_C5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_DS5, NOTE_G4, REST,
  NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_A4,
  // New spooky phrases for extension
  NOTE_GS4, NOTE_B4, NOTE_D5, NOTE_F5, REST,
  NOTE_D5, NOTE_F5, NOTE_GS4, NOTE_A4, REST,
  NOTE_B4, NOTE_D5, NOTE_F5, NOTE_B4, NOTE_GS4, REST,
  NOTE_E5, NOTE_G5, NOTE_B4, NOTE_E5, REST,
  NOTE_F5, NOTE_DS5, NOTE_C5, NOTE_A4, REST,
  NOTE_G4, NOTE_B4, NOTE_DS5, NOTE_G5, NOTE_B4, NOTE_G4, REST,
  NOTE_A4, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_F5, NOTE_C5, NOTE_A4, REST,
  NOTE_DS5, NOTE_G5, NOTE_B4, NOTE_DS5, NOTE_G4, REST,
  NOTE_F5, NOTE_D5, NOTE_B4, NOTE_F5, NOTE_D5, NOTE_B4, REST,
  NOTE_C5, NOTE_E5, NOTE_GS4, NOTE_C5, NOTE_E5, NOTE_GS4, REST,
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_A4, NOTE_F5, NOTE_D5, REST,
  NOTE_B4, NOTE_G5, NOTE_E5, NOTE_B4, NOTE_G5, NOTE_E5, REST,
  NOTE_C5, NOTE_A5, NOTE_F5, NOTE_C5, NOTE_A5, NOTE_F5, REST,
  NOTE_DS5, NOTE_B5, NOTE_G5, NOTE_DS5, NOTE_B5, NOTE_G5, REST,
  NOTE_F5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_C6, NOTE_A5, REST,
  NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_A4, REST
};
const int spooky_co_pilot_durs[] = {
  500, 250, 250, 750, 150,
  250, 250, 500, 1000, 200,
  250, 250, 500, 500, 750, 150,
  250, 250, 1000, 500, 300,
  250, 250, 250, 750, 500, 1000, 250,
  250, 250, 500, 500, 1500,
  // Durations for new spooky phrases (sum to ~30s total)
  400, 200, 200, 600, 150,
  200, 200, 400, 500, 200,
  200, 200, 400, 400, 600, 150,
  300, 400, 200, 300, 200,
  400, 200, 200, 600, 150,
  200, 200, 400, 500, 200, 200, 400, 400, 600, 150,
  300, 400, 200, 300, 200, 400, 200, 200, 600, 150,
  200, 200, 400, 500, 200, 200, 400, 400, 600, 150,
  300, 400, 200, 300, 200, 400, 200, 200, 600, 150,
  200, 200, 400, 500, 200, 200, 400, 400, 600, 150,
  300, 400, 200, 300, 200, 400, 200, 200, 600, 150,
  200, 200, 400, 500, 200, 200, 400, 400, 600, 150,
  300, 400, 200, 300, 200, 400, 200, 200, 600, 150,
  1000
};
const int SPOOKY_COPILOT_LEN = sizeof(spooky_co_pilot) / sizeof(spooky_co_pilot[0]);

void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, LOW); // Start with signal LOW
  holdState();
}

void loop() {
  // HOLD: lights off, no sound, wait for a press (active-low)
  if (digitalRead(BTN1) == LOW) {
    digitalWrite(SIGNAL_PIN, HIGH); // Signal puppetBaseLights to hold (active HIGH)
    playFor30s(LED1, upbeat_co_pilot, upbeat_co_pilot_len, UPBEAT_COPILOT_LEN);
    digitalWrite(SIGNAL_PIN, LOW);  // Release hold after playing
    holdState();
  } else if (digitalRead(BTN2) == LOW) {
    digitalWrite(SIGNAL_PIN, HIGH); // Signal puppetBaseLights to hold (active HIGH)
    playFor30s(LED2, spooky_co_pilot, spooky_co_pilot_durs, SPOOKY_COPILOT_LEN);
    digitalWrite(SIGNAL_PIN, LOW);  // Release hold after playing
    holdState();
  }
  // tiny debounce
  delay(10);
}

void holdState() {
  noTone(BUZZ);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

// Loop the given melody for ~10 seconds while LED stays on
void playFor10s(int ledPin, const int *notes, const int *durs, int len) {
  unsigned long start = millis();
  digitalWrite(ledPin, HIGH);
  while (millis() - start < 10000UL) {
    for (int i = 0; i < len && (millis() - start) < 10000UL; i++) {
      int n = notes[i];
      int d = durs[i];
      if (n == REST) {
        noTone(BUZZ);
        delay(d);
      } else {
        tone(BUZZ, n, d * 0.9); // 90% duty so we get a tiny gap
        delay(d);
      }
    }
  }
  noTone(BUZZ);
  digitalWrite(ledPin, LOW);
}

// Loop the given melody for ~30 seconds while LED stays on
void playFor30s(int ledPin, const int *notes, const int *durs, int len) {
  unsigned long start = millis();
  digitalWrite(ledPin, HIGH);
  while (millis() - start < 30000UL) {
    for (int i = 0; i < len && (millis() - start) < 30000UL; i++) {
      int n = notes[i];
      int d = durs[i];
      if (n == REST) {
        noTone(BUZZ);
        delay(d);
      } else {
        tone(BUZZ, n, d * 0.9);
        delay(d);
      }
    }
  }
  noTone(BUZZ);
  digitalWrite(ledPin, LOW);
}
