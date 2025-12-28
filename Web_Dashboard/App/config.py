import json
from datetime import datetime


class ActivityLogger:
    def __init__(self, log_file='activity.log'):
        self.log_file = log_file

    def log(self, username, action, details='', status='info'):
        """Логирование действия пользователя"""
        entry = {
            "timestamp": datetime.now().isoformat(),
            "username": username,
            "action": action,
            "details": details,
            "status": status
        }

        with open(self.log_file, 'a', encoding='utf-8') as f:
            f.write(json.dumps(entry, ensure_ascii=False) + '\n')

        return entry


# Конфигурация приложения
USER_CREDENTIALS = {
    "pexa6": "1055"
}

# Настройки сессии
SESSION_SECRET = "cerberus-super-secret-2024"
SESSION_TIMEOUT = 3600  # 1 час в секундах

# Настройки модулей
MODULES = {
    "linux_control": {
        "name": "🐧 Управление Linux",
        "description": "Полный контроль над Linux системой",
        "functions": [
            {"id": "terminal", "name": "🖥️ Терминал", "description": "Командная строка"},
            {"id": "processes", "name": "⚙️ Процессы", "description": "Управление процессами"},
            {"id": "services", "name": "🔧 Сервисы", "description": "Управление сервисами"},
            {"id": "files", "name": "📁 Файлы", "description": "Файловый менеджер"},
            {"id": "network", "name": "🌐 Сеть", "description": "Сетевые настройки"},
            {"id": "users", "name": "👤 Пользователи", "description": "Управление пользователями"},
            {"id": "firewall", "name": "🔥 Фаервол", "description": "Настройки firewall"},
            {"id": "logs", "name": "📝 Логи", "description": "Просмотр логов системы"}
        ]
    },
    "modules_control": {
        "name": "🎛️ Управление модулями",
        "description": "Централизованное управление всеми модулями Cerberus",
        "functions": [
            {"id": "security", "name": "🛡️ Безопасность", "description": "Модуль безопасности"},
            {"id": "monitoring", "name": "📊 Мониторинг", "description": "Мониторинг системы"},
            {"id": "network_scan", "name": "🔍 Сканирование сети", "description": "Сетевой сканер"},
            {"id": "backup", "name": "💾 Резервное копирование", "description": "Backup системы"},
            {"id": "alerts", "name": "⚠️ Оповещения", "description": "Система уведомлений"},
            {"id": "reports", "name": "📈 Отчеты", "description": "Генерация отчетов"},
            {"id": "automation", "name": "🤖 Автоматизация", "description": "Автоматические задачи"},
            {"id": "settings", "name": "⚙️ Настройки", "description": "Настройки Cerberus"}
        ]
    }
}