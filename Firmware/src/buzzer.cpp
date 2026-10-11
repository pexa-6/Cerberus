#include "buzzer.h"
#include <Arduino.h>
#include "pins.h"
#include "config.h"

namespace {
bool g_enabled = BUZZER_DEFAULT_ON;
constexpr uint8_t BUZZER_CHANNEL = 0;
}

namespace Buzzer {

void begin() {
  // Зуммер через LEDC (та же подсистема, что уже используется для
  // подсветки дисплея) вместо tone()/noTone(): в ядре arduino-esp32
  // 3.x это более надёжный путь, ledcWriteTone сам держит скважность
  // около 50% на любой заданной частоте.
  ledcSetup(BUZZER_CHANNEL, 2000, 10);
  ledcAttachPin(PIN_BUZZER, BUZZER_CHANNEL);
  ledcWrite(PIN_BUZZER, 0);
}

void setEnabled(bool on) {
  g_enabled = on;
}

bool enabled() {
  return g_enabled;
}

void tone(unsigned int freqHz, unsigned long durationMs) {
  if (!g_enabled) return;
  // Блокирующий вызов - сигналы короткие (<= ~150 мс), для тестовой
  // прошивки этого достаточно. При желании позже переделать на
  // неблокирующий таймер, если UI начнёт ощутимо подтормаживать.
  ledcWriteTone(PIN_BUZZER, freqHz);
  delay(durationMs);
  ledcWrite(PIN_BUZZER, 0);
}

void click() {
  tone(1800, 15);
}

void confirm() {
  tone(2000, 40);
  delay(30);
  tone(2600, 60);
}

void error() {
  tone(300, 150);
}

} // namespace Buzzer
