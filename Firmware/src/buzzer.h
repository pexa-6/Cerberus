#pragma once

// Маленький пассивный зуммер на GPIO9 (через резистор 100R).
// Прямое управление с пина, без транзистора - см. гайд по железу.

namespace Buzzer {

void begin();

// Включить/выключить звук глобально (настройка хранится в Storage).
void setEnabled(bool on);
bool enabled();

// Короткие готовые сигналы для UI.
void click();   // тихий короткий щелчок при навигации по меню
void confirm();  // двойной сигнал при подтверждении (OK)
void error();    // низкий сигнал при ошибке

// Одиночный тон произвольной длительности (мс) и частоты (Гц).
void tone(unsigned int freqHz, unsigned long durationMs);

} // namespace Buzzer
