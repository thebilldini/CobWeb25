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

// === Imperial March Melody ===
const int imperial_notes[] = {
  NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
  REST, NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_FS5,
  REST, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_C5,
  REST, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
  REST
};
const int imperial_durs[] = {
  550, 550, 550, 385, 165, 550, 385, 165,
  550, 385, 165, 550, 385, 165, 550, 385, 165,
  550, 550, 550, 550, 385, 165, 550, 385, 165,
  550, 275, 550, 275, 550, 138, 138, 275,
  275, 275, 550, 275, 550, 275,
  1100
};
const int IMPERIAL_LEN = sizeof(imperial_notes) / sizeof(imperial_notes[0]);

// === New Toccata Melody ===
const int toccataMel[] = {
  NOTE_A5, NOTE_G6, NOTE_A5, REST,
  NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_CS6, REST, NOTE_D6, REST,
  NOTE_A4, NOTE_G5, NOTE_A4, REST,
  NOTE_E4, REST, NOTE_F4, REST,
  NOTE_CS5, REST, NOTE_D5, REST,
  NOTE_A3, NOTE_G4, NOTE_A3, REST,
  NOTE_G3, NOTE_F3, NOTE_E3, NOTE_D3,
  NOTE_CS4, REST, NOTE_D4, REST,
  NOTE_D3, NOTE_D3, NOTE_AS3, REST,
  NOTE_CS4, REST, NOTE_D4, REST,
  NOTE_E4, REST, NOTE_E4, REST,
  NOTE_E4, NOTE_E4, REST, NOTE_D4,
  REST, NOTE_E4, REST, NOTE_FS4,
  REST, REST, NOTE_CS6, REST,
  NOTE_D6, REST, NOTE_E6, REST,
  NOTE_CS6, REST, NOTE_D6, REST,
  NOTE_E6, REST, NOTE_CS6, REST,
  NOTE_D6, REST, NOTE_E6, REST,
  NOTE_CS6, REST, NOTE_D6, REST,
  NOTE_E6, REST, NOTE_F6, REST,
  NOTE_G6, REST, NOTE_E6, REST,
  NOTE_F6, REST, NOTE_G6, REST,
  NOTE_E6, REST, NOTE_F6, REST,
  NOTE_G6, REST, NOTE_E6, REST,
  NOTE_F6, REST, NOTE_G6, REST,
  NOTE_A6, REST, NOTE_AS6, REST,
  NOTE_G6, REST, NOTE_A6, REST,
  NOTE_AS6, REST, NOTE_G6, REST,
  NOTE_A6, REST, NOTE_AS6, REST,
  NOTE_G6, REST, NOTE_A6, REST,
  NOTE_AS6, REST, NOTE_G6, REST,
  NOTE_A6, REST, NOTE_G6, REST,
  NOTE_A6, REST, NOTE_A7, REST,
  NOTE_G5, REST, NOTE_AS5, REST,
  NOTE_E6, REST, NOTE_G5, REST,
  NOTE_AS5, REST, NOTE_E6, REST,
  NOTE_F5, REST, NOTE_A5, REST,
  NOTE_D6, REST, NOTE_F5, REST,
  NOTE_A5, REST, NOTE_D6, REST,
  NOTE_E5, REST, NOTE_G5, REST,
  NOTE_C6, REST, NOTE_E5, REST,
  NOTE_G5, REST, NOTE_C6, REST,
  NOTE_D5, REST, NOTE_F5, REST,
  NOTE_AS5, REST, NOTE_D5, REST,
  NOTE_F5, REST, NOTE_AS5, REST,
  NOTE_C5, REST, NOTE_E5, REST,
  NOTE_A5, REST, NOTE_C5, REST,
  NOTE_E5, REST, NOTE_A5, REST,
  NOTE_AS4, REST, NOTE_D5, REST,
  NOTE_G5, REST, NOTE_AS4, REST,
  NOTE_D5, REST, NOTE_G5, REST,
  NOTE_A4, REST, NOTE_C5, REST,
  NOTE_F5, REST, NOTE_A4, REST,
  NOTE_C5, REST, NOTE_F5, REST,
  NOTE_G4, REST, NOTE_AS4, REST,
  NOTE_E5, REST, NOTE_G4, REST,
  NOTE_AS4, REST, NOTE_E5, REST,
  NOTE_F4, REST, NOTE_A4, REST,
  NOTE_D5, REST, NOTE_F4, REST
};
const int toccataLen[] = {
  180, 180, 384, 492,
  180, 180, 180, 180,
  348, 36, 696, 144,
  180, 180, 384, 492,
  348, 36, 348, 36,
  348, 36, 696, 2376,
  180, 180, 384, 492,
  180, 180, 180, 24,
  348, 36, 696, 2376,
  3060, 12, 2772, 300,
  2772, 300, 2472, 600,
  2772, 300, 2772, 300,
  3060, 2784, 300, 696,
  72, 696, 72, 2928,
  3060, 156, 696, 72,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 384, 384,
  384, 384, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  384, 384, 384, 384,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 264, 252,
  384, 3060, 3060, 408,
  696, 72, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  384, 384, 384, 384,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 384, 3060,
  3060, 408, 696, 72,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 384, 384,
  384, 384, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  384, 384, 384, 384,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 384, 3060,
  3060, 408, 696, 72,
  456, 48, 468, 48,
  468, 48, 456, 48,
  468, 48, 468, 48,
  456, 48, 468, 48,
  468, 48, 384, 384
};
const int TOCCATA_LEN = sizeof(toccataMel) / sizeof(toccataMel[0]);

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
    playFor30s(LED1, toccataMel, toccataLen, TOCCATA_LEN);
    digitalWrite(SIGNAL_PIN, LOW);  // Release hold after playing
    holdState();
  } else if (digitalRead(BTN2) == LOW) {
    digitalWrite(SIGNAL_PIN, HIGH); // Signal puppetBaseLights to hold (active HIGH)
    playFor10s(LED2, imperial_notes, imperial_durs, IMPERIAL_LEN);
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
