#include <Arduino.h>
#include "pins.h"
#include "display.h"
#include "input.h"
#include "buzzer.h"
#include "storage.h"
#include "bus.h"
#include "ui.h"

void setup() {
  Serial.begin(115200);

  Input::begin();
  Display::begin();
  Buzzer::begin();
  radioBus_begin();

  if (!Storage::begin()) {
    Serial.println("[Storage] SD не найдена - продолжаем без карты "
                    "(иконки будут точками, настройки по умолчанию)");
  } else {
    Serial.println("[Storage] SD готова, структура папок проверена");
  }

  UI::begin();
}

void loop() {
  UI::update();
}
