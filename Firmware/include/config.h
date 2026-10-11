#pragma once
#include <cstdint>

// ============================================================
// Cerberus - общие настройки проекта
// ============================================================

#define FW_NAME     "CERBERUS"
#define FW_VERSION  "0.1.0-test"

// ---------- Экран ------------------------------------------------
#define SCREEN_W 240
#define SCREEN_H 320

// ---------- Кнопки -------------------------------------------------
#define BTN_DEBOUNCE_MS 30UL

// ---------- Подсветка --------------------------------------------
#define BL_PWM_FREQ_HZ   5000
#define BL_PWM_RES_BITS  8
#define BL_DEFAULT_PCT   75   // 0-100, одно из значений цикла в Settings (25/50/75/100)

// ---------- Зуммер -------------------------------------------------
#define BUZZER_DEFAULT_ON true

// ---------- Пути на SD-карте ---------------------------------------
// Структура создаётся автоматически при первом старте, если её нет.
#define SD_DIR_IMAGES    "/Images"
#define SD_DIR_CONFIG    "/Config"
#define SD_DIR_NRF24     "/NRF24L01"
#define SD_DIR_CC1101    "/CC1101"
#define SD_DIR_PN532     "/PN532"
#define SD_DIR_RDM6300   "/RDM6300"
#define SD_DIR_CAPTURES  "/Captures"

#define SD_SETTINGS_FILE "/Config/settings.cfg"

// ---------- Цветовая палитра UI (RGB565) ----------------------------
// Собрана той же функцией rgb(), что и в прежнем MODULE LAB скетче,
// чтобы весь UI проекта выглядел единообразно.
constexpr uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

namespace Theme {
constexpr uint16_t BG      = rgb565(8, 12, 22);
constexpr uint16_t HEADER  = rgb565(16, 24, 44);
constexpr uint16_t CARD    = rgb565(22, 30, 50);
constexpr uint16_t SELECT  = rgb565(34, 50, 86);
constexpr uint16_t WHITE   = rgb565(255, 255, 255);
constexpr uint16_t TEXT    = rgb565(200, 210, 230);
constexpr uint16_t DIM     = rgb565(120, 134, 160);
constexpr uint16_t GREEN   = rgb565(60, 220, 120);
constexpr uint16_t RED     = rgb565(255, 80, 80);
constexpr uint16_t AMBER   = rgb565(255, 190, 40);
constexpr uint16_t ACCENT  = rgb565(80, 160, 255);
}
