// Required for Arduino functions and types
#include <Arduino.h>
#include "pitches.h"

// === Pin Assignments ===
const int BTN1 = 2;    // Button 1 (to GND, use INPUT_PULLUP)
const int BTN2 = 3;    // Button 2 (to GND, use INPUT_PULLUP)
const int LED1 = 9;    // LED for button 1
const int LED2 = 10;   // LED for button 2
const int BUZZ = 8;    // Piezo/speaker
const int SIGNAL_PIN = 4; // Pin to signal puppetBaseLights (connect to its pin 2)

// === Mashup Melody (Toccata and Fugue placeholder) ===
const int mash_notes[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, REST,
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, REST,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_F4, NOTE_D4, REST,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_F4, NOTE_D4, REST,
};
const int mash_durs[] = {
  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 8
};
const int MASH_LEN = sizeof(mash_notes) / sizeof(mash_notes[0]);

// === Tetris Theme (from robsoncouto/arduino-songs) ===
const int tetris_notes[] = {
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4,
  NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, REST,
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5,
  NOTE_A4, NOTE_A4, REST
};
const int tetris_durs[] = {
  125, 125, 250, 250, 250, 125, 250, 125,
  125, 250, 250, 250, 125, 250, 125, 125,
  250, 250, 250, 250,
  125, 125, 250, 250, 250, 125, 250, 125,
  125, 250, 250, 250, 125, 250, 125, 125,
  250, 250, 250
};
const int TETRIS_LEN = sizeof(tetris_notes) / sizeof(tetris_notes[0]);

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
    playFor30s(LED1, mash_notes, mash_durs, MASH_LEN);
    digitalWrite(SIGNAL_PIN, LOW);  // Release hold after playing
    holdState();
  } else if (digitalRead(BTN2) == LOW) {
    digitalWrite(SIGNAL_PIN, HIGH); // Signal puppetBaseLights to hold (active HIGH)
    playFor10s(LED2, tetris_notes, tetris_durs, TETRIS_LEN);
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
      int d = durs[i] * 100; // Adjust duration for tempo
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
