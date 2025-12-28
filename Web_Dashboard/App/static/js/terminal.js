// terminal.js
class WebTerminal {
    constructor() {
        this.history = [];
        this.historyIndex = -1;
        this.commands = {
            'help': this.showHelp.bind(this),
            'clear': this.clear.bind(this),
            'echo': this.echo.bind(this),
            'whoami': this.whoami.bind(this),
            'pwd': this.pwd.bind(this),
            'ls': this.ls.bind(this),
            'ps': this.ps.bind(this),
            'date': this.date.bind(this),
            'neofetch': this.neofetch.bind(this),
            'cerberus': this.cerberusInfo.bind(this)
        };
    }

    async execute(command) {
        this.history.push(command);
        this.historyIndex = this.history.length;

        const [cmd, ...args] = command.trim().split(' ');

        if (this.commands[cmd]) {
            return await this.commands[cmd](args);
        } else if (cmd) {
            return `Команда "${cmd}" не найдена. Введите "help" для списка команд`;
        }

        return '';
    }

    showHelp() {
        return `
Доступные команды:
• help - показать эту справку
• clear - очистить терминал
• echo [текст] - вывести текст
• whoami - показать текущего пользователя
• pwd - показать текущую директорию
• ls - список файлов
• ps - список процессов
• date - показать дату и время
• neofetch - информация о системе
• cerberus - информация о Cerberus
        `.trim();
    }

    whoami() {
        return 'pexa6';
    }

    pwd() {
        return '/home/pexa6/cerberus-control';
    }

    ls() {
        return `
drwxr-xr-x 2 pexa6 pexa6 4096 Jan 15 config/
drwxr-xr-x 3 pexa6 pexa6 4096 Jan 15 logs/
drwxr-xr-x 4 pexa6 pexa6 4096 Jan 15 modules/
-rw-r--r-- 1 pexa6 pexa6 1234 Jan 15 main.py
-rw-r--r-- 1 pexa6 pexa6  567 Jan 15 requirements.txt
        `.trim();
    }

    async ps() {
        try {
            const response = await fetch('/api/system/processes?limit=5');
            const data = await response.json();

            let output = 'PID\tИмя\t\tCPU%\tПамять%\n';
            output += '─'.repeat(40) + '\n';

            data.processes.forEach(proc => {
                output += `${proc.pid}\t${proc.name.substring(0, 12)}\t${proc.cpu_percent.toFixed(1)}\t${proc.memory_percent.toFixed(1)}\n`;
            });

            return output;
        } catch {
            return 'Не удалось получить список процессов';
        }
    }

    date() {
        return new Date().toLocaleString('ru-RU');
    }

    neofetch() {
        return `
              ▗▄▄▄       pexa6@cerberus 
              ▜███▙       ────────────── 
         ▟█████████████▙   OS: Cerberus Control v2.0
        ▟███████████████▙  Host: Security System 
▟████████████████████████  Kernel: 6.5.0-15-generic 
▜████████████████████████  Uptime: 2 hours, 15 mins 
        ▜███████████████▛  Packages: 148 (pip) 
         ▜█████████████▛   Shell: bash 5.2.15 
              ▜███▛        Terminal: Web Terminal 
              ▝▀▀▀         CPU: Intel i7-12700K 
                           Memory: 32GB DDR4 
        `.trim();
    }

    cerberusInfo() {
        return `
╔══════════════════════════════════════╗
║        CERBERUS CONTROL v2.0         ║
╠══════════════════════════════════════╣
║ • Система управления безопасностью   ║
║ • Веб-интерфейс на FastAPI           ║
║ • Мониторинг в реальном времени      ║
║ • Управление модулями                ║
║ • Терминальный доступ                ║
║ • Расширяемая архитектура            ║
╚══════════════════════════════════════╝
👤 Пользователь: pexa6
🌐 Сервер: http://127.0.0.1:8000
📊 Статус: Активен
        `.trim();
    }

    echo(args) {
        return args.join(' ');
    }

    clear() {
        return 'CLEAR'; // Специальное значение для очистки
    }
}