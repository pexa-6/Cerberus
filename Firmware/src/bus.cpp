#include "bus.h"
#include "pins.h"

// FSPI - второй аппаратный SPI-контроллер S3, отдельный от HSPI,
// на котором сидит дисплей (TFT_eSPI сам поднимает HSPI внутри себя).
SPIClass radioBus(FSPI);

namespace {
bool g_started = false;
}

void radioBus_begin() {
  if (g_started) return;
  radioBus.begin(PIN_BUS_SCK, PIN_BUS_MISO, PIN_BUS_MOSI, -1 /* CS раздаёт каждое устройство само */);
  g_started = true;
}
