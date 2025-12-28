# Создай папку modules/ и файл:
# modules/__init__.py

class Module:
    def __init__(self, name, description, version="1.0.0"):
        self.name = name
        self.description = description
        self.version = version
        self.functions = []

    def register_function(self, name, handler, description=""):
        self.functions.append({
            "name": name,
            "handler": handler,
            "description": description
        })

    def to_dict(self):
        return {
            "name": self.name,
            "description": self.description,
            "version": self.version,
            "functions": [f["name"] for f in self.functions]
        }


# Пример модуля
security_module = Module("Безопасность", "Модуль мониторинга безопасности")
security_module.register_function("scan_processes", lambda: "Сканирование процессов...")
security_module.register_function("check_network", lambda: "Проверка сети...")