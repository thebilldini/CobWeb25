// Required for Arduino functions and types
#include <Arduino.h>
// === Pin Assignments ===
const int BTN1 = 2;    // Button 1 (to GND, use INPUT_PULLUP)
const int BTN2 = 3;    // Button 2 (to GND, use INPUT_PULLUP)
const int LED1 = 9;    // LED for button 1
const int LED2 = 10;   // LED for button 2
const int BUZZ = 8;    // Piezo/speaker

// === Musical Notes (Hz) ===
#define REST    0
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_DS5 622
#define NOTE_FS5 740
#define NOTE_B5 988
#define NOTE_C6 1046
#define NOTE_E6 1319
#define NOTE_C7 2093
#define NOTE_E7 2637
#define NOTE_G6 1568
#define NOTE_G7 3136
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_AS6 1865

// === PAC-MAN Intro Melody ===
const int pac_notes[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_C5, NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6
};
const int pac_durs[] = {
  150, 150, 150, 150, 180, 150, 150,
  150, 150, 150, 150, 180, 150, 150
};
const int PAC_LEN = sizeof(pac_notes) / sizeof(pac_notes[0]);

// === Super Mario Bros. Overworld Melody ===
const int mario_notes[] = {
  NOTE_E7, NOTE_E7, REST, NOTE_E7, REST, NOTE_C7, NOTE_E7, REST,
  NOTE_G7, REST, NOTE_G6, REST,
  NOTE_C7, REST, NOTE_G6, REST, NOTE_E6, REST,
  NOTE_A6, REST, NOTE_B6, REST, NOTE_AS6, NOTE_A6
};
const int mario_durs[] = {
  200, 200, 120, 200, 120, 200, 200, 120,
  200, 140, 200, 140,
  200, 120, 200, 120, 240, 120,
  200, 120, 200, 120, 160, 200
};
const int MARIO_LEN = sizeof(mario_notes) / sizeof(mario_notes[0]);

void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  holdState();
}

void loop() {
  // HOLD: lights off, no sound, wait for a press (active-low)
  if (digitalRead(BTN1) == LOW) {
    playFor10s(LED1, pac_notes, pac_durs, PAC_LEN);
    holdState();
  } else if (digitalRead(BTN2) == LOW) {
    playFor10s(LED2, mario_notes, mario_durs, MARIO_LEN);
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
