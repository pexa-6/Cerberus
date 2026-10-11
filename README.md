# 🐺 Cerberus

### Open-Source Embedded Hardware Project

**Cerberus** is a portable embedded hardware project built around the **ESP32-S3**. It combines wireless communication modules, RFID/NFC interfaces, infrared communication, a TFT display, and removable storage into a single experimental platform.

The project is developed to explore embedded systems, electronics, PCB design, firmware architecture, and low-level hardware interaction.

<p align="center">
  <strong>ESP32-S3 · Embedded Systems · Custom PCB · C/C++</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Status-In%20Development-orange?style=for-the-badge" alt="Project status">
  <img src="https://img.shields.io/badge/Platform-ESP32--S3-blue?style=for-the-badge" alt="Platform">
  <img src="https://img.shields.io/badge/PCB-KiCad-314CB0?style=for-the-badge" alt="PCB design">
  <img src="https://img.shields.io/badge/Firmware-PlatformIO-FF7F00?style=for-the-badge" alt="Firmware">
</p>

---

## 📖 Table of Contents

- [🇺🇸 English](#-english)
- [🇷🇺 Русский](#-русский)

---

# 🇺🇸 English

## ✨ Overview

Cerberus is a personal embedded systems project focused on building a portable, modular hardware platform from the ground up.

The project combines custom hardware design with firmware development. Its architecture is built around an ESP32-S3 microcontroller, with dedicated modules for wireless communication, RFID/NFC, infrared, display output, and data storage.

Cerberus is a work in progress. Hardware integration, PCB design, and firmware development are ongoing.

## ⚡ Features

- 🧠 **ESP32-S3-N16R8** — main microcontroller with 16 MB flash and 8 MB PSRAM.
- 📡 **2× NRF24L01** — 2.4 GHz wireless communication.
- 📻 **CC1101** — sub-GHz wireless transceiver.
- 🪪 **PN532** — NFC interface.
- 🏷️ **RDM6300** — RFID reader.
- 🔴 **Infrared TX/RX** — infrared signal transmission and reception.
- 🖥️ **ILI9341 TFT** — 240 × 320 display.
- 💾 **MicroSD** — removable data storage.
- 🎛️ **Physical controls** — five navigation buttons.
- 🔋 **Portable power** — rechargeable battery and power-management circuitry.
- 🔌 **USB connectivity** — development, firmware uploading, and serial debugging.
- 🔧 **Custom PCB design** — circuit design and board development in KiCad.

> Features and hardware interfaces are subject to change as development progresses.

## 🧩 Hardware

| Component | Purpose |
|---|---|
| ESP32-S3-N16R8 | Main processing unit |
| NRF24L01 × 2 | 2.4 GHz wireless communication |
| CC1101 | Sub-GHz radio communication |
| PN532 | NFC |
| RDM6300 | RFID |
| ILI9341 | TFT display |
| MicroSD | Data storage |
| IR transmitter and receiver | Infrared communication |
| Digispark ATtiny85 | Separate experimental microcontroller |
| IP5306-based power module | Battery charging and 5 V power output |

## 🛠️ Technology Stack

- **Firmware:** C/C++
- **Framework:** Arduino
- **Build system:** PlatformIO
- **PCB design:** KiCad
- **Hardware documentation:** Markdown
- **Version control:** Git

## 📂 Repository Structure

```text
Cerberus/
├── Firmware/        # Firmware source code
├── Hardware/       # Hardware-related files
├── KiCad/          # Schematics, PCB layouts and libraries
├── Documentation/  # Technical documentation
│   └── Hardware Datasheet.md
└── README.md       # Project overview
```

## 🚧 Development Status

Cerberus is currently under active development.

- [x] ESP32-S3 firmware environment
- [x] Initial hardware architecture
- [x] Initial KiCad schematic
- [x] Basic peripheral testing
- [ ] Finalize the power architecture
- [ ] Complete PCB design and verification
- [ ] Integrate and test all hardware modules
- [ ] Develop the main firmware architecture
- [ ] Implement the user interface
- [ ] Complete system-level testing

The checklist reflects the current development plan and will be updated as the project evolves.

## 📚 Documentation

Detailed hardware information is maintained separately from this overview.

- **Hardware Datasheet** — hardware architecture, connections, GPIO assignments, power distribution, components, resistors, capacitors, and design notes.

See [`Documentation/Hardware Datasheet.md`](Documentation/Hardware%20Datasheet.md).

## 🎯 Project Goals

- Develop a deeper understanding of embedded systems.
- Design and document custom electronic hardware.
- Build modular firmware with clear responsibilities.
- Learn practical PCB layout and power-distribution techniques.
- Integrate multiple hardware interfaces into one platform.
- Create a maintainable and well-documented project.

## ⚠️ Responsible Use

Cerberus is an experimental embedded systems and hardware development project. Wireless, RFID/NFC, infrared, and USB-related functionality should be tested only on devices and systems you own or are authorized to use.

## 📌 Project Status

**Work in progress — hardware and firmware are evolving.**

---

# 🇷🇺 Русский

## ✨ О проекте

**Cerberus** — мой персональный embedded-проект, целью которого является создание портативной аппаратной платформы на базе ESP32-S3.

Проект объединяет разработку собственной электроники, проектирование печатных плат и написание прошивки. В одной системе используются радиомодули, RFID/NFC, инфракрасная связь, TFT-дисплей и съёмное хранилище данных.

Cerberus разрабатывается с нуля: от принципиальной схемы и системы питания до архитектуры прошивки и пользовательского интерфейса.

## ⚡ Возможности

- 🧠 **ESP32-S3-N16R8** — основной микроконтроллер с 16 MB Flash и 8 MB PSRAM.
- 📡 **2× NRF24L01** — беспроводная связь на частоте 2,4 GHz.
- 📻 **CC1101** — радиосвязь в диапазонах ниже 1 GHz.
- 🪪 **PN532** — работа с NFC.
- 🏷️ **RDM6300** — считывание RFID.
- 🔴 **IR TX/RX** — передача и приём инфракрасных сигналов.
- 🖥️ **ILI9341 TFT** — дисплей с разрешением 240 × 320.
- 💾 **MicroSD** — съёмное хранилище данных.
- 🎛️ **Физические кнопки** — навигация по интерфейсу.
- 🔋 **Автономное питание** — аккумулятор и схема управления питанием.
- 🔌 **USB** — прошивка, подключение к компьютеру и отладка.
- 🔧 **Собственная электроника** — разработка схем и печатных плат в KiCad.

> Проект находится в разработке. Некоторые возможности ещё предстоит интегрировать и проверить в составе единой системы.

## 🧩 Аппаратная часть

| Компонент | Назначение |
|---|---|
| ESP32-S3-N16R8 | Основной микроконтроллер |
| 2× NRF24L01 | Радиосвязь 2,4 GHz |
| CC1101 | Sub-GHz радиосвязь |
| PN532 | NFC |
| RDM6300 | RFID |
| ILI9341 | TFT-дисплей |
| MicroSD | Хранение данных |
| IR TX/RX | Инфракрасная связь |
| Digispark ATtiny85 | Отдельный экспериментальный микроконтроллер |
| Модуль питания на IP5306 | Зарядка аккумулятора и формирование 5 V |

## 🛠️ Технологии

- **Прошивка:** C/C++
- **Фреймворк:** Arduino
- **Сборка:** PlatformIO
- **Проектирование электроники:** KiCad
- **Документация:** Markdown
- **Контроль версий:** Git

## 📂 Структура репозитория

```text
Cerberus/
├── Firmware/        # Исходный код прошивки
├── Hardware/       # Файлы аппаратной части
├── KiCad/          # Схемы, платы и библиотеки
├── Documentation/  # Техническая документация
│   └── Hardware Datasheet.md
└── README.md       # Описание проекта
```

## 🚧 Текущий статус разработки

Cerberus находится в активной разработке.

- [x] Настройка среды разработки ESP32-S3
- [x] Первоначальная архитектура аппаратной части
- [x] Первоначальная принципиальная схема KiCad
- [x] Базовое тестирование периферии
- [ ] Завершение архитектуры питания
- [ ] Завершение и проверка PCB
- [ ] Интеграция всех аппаратных модулей
- [ ] Разработка архитектуры прошивки
- [ ] Реализация пользовательского интерфейса
- [ ] Комплексное тестирование системы

Список будет обновляться по мере развития проекта.

## 📚 Документация

Подробное описание аппаратной части вынесено в отдельный документ.

- **Hardware Datasheet** — архитектура, распиновка GPIO, питание, компоненты, резисторы, конденсаторы и технические заметки.

Открыть: [`Documentation/Hardware Datasheet.md`](Documentation/Hardware%20Datasheet.md).

## 🎯 Цели проекта

- Углублённо изучать embedded-разработку.
- Проектировать собственные электронные устройства.
- Разрабатывать понятную и модульную прошивку.
- Освоить проектирование печатных плат и схем питания.
- Объединять различные аппаратные интерфейсы в единой системе.
- Поддерживать качественную и актуальную техническую документацию.

## ⚠️ Ответственное использование

Cerberus — экспериментальный проект по разработке embedded-систем и электроники. Проверяй функции беспроводной связи, RFID/NFC, инфракрасного интерфейса и USB только на собственных устройствах или с разрешения владельца.

## 📌 Статус проекта

**Проект находится в разработке — аппаратная часть и прошивка продолжают развиваться.**

---

<p align="center">
  <strong>🐺 Cerberus — Explore. Build. Understand.</strong>
</p>