#include "input.h"
#include <Arduino.h>
#include "pins.h"
#include "config.h"

namespace {

constexpr int N = (int)Btn::Count;
const uint8_t PINS[N] = { PIN_BTN_UP, PIN_BTN_DOWN, PIN_BTN_LEFT, PIN_BTN_RIGHT, PIN_BTN_OK };

bool          g_state[N];      // устойчивое состояние (true = нажата)
bool          g_rawLast[N];    // последнее "сырое" чтение
unsigned long g_changedAt[N];  // когда raw последний раз менялось

// очередь только что подтверждённых НАЖАТИЙ на этот кадр poll()
bool g_pending[N];

} // namespace

namespace Input {

void begin() {
  for (int i = 0; i < N; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
    g_state[i] = false;
    g_rawLast[i] = false;
    g_changedAt[i] = 0;
    g_pending[i] = false;
  }
}

bool poll(Btn& out) {
  unsigned long now = millis();

  for (int i = 0; i < N; i++) {
    bool raw = (digitalRead(PINS[i]) == LOW);

    if (raw != g_rawLast[i]) {
      g_rawLast[i] = raw;
      g_changedAt[i] = now;
    }

    if ((now - g_changedAt[i]) > BTN_DEBOUNCE_MS && raw != g_state[i]) {
      g_state[i] = raw;
      if (raw) g_pending[i] = true;  // зафиксировали нажатие
    }
  }

  for (int i = 0; i < N; i++) {
    if (g_pending[i]) {
      g_pending[i] = false;
      out = (Btn)i;
      return true;
    }
  }
  return false;
}

bool isDown(Btn b) {
  return g_state[(int)b];
}

} // namespace Input
