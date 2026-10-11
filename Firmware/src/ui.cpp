#include "ui.h"
#include <Arduino.h>
#include "display.h"
#include "input.h"
#include "buzzer.h"
#include "storage.h"
#include "config.h"

namespace {

// ============================================================
// Главное меню
// ============================================================
struct MenuItem {
  const char* name;
  const char* icon;   // имя файла на SD без ".bin" (см. /Images)
  uint16_t    accent;
};

enum class Screen { Menu, Stub, SdBrowser, Settings, About };

const MenuItem MENU[] = {
  { "NRF24L01",   "antenna",   rgb565(0, 200, 255) },
  { "CC1101",     "signal",    rgb565(255, 120, 60) },
  { "PN532",      "rfid_chip", rgb565(170, 110, 255) },
  { "RDM6300",    "tags",      rgb565(255, 210, 60) },
  { "SD Browser", "sdcard",    rgb565(90, 160, 255) },
  { "Settings",   "setting",   rgb565(150, 160, 180) },
  { "About",      "about",     rgb565(120, 220, 160) },
};
constexpr int MENU_COUNT = sizeof(MENU) / sizeof(MENU[0]);

Screen g_screen = Screen::Menu;
int    g_sel = 0;        // выбранный пункт меню
int    g_settingsSel = 0;  // выбранная строка в Settings

Storage::Settings g_settings;

// ---------- SD Browser состояние --------------------------------
constexpr int MAX_ENTRIES = 40;
char g_entryNames[MAX_ENTRIES][64];
bool g_entryIsDir[MAX_ENTRIES];
int  g_entryCount = 0;
int  g_browserSel = 0;
char g_currentPath[160] = "/";

// ============================================================
// Общие мелкие помощники рисования
// ============================================================

void drawIconOrDot(const char* icon, int x, int y, uint16_t accent) {
  if (!Storage::drawIcon(icon, x, y, Theme::WHITE, Theme::CARD, true)) {
    // SD не готова или иконки нет - не ломаем экран, просто точка.
    tft.fillCircle(x + 8, y + 8, 5, accent);
  }
}

// ============================================================
// Главное меню
// ============================================================

void drawMenuRow(int i, bool selected) {
  const MenuItem& m = MENU[i];
  int y = 40 + i * 36;
  uint16_t bg = selected ? Theme::SELECT : Theme::CARD;

  tft.fillRoundRect(8, y, 224, 34, 6, bg);
  if (selected) tft.drawRoundRect(8, y, 224, 34, 6, m.accent);
  tft.fillRoundRect(8, y, 6, 34, 3, m.accent);

  drawIconOrDot(m.icon, 20, y + 9, m.accent);

  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(selected ? Theme::WHITE : Theme::TEXT, bg);
  tft.drawString(m.name, 44, y + 9, 2);
}

void drawMenu() {
  tft.fillScreen(Theme::BG);
  Display::drawHeader(FW_NAME);

  int segW = SCREEN_W / MENU_COUNT;
  for (int i = 0; i < MENU_COUNT; i++) {
    int w = (i == MENU_COUNT - 1) ? SCREEN_W - i * segW : segW;
    tft.fillRect(i * segW, 36, w, 3, MENU[i].accent);
  }

  for (int i = 0; i < MENU_COUNT; i++) drawMenuRow(i, i == g_sel);

  char hint[48];
  snprintf(hint, sizeof(hint), "%s   %s",
           Storage::ready() ? "SD: OK" : "SD: нет карты",
           "UP/DOWN  OK открыть");
  Display::drawFooter(hint);
}

// ============================================================
// Заглушка модуля (NRF24L01 / CC1101 / PN532 / RDM6300)
// ============================================================

void drawStub(int menuIndex) {
  const MenuItem& m = MENU[menuIndex];
  tft.fillScreen(Theme::BG);
  Display::drawHeader(m.name);
  tft.fillRect(0, 36, SCREEN_W, 3, m.accent);

  tft.fillRoundRect(8, 60, 224, 70, 6, Theme::CARD);
  drawIconOrDot(m.icon, 20, 70, m.accent);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(Theme::AMBER, Theme::CARD);
  tft.drawString("TODO", 20, 100, 2);
  tft.setTextColor(Theme::TEXT, Theme::CARD);
  tft.drawString("Driver not wired up yet", 20, 118, 1);

  Display::drawFooter("LEFT назад");
}

// ============================================================
// SD Browser
// ============================================================

void reloadBrowser() {
  g_entryCount = Storage::listDir(g_currentPath, g_entryNames, g_entryIsDir, MAX_ENTRIES);
  if (g_browserSel >= g_entryCount) g_browserSel = 0;
}

void drawBrowserRow(int i, bool selected) {
  int y = 60 + i * 26;
  uint16_t bg = selected ? Theme::SELECT : Theme::BG;
  tft.fillRect(8, y, 224, 24, bg);

  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(g_entryIsDir[i] ? Theme::ACCENT : Theme::TEXT, bg);
  char label[70];
  snprintf(label, sizeof(label), "%s%s", g_entryIsDir[i] ? "[+] " : "    ", g_entryNames[i]);
  tft.drawString(label, 14, y + 5, 2);
}

void drawBrowser() {
  tft.fillScreen(Theme::BG);
  Display::drawHeader("SD Browser");
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(Theme::DIM, Theme::BG);
  tft.drawString(g_currentPath, 12, 40, 1);

  if (!Storage::ready()) {
    tft.setTextColor(Theme::RED, Theme::BG);
    tft.drawString("Карта не найдена", 12, 70, 2);
  } else if (g_entryCount == 0) {
    tft.setTextColor(Theme::DIM, Theme::BG);
    tft.drawString("(пусто)", 12, 70, 2);
  } else {
    for (int i = 0; i < g_entryCount; i++) drawBrowserRow(i, i == g_browserSel);
  }

  Display::drawFooter("OK открыть   LEFT назад");
}

void browserOpenSelected() {
  if (g_entryCount == 0) return;
  if (!g_entryIsDir[g_browserSel]) {
    Buzzer::click();  // файлы пока не открываем в этой версии
    return;
  }
  // спускаемся в папку
  if (strcmp(g_currentPath, "/") != 0) strncat(g_currentPath, "/", sizeof(g_currentPath) - strlen(g_currentPath) - 1);
  strncat(g_currentPath, g_entryNames[g_browserSel], sizeof(g_currentPath) - strlen(g_currentPath) - 1);
  g_browserSel = 0;
  reloadBrowser();
}

bool browserGoUp() {
  if (strcmp(g_currentPath, "/") == 0) return false;  // уже в корне
  char* slash = strrchr(g_currentPath, '/');
  if (slash == g_currentPath) {
    g_currentPath[1] = '\0';  // вернулись в "/"
  } else {
    *slash = '\0';
  }
  g_browserSel = 0;
  reloadBrowser();
  return true;
}

// ============================================================
// Settings
// ============================================================

void drawSettings() {
  tft.fillScreen(Theme::BG);
  Display::drawHeader("Settings");

  for (int i = 0; i < 2; i++) {
    int y = 60 + i * 50;
    bool sel = (i == g_settingsSel);
    tft.fillRoundRect(8, y, 224, 42, 6, sel ? Theme::SELECT : Theme::CARD);

    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(Theme::TEXT, sel ? Theme::SELECT : Theme::CARD);

    if (i == 0) {
      tft.drawString("Brightness", 18, y + 6, 2);
      char buf[8];
      snprintf(buf, sizeof(buf), "%u%%", g_settings.backlightPercent);
      tft.setTextColor(Theme::ACCENT, sel ? Theme::SELECT : Theme::CARD);
      tft.drawString(buf, 18, y + 24, 2);
    } else {
      tft.drawString("Buzzer", 18, y + 6, 2);
      tft.setTextColor(g_settings.buzzerEnabled ? Theme::GREEN : Theme::DIM,
                        sel ? Theme::SELECT : Theme::CARD);
      tft.drawString(g_settings.buzzerEnabled ? "ON" : "OFF", 18, y + 24, 2);
    }
  }

  Display::drawFooter("OK изменить   LEFT назад");
}

void settingsActivate() {
  if (g_settingsSel == 0) {
    uint8_t steps[] = { 25, 50, 75, 100 };
    int idx = 0;
    for (int i = 0; i < 4; i++) if (g_settings.backlightPercent <= steps[i]) { idx = i; break; }
    idx = (idx + 1) % 4;
    g_settings.backlightPercent = steps[idx];
    Display::setBacklight(g_settings.backlightPercent);
  } else {
    g_settings.buzzerEnabled = !g_settings.buzzerEnabled;
    Buzzer::setEnabled(g_settings.buzzerEnabled);
  }
  Storage::saveSettings(g_settings);
}

// ============================================================
// About
// ============================================================

void drawAbout() {
  tft.fillScreen(Theme::BG);
  Display::drawHeader("About");
  drawIconOrDot("about", 100, 60, Theme::ACCENT);

  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(Theme::WHITE, Theme::BG);
  tft.drawString(FW_NAME, SCREEN_W / 2, 110, 4);
  tft.setTextColor(Theme::DIM, Theme::BG);
  tft.drawString(FW_VERSION, SCREEN_W / 2, 136, 2);
  tft.drawString("by Pexa6", SCREEN_W / 2, 160, 2);

  Display::drawFooter("LEFT назад");
}

// ============================================================
// Переходы между экранами
// ============================================================

void openMenuItem() {
  Buzzer::confirm();
  switch (g_sel) {
    case 4: g_screen = Screen::SdBrowser; strcpy(g_currentPath, "/"); g_browserSel = 0; reloadBrowser(); drawBrowser(); break;
    case 5: g_screen = Screen::Settings; g_settingsSel = 0; drawSettings(); break;
    case 6: g_screen = Screen::About; drawAbout(); break;
    default: g_screen = Screen::Stub; drawStub(g_sel); break;
  }
}

void backToMenu() {
  Buzzer::click();
  g_screen = Screen::Menu;
  drawMenu();
}

} // namespace

