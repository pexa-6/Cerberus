#pragma once
#include <cstdint>
#include <SD.h>
#include "display.h"

namespace Storage {

// Инициализирует SD на общей шине (SCK16/MOSI41/MISO13, CS40, та же
// шина что NRF24 x2, CC1101, PN532). Создаёт недостающие папки
// (Images, Config, NRF24L01, CC1101, PN532, RDM6300, Captures),
// если SD-карта новая или папок ещё нет.
// Возвращает true, если карта определилась и готова к работе.
bool begin();

// true, если begin() в своё время прошёл успешно. UI должен
// проверять это перед любой операцией с файлами и показывать
// "No SD card", а не зависать/падать.
bool ready();

// --- Иконки -----------------------------------------------------
// Грузит иконку "/Images/<name>.bin" (см. tools/convert_icons.py)
// и рисует её 1-битные пиксели по адресу (x, y): fg - цвет "включенных"
// пикселей, bg - цвет фона (игнорируется, если transparent=true и
// тогда фоновые пиксели просто не трогаются, оставляя то, что уже
// нарисовано под иконкой).
// Возвращает false, если файла нет или SD не готова - в этом случае
// вызывающий код сам решает, чем заменить иконку (например, точкой
// нужного цвета), экран при этом не портится.
bool drawIcon(const char* name, int x, int y, uint16_t fg, uint16_t bg, bool transparent);

// --- Настройки ----------------------------------------------------
struct Settings {
  uint8_t backlightPercent;
  bool    buzzerEnabled;
};

// Загружает /Config/settings.cfg. Если файла нет или SD не готова,
// возвращает значения по умолчанию из config.h - UI продолжает
// работать и без SD-карты.
Settings loadSettings();

// Перезаписывает /Config/settings.cfg. Без эффекта, если SD не готова.
void saveSettings(const Settings& s);

// --- Простой просмотр файлов --------------------------------------
// Возвращает имена файлов/папок в 'dirPath' (без полного пути),
// максимум maxCount штук, через outIsDir[i] сообщает, папка это или
// файл. Возвращает реальное количество найденных записей.
int listDir(const char* dirPath, char outNames[][64], bool outIsDir[], int maxCount);

} // namespace Storage
