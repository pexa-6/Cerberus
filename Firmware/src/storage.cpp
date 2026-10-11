#include "storage.h"
#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "bus.h"

namespace {

bool g_ready = false;

// Папки, которые должны существовать на SD-карте. Создаются сами
// при первом старте, если их ещё нет - руками на карте ничего
// готовить не нужно, кроме самих иконок (см. README проекта).
const char* const REQUIRED_DIRS[] = {
  SD_DIR_IMAGES, SD_DIR_CONFIG, SD_DIR_NRF24,
  SD_DIR_CC1101, SD_DIR_PN532, SD_DIR_RDM6300, SD_DIR_CAPTURES,
};
constexpr int REQUIRED_DIRS_COUNT = sizeof(REQUIRED_DIRS) / sizeof(REQUIRED_DIRS[0]);

void ensureFolderStructure() {
  for (int i = 0; i < REQUIRED_DIRS_COUNT; i++) {
    if (!SD.exists(REQUIRED_DIRS[i])) {
      SD.mkdir(REQUIRED_DIRS[i]);
    }
  }
}

} // namespace

namespace Storage {

bool begin() {
  radioBus_begin();

  // 4 МГц - надёжная стартовая скорость для SD на общей шине;
  // библиотека сама поднимет скорость после инициализации карты.
  if (!SD.begin(PIN_SD_CS, radioBus, 4000000)) {
    g_ready = false;
    return false;
  }

  if (SD.cardType() == CARD_NONE) {
    g_ready = false;
    return false;
  }

  ensureFolderStructure();
  g_ready = true;
  return true;
}

bool ready() {
  return g_ready;
}

bool drawIcon(const char* name, int x, int y, uint16_t fg, uint16_t bg, bool transparent) {
  if (!g_ready) return false;

  char path[80];
  snprintf(path, sizeof(path), "%s/%s.bin", SD_DIR_IMAGES, name);

  File f = SD.open(path, FILE_READ);
  if (!f) return false;

  uint8_t header[4];
  if (f.read(header, 4) != 4) {
    f.close();
    return false;
  }
  int w = header[0] | (header[1] << 8);
  int h = header[2] | (header[3] << 8);

  // Защита от повреждённого/неожиданного файла - иконки у нас 16x16.
  if (w <= 0 || h <= 0 || w > 64 || h > 64) {
    f.close();
    return false;
  }

  int rowBytes = (w + 7) / 8;
  uint8_t rowBuf[8];  // хватает на w<=64 (64/8=8 байт на строку)

  for (int row = 0; row < h; row++) {
    if (f.read(rowBuf, rowBytes) != rowBytes) {
      f.close();
      return false;
    }
    for (int col = 0; col < w; col++) {
      uint8_t byte = rowBuf[col / 8];
      bool on = (byte >> (7 - (col % 8))) & 0x01;
      if (on) {
        tft.drawPixel(x + col, y + row, fg);
      } else if (!transparent) {
        tft.drawPixel(x + col, y + row, bg);
      }
    }
  }

  f.close();
  return true;
}

Settings loadSettings() {
  Settings s;
  s.backlightPercent = BL_DEFAULT_PCT;
  s.buzzerEnabled = BUZZER_DEFAULT_ON;

  if (!g_ready) return s;

  File f = SD.open(SD_SETTINGS_FILE, FILE_READ);
  if (!f) return s;  // файла ещё нет - значит дефолты, это нормально

  while (f.available()) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (line.length() == 0 || line.startsWith("#")) continue;

    int eq = line.indexOf('=');
    if (eq < 0) continue;

    String key = line.substring(0, eq);
    String val = line.substring(eq + 1);
    key.trim();
    val.trim();

    if (key == "backlight") {
      int v = val.toInt();
      if (v >= 0 && v <= 100) s.backlightPercent = (uint8_t)v;
    } else if (key == "buzzer") {
      s.buzzerEnabled = (val == "1" || val == "true");
    }
  }

  f.close();
  return s;
}

void saveSettings(const Settings& s) {
  if (!g_ready) return;

  File f = SD.open(SD_SETTINGS_FILE, FILE_WRITE);
  if (!f) return;

  f.printf("backlight=%u\n", (unsigned)s.backlightPercent);
  f.printf("buzzer=%d\n", s.buzzerEnabled ? 1 : 0);

  f.close();
}

int listDir(const char* dirPath, char outNames[][64], bool outIsDir[], int maxCount) {
  if (!g_ready) return 0;

  File dir = SD.open(dirPath);
  if (!dir || !dir.isDirectory()) {
    if (dir) dir.close();
    return 0;
  }

  int count = 0;
  File entry = dir.openNextFile();
  while (entry && count < maxCount) {
    const char* n = entry.name();
    // SD.open на ESP32 иногда отдаёт полный путь в name() - берём
    // только последний сегмент, чтобы в UI не было длинных путей.
    const char* slash = strrchr(n, '/');
    const char* base = slash ? slash + 1 : n;

    strncpy(outNames[count], base, 63);
    outNames[count][63] = '\0';
    outIsDir[count] = entry.isDirectory();

    count++;
    entry.close();
    entry = dir.openNextFile();
  }
  if (entry) entry.close();
  dir.close();

  return count;
}

} // namespace Storage