// ============================================================
// Публичный API
// ============================================================

namespace UI {

void begin() {
  g_settings = Storage::loadSettings();
  Display::setBacklight(g_settings.backlightPercent);
  Buzzer::setEnabled(g_settings.buzzerEnabled);

  // Заставка
  tft.fillScreen(Theme::BG);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(Theme::WHITE, Theme::BG);
  tft.drawString(FW_NAME, SCREEN_W / 2, 150, 4);
  tft.setTextColor(Theme::DIM, Theme::BG);
  tft.drawString("test firmware", SCREEN_W / 2, 180, 2);
  Buzzer::tone(1500, 60);
  delay(600);

  g_screen = Screen::Menu;
  drawMenu();
}

void update() {
  Btn b;
  while (Input::poll(b)) {
    switch (g_screen) {

      case Screen::Menu:
        if (b == Btn::Up || b == Btn::Down) {
          int old = g_sel;
          g_sel = (b == Btn::Down) ? (g_sel + 1) % MENU_COUNT
                                    : (g_sel + MENU_COUNT - 1) % MENU_COUNT;
          Buzzer::click();
          drawMenuRow(old, false);
          drawMenuRow(g_sel, true);
        } else if (b == Btn::Ok || b == Btn::Right) {
          openMenuItem();
        }
        break;

      case Screen::Stub:
        if (b == Btn::Left) backToMenu();
        break;

      case Screen::SdBrowser:
        if (b == Btn::Up || b == Btn::Down) {
          if (g_entryCount > 0) {
            g_browserSel = (b == Btn::Down) ? (g_browserSel + 1) % g_entryCount
                                             : (g_browserSel + g_entryCount - 1) % g_entryCount;
            Buzzer::click();
            drawBrowser();
          }
        } else if (b == Btn::Ok || b == Btn::Right) {
          browserOpenSelected();
          drawBrowser();
        } else if (b == Btn::Left) {
          if (!browserGoUp()) {
            backToMenu();
          } else {
            Buzzer::click();
            drawBrowser();
          }
        }
        break;

      case Screen::Settings:
        if (b == Btn::Up || b == Btn::Down) {
          g_settingsSel = 1 - g_settingsSel;  // всего 2 строки
          Buzzer::click();
          drawSettings();
        } else if (b == Btn::Ok || b == Btn::Right) {
          settingsActivate();
          drawSettings();
        } else if (b == Btn::Left) {
          backToMenu();
        }
        break;

      case Screen::About:
        if (b == Btn::Left) backToMenu();
        break;
    }
  }
}

} // namespace UI
