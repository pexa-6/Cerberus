
#            Cerberus README
___
##              Структура Проекта                                  Cerberus:

```                                  Python

Cerberus-Flipper
│
├── 🔧 Core_Firmware/
# Основная прошивка ESP32
│   │
│   ├── 🎮 Main_Controller/
│   │   ├── main.cpp
# Главный цикл
│   │   ├──system_manager.cpp
# Управление системой
│   │   ├── mode_switcher.cpp
# Переключение режимов
│   │   └── power_manager.cpp
# Управление питанием
│   │
│   ├── 🖥️ Display_Manager/
│   │   ├── tft_display.cpp
# Работа с TFT дисплеем
│   │   ├── ui_manager.cpp
# Управление интерфейсом
│   │   ├── menu_system.cpp
# Система меню
│   │   └── graphics_engine.cpp
# Графический движок
│   │
│   ├── 🔘 Input_Handler/
│   │   ├── button_manager.cpp
# Обработка кнопок
│   │   ├── slider_handler.cpp
# Обработка слайдеров
│   │   ├── touch_controller.cpp
# Тачскрин
│   │   └── gesture_detector.cpp
# Распознавание жестов
│   │
│   ├── ⚡ System_Services/
│   │   ├── battery_monitor.cpp
# Мониторинг батареи
│   │   ├── temperature_control.cpp
# Контроль температуры
│   │   ├── file_system.cpp
# Работа с файлами
│   │   └── rpi_communicator.cpp
# Связь с Raspberry Pi
│   │
│   ├── 📁 include/
│   │   ├── config.h
# Конфигурация проекта
│   │   ├── pins.h
# Распиновка
│   │   └── constants.h
# Константы
│   │
│   └── 🔧 platformio.ini
# Конфиг PlatformIO
│
├── 📡 Modules/
# Все модули
│   │
│   ├── 🦅 LoRa_E220/
│   │   ├── lora_mesh.cpp
# Mesh сеть
│   │   ├── long_range_chat.cpp
# Дальний чат
│   │   ├── gps_tracking.cpp
# GPS трекинг
│   │   └── emergency_beacon.cpp
# Аварийный маяк
│   │
│   ├── 📶 RF_NRF24L01/
│   │   ├── fast_file_transfer.cpp
# Быстрая передача файлов
│   │   ├── pentest_data_sync.cpp
# Синхронизация данных
│   │   ├── local_chat.cpp
# Локальный чат
│   │   └── device_scanner.cpp
# Сканер устройств
│   │
│   ├── 📻 RF_CC1101/
│   │   ├── universal_scanner.cpp
# Универсальный сканер
│   │   ├── signal_analyzer.cpp
# Анализ сигналов
│   │   ├── replay_attacks.cpp
# Атаки повторением
│   │   └── protocol_decoder.cpp
# Декодирование протоколов
│   │
│   ├── 🔘 RFID-NFC_PN532/
│   │   ├── nfc_reader.cpp
# Чтение NFC
│   │   ├── card_emulator.cpp
# Эмуляция карт
│   │   ├── data_cloner.cpp
# Клонирование данных
│   │   └── access_control.cpp
# Контроль доступа
│   │
│   ├── 📺 IR_Controller/
│   │   ├── ir_transceiver.cpp
# Прием/передача ИК
│   │   ├── remote_control.cpp
# Управление техникой
│   │   ├── signal_learning.cpp
# Обучение сигналам
│   │   └── database_manager.cpp
# База кодов пультов
│   │
│   ├── 🦆 USB_Bad/
│   │   ├── 🔑 Access_Tools/
│   │   │   ├── admin_access.ino
# Создание админа
│   │   │   ├── reverse_shell.ino
# Обратная оболочка
│   │   │   └── persistence.ino
# Установка автозапуска
│   │   │
│   │   ├️ 🦠 Shutdown_Tools/
│   │   │   ├── shutdown_windows.ino
# Выключение Windows
│   │   │   └── shutdown_linux.ino
# Выключение Linux
│   │   │
│   │   ├️ 📡 Network_Tools/
│   │   │   ├️ wifi_stealer.ino
# Кража Wi-Fi паролей
│   │   │   ├️ network_scanner.ino
# Сканирование сети
│   │   │   └️ packet_sniffer.ino
# Перехват пакетов
│   │   │
│   │   └️ 🔧 Utilities/
│   │       ├️ firmware_flasher.ino
# Прошивальщик
│   │       ├️ payload_generator.py
# Генератор payload
│   │       └️ script_converter.cpp
# Конвертер скриптов
│   │
│   └── 🔔 Buzzer/
│       ├── audio_alerts.cpp
# Звуковые оповещения
│       ├── melody_player.cpp
# Проигрыватель мелодий
│       └── morse_code.cpp
# Азбука Морзе
│
├── 🌐 Web_Dashboard/
# FastAPI веб-интерфейс
│   │
│   ├── 🎨 Frontend/
# Frontend часть FastAPI
│   │   │
│   │   ├── 🎯 main.py
# Точка входа FastAPI
│   │   │
│   │   ├── 📁 static/
# Статические файлы
│   │   │   │
│   │   │   ├── 📁 html/
│   │   │   └── index.html
# Главная страница
│   │   │   │
│   │   │   ├── 📁 css/
│   │   │   │   ├──   main.css
# Основные стили
│   │   │   │   ├── dark_theme.css
# Темная тема
│   │   │   │   └── responsive.css
# Адаптивность
│   │   │   │
│   │   │   ├── 📁 js/
│   │   │   │   ├── app.js
# Основной скрипт
│   │   │   │   ├── api.js
# Работа с API
│   │   │   │   ├── websocket.js
# WebSocket клиент
│   │   │   │   ├──  charts.js
# Графики и диаграммы
│   │   │   │   └── realtime.js
# Real-time обновления
│   │   │   │
│   │   │   ├── 📁 images/
│   │   │   │   ├──   logo.png
# Логотип Cerberus
│   │   │   │   ├── favicon.ico
# Иконка
│   │   │   │   └── background.jpg
# Фон
│   │
│   ├── ⚙️ Backend/
# Backend часть FastAPI
│   │
│   ├── 🔌 API/
# API часть FastAPI
│   │   │
│   │   ├── 📁 core/
# Ядро приложения
│   │   │   ├── config.py
# Конфигурация
│   │   │   ├── security.py
# Аутентификация
│   │   │   ├── database.py
# База данных
│   │   │   └── dependencies.py
# FastAPI зависимости
│   │   │
│   │   ├── 📁 models/
# Pydantic модели
│   │   │   ├── system_models.py
# Модели системы
│   │   │   ├── module_models.py
# Модели модулей
│   │   │   └── data_models.py
# Модели данных
│   │   │
│   │   ├── 📁 services/
# Бизнес-логика
│   │   │   ├── module_manager.py
# Управление модулями
│   │   │   ├── data_processor.py
# Обработка данных
│   │   │   ├── rpi_communicator.py
# Связь с RPi сервисами
│   │   │   └── websocket_manager.py
# Управление WebSocket
│   │   │
│   │   ├── 📁 api/
# API endpoints
│   │   │   ├── __init__.py
│   │   │   ├── system.py
# Системные endpoints
│   │   │   ├── modules.py
# Управление модулями
│   │   │   ├── data.py
# Работа с данными
│   │   │   └── websockets.py
# WebSocket handlers
│   │
│   ├── 📁 tests/
# Тесты
│   │   ├── test_api.py
# Тесты API
│   │   ├── test_services.py
# Тесты сервисов
│   │   └── conftest.py
# Конфигурация тестов
│   │
│   ├── 🔧 requirements.txt
# Зависимости Python
│   └── 🔧 startup.sh
# Скрипт запуска
│   │   │
│   │   └── 📁 utils/
# Утилиты
│   │       ├── logger.py
# Логирование
│   │       ├── validators.py
# Валидаторы
│   │       └── helpers.py
# Вспомогательные функции
│   │
├── 🛠️ Tools/
# Инструменты и утилиты
│   ├── 🐧 Kali_Scripts/
│   │   ├── network_pentest/
│   │   │   ├── wifi_attacks.sh
# Атаки на Wi-Fi
│   │   │   ├── network_scan.py
# Сканирование сети
│   │   │   └── vulnerability_scan.py
# Поиск уязвимостей
│   │   │
│   │   ├── rf_analysis/
│   │   │   ├── spectrum_analyzer.py
# Анализатор спектра
│   │   │   ├── signal_decoder.py
# Декодер сигналов
│   │   │   └── protocol_analyzer.py
# Анализатор протоколов
│   │   │
│   │   └── data_processing/
│   │       ├── log_analyzer.py
# Анализатор логов
│   │       ├── data_visualizer.py
# Визуализатор данных
│   │       └── report_generator.py
# Генератор отчетов
│   │
│   ├── 📊 Data_Analyzer/
│   │   ├── signal_processor.cpp
# Обработчик сигналов
│   │   ├── pattern_matcher.cpp
# Поиск паттернов
│   │   └── data_exporter.cpp
# Экспорт данных
│   │
│   └── 🔧 Utilities/
│       ├── firmware_updater.py
# Обновление прошивки
│       ├── config_manager.py
# Менеджер конфигураций
│       ├── backup_tool.py
# Инструмент бэкапа
│       └── diagnostic_tool.py
# Диагностика системы
│
├── 📊 Data/
# Хранение данных
│   ├── 📁 Logs/
│   │   ├── system_logs/
# Системные логи
│   │   ├── module_logs/
# Логи модулей
│   │   └── security_logs/
# Логи безопасности
│   │
│   ├── 🎯 Captures/
│   │   ├── rf_signals/
# Захваты RF сигналов
│   │   ├── network_data/
# Сетевые данные
│   │   ├── nfc_data/
# NFC данные
│   │   └── ir_codes/
# ИК коды
│   │
│   └── ⚙️ Profiles/
│       ├── user_profiles/
# Профили пользователей
│       ├── module_presets/
# Пресеты модулей
│       └── attack_scenarios/
# Сценарии атак
│
├── 📚 Docs/
# Документация
│   ├── 🔌 Pinout.md
# Полная распиновка
│   ├── 🏗️ Build_Guide.md
# Инструкция сборки
│   ├── 💻 API_Reference.md
# Документация FastAPI
│   ├── 🐛 Troubleshooting.md
# Решение проблем
│   ├── 🔒 Security_Guide.md
# Руководство безопасности
│   └── 📖 User_Manual.md
# Руководство пользователя
│
├── 🔌 Hardware/
# Схемы и корпус
│   ├── 🖨️ Case_Design/
│   │   ├── main_case.stl
# Основной корпус
│   │   ├── button_panel.stl
# Панель кнопок
│   │   ├── antenna_mount.stl
# Крепления антенн
│   │   └── assembly_guide.md
# Инструкция сборки
│   │
│   └── 🔌 Schematics/
│       ├── main_board.kicad_sch
# Основная плата
│       ├── power_circuit.kicad_sch
# Схема питания
│       ├── rf_module.kicad_sch
# RF модули
│       └── bom.csv
# Список компонентов
│
└── 📄 README.md
# Главный README
```
___
