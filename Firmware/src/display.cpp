#include "display.h"
#include "pins.h"

TFT_eSPI tft = TFT_eSPI();

namespace {
uint8_t g_backlightPercent = BL_DEFAULT_PCT;
constexpr uint8_t BL_PWM_CHANNEL = 1;
const int BL_CHANNEL_PIN = PIN_TFT_BL;  // ledcAttach работает по номеру пина (core 3.x)
}

namespace Display {

void begin() {
  tft.init();
  tft.setRotation(0);  // 0 = портрет 240x320, под кнопки UP/DOWN/LEFT/RIGHT/OK
  tft.fillScreen(Theme::BG);

  ledcSetup(BL_PWM_CHANNEL, BL_PWM_FREQ_HZ, BL_PWM_RES_BITS);
  ledcAttachPin(BL_CHANNEL_PIN, BL_PWM_CHANNEL);
  setBacklight(g_backlightPercent);
}

void setBacklight(uint8_t percent) {
  if (percent > 100) percent = 100;
  g_backlightPercent = percent;
  uint32_t duty = (uint32_t)((1 << BL_PWM_RES_BITS) - 1) * percent / 100;
  ledcWrite(BL_CHANNEL_PIN, duty);
}

uint8_t backlight() {
  return g_backlightPercent;
}

void sleepScreen() {
  ledcWrite(BL_CHANNEL_PIN, 0);
}

void wakeScreen() {
  setBacklight(g_backlightPercent);
}

void drawHeader(const char* title) {
  tft.fillRect(0, 0, SCREEN_W, 36, Theme::HEADER);
  tft.setTextDatum(ML_DATUM);
  tft.setTextColor(Theme::WHITE, Theme::HEADER);
  tft.drawString(title, 12, 18, 4);
}

void drawFooter(const char* hint) {
  tft.fillRect(0, SCREEN_H - 24, SCREEN_W, 24, Theme::HEADER);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(Theme::DIM, Theme::HEADER);
  tft.drawString(hint, SCREEN_W / 2, SCREEN_H - 12, 2);
}

} // namespace Display
