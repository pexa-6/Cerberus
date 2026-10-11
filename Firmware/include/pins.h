#pragma once
// ============================================================
// Cerberus - сводная распиновка
// Правь только этот файл, если поменяешь разводку платы -
// остальной код ссылается только на эти имена.
// ============================================================

// ---------- Дисплей (ILI9341, HSPI) --------------------------
// MISO не подключен физически (дисплею чтение не нужно).
// RESET дисплея подключен к выводу RST (EN) платы, поэтому
// в platformio.ini стоит TFT_RST=-1 и отдельный пин не нужен.
#define PIN_TFT_CS    10
#define PIN_TFT_MOSI  11
#define PIN_TFT_SCK   12
#define PIN_TFT_DC    14
#define PIN_TFT_BL    15   // подсветка, управляется PWM (ledc)

// ---------- Кнопки --------------------------------------------
#define PIN_BTN_UP     4
#define PIN_BTN_DOWN   5
#define PIN_BTN_LEFT   6
#define PIN_BTN_RIGHT  7
#define PIN_BTN_OK     8

// ---------- Общая радио/SD шина (стандартный SPI, FSPI) -------
#define PIN_BUS_SCK   16
#define PIN_BUS_MOSI  41
#define PIN_BUS_MISO  13

#define PIN_SD_CS     40

#define PIN_NRF1_CE   17
#define PIN_NRF1_CSN  48
#define PIN_NRF2_CE   21
#define PIN_NRF2_CSN  18

#define PIN_CC_CS     38
#define PIN_CC_GDO0   39

#define PIN_PN532_CS   2   // PN532 переведён на SPI, общая шина

// ---------- Прочее ---------------------------------------------
#define PIN_IR_RX     1    // VS1838B OUT (через резистор 100R на схеме)
#define PIN_RDM_RX    42   // RDM6300 TX -> вход UART1
#define PIN_IR_TX     47   // база Q1 (BC337), драйвер IR LED
#define PIN_BUZZER     9   // через резистор 100R на схеме
