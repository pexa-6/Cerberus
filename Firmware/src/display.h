#pragma once
#include <TFT_eSPI.h>
#include "config.h"

// Один общий объект дисплея на весь проект.
extern TFT_eSPI tft;

namespace Display {

// Инициализация: tft.init(), ориентация, подсветка на BL_DEFAULT_PCT.
void begin();

// Яркость подсветки, 0-100%. Сохраняется только в ОЗУ -
// за сохранение на SD отвечает Storage::saveSettings().
void setBacklight(uint8_t percent);
uint8_t backlight();

// Полностью гасит/включает подсветку (для экономии батареи),
// не трогая сохранённый уровень яркости.
void sleepScreen();
void wakeScreen();

// Общие виджеты, которыми пользуются все экраны UI, чтобы
// весь интерфейс был визуально единым.
void drawHeader(const char* title);
void drawFooter(const char* hint);

} // namespace Display
