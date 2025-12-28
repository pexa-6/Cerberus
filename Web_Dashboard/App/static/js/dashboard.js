// Обновление времени
function updateDashboardTime() {
    const now = new Date();
    const timeString = now.toLocaleTimeString('ru-RU', {
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit'
    });

    const timeElements = document.querySelectorAll('#dashboardTime, #systemTime');
    timeElements.forEach(el => {
        if (el) el.textContent = timeString;
    });
}

// Проверка статуса API
async function checkApiStatus() {
    try {
        const response = await fetch('/api/status');
        const data = await response.json();

        alert(`✅ Сервер работает\nСтатус: ${data.status}\nВремя: ${new Date(data.timestamp).toLocaleTimeString()}`);
    } catch (error) {
        alert(`❌ Ошибка подключения к серверу: ${error.message}`);
    }
}

// Выход из системы
async function logout() {
    if (!confirm('Вы уверены, что хотите выйти?')) return;

    try {
        await fetch('/logout', { method: 'POST' });
        window.location.href = '/';
    } catch (error) {
        alert('Ошибка при выходе: ' + error.message);
    }
}

// Быстрые действия (заглушки)
function terminalQuickAccess() {
    showModal('Быстрый терминал', `
        <div class="terminal-simulator">
            <div class="terminal-header">
                <div class="terminal-title">Terminal - Quick Access</div>
                <div class="terminal-controls">
                    <span class="dot red"></span>
                    <span class="dot yellow"></span>
                    <span class="dot green"></span>
                </div>
            </div>
            <div class="terminal-body">
                <div class="terminal-output">
                    <span class="prompt">$</span> whoami<br>
                    <span class="output">pexa6</span><br><br>
                    
                    <span class="prompt">$</span> pwd<br>
                    <span class="output">/home/pexa6/cerberus</span><br><br>
                    
                    <span class="prompt">$</span> <span class="cursor">█</span>
                </div>
            </div>
        </div>
        
        <style>
            .terminal-simulator {
                background: #1a1a1a;
                border-radius: 8px;
                overflow: hidden;
                font-family: 'Courier New', monospace;
            }
            .terminal-header {
                background: #333;
                padding: 10px 15px;
                display: flex;
                justify-content: space-between;
                align-items: center;
            }
            .terminal-title {
                color: #fff;
                font-size: 0.9rem;
            }
            .terminal-controls {
                display: flex;
                gap: 8px;
            }
            .dot {
                width: 12px;
                height: 12px;
                border-radius: 50%;
            }
            .dot.red { background: #ff5f56; }
            .dot.yellow { background: #ffbd2e; }
            .dot.green { background: #27ca3f; }
            .terminal-body {
                padding: 20px;
            }
            .terminal-output {
                color: #00ff00;
                line-height: 1.5;
            }
            .prompt {
                color: #00d4ff;
                font-weight: bold;
                margin-right: 10px;
            }
            .output {
                color: #fff;
            }
            .cursor {
                animation: blink 1s infinite;
            }
            @keyframes blink {
                0%, 50% { opacity: 1; }
                51%, 100% { opacity: 0; }
            }
        </style>
    `);
}

function processMonitor() {
    showModal('Монитор процессов', `
        <div class="process-monitor">
            <div class="monitor-header">
                <h4>Системные процессы</h4>
                <button class="btn-refresh" onclick="alert('Обновление...')">
                    <i class="fas fa-sync-alt"></i>
                </button>
            </div>
            <div class="process-list">
                <div class="process-item">
                    <span class="process-name">systemd</span>
                    <span class="process-pid">PID: 1</span>
                    <span class="process-cpu">CPU: 0.1%</span>
                </div>
                <div class="process-item">
                    <span class="process-name">bash</span>
                    <span class="process-pid">PID: 1234</span>
                    <span class="process-cpu">CPU: 0.5%</span>
                </div>
                <div class="process-item">
                    <span class="process-name">python3</span>
                    <span class="process-pid">PID: 5678</span>
                    <span class="process-cpu">CPU: 15.2%</span>
                </div>
            </div>
        </div>
        
        <style>
            .process-monitor {
                background: rgba(255,255,255,0.05);
                border-radius: 10px;
                padding: 20px;
            }
            .monitor-header {
                display: flex;
                justify-content: space-between;
                align-items: center;
                margin-bottom: 20px;
            }
            .btn-refresh {
                background: rgba(0,212,255,0.2);
                color: #00d4ff;
                border: none;
                width: 40px;
                height: 40px;
                border-radius: 50%;
                cursor: pointer;
                display: flex;
                align-items: center;
                justify-content: center;
            }
            .process-list {
                display: flex;
                flex-direction: column;
                gap: 10px;
            }
            .process-item {
                display: flex;
                justify-content: space-between;
                padding: 12px;
                background: rgba(0,0,0,0.3);
                border-radius: 8px;
                border-left: 4px solid #00d4ff;
            }
            .process-name {
                font-weight: bold;
                color: #fff;
            }
            .process-pid, .process-cpu {
                color: #a0aec0;
                font-size: 0.9rem;
            }
        </style>
    `);
}

function networkStatus() {
    showModal('Статус сети', `
        <div class="network-status">
            <div class="network-stats">
                <div class="stat-card">
                    <div class="stat-icon"><i class="fas fa-wifi"></i></div>
                    <div class="stat-info">
                        <h5>Сеть</h5>
                        <p class="stat-value">Online</p>
                    </div>
                </div>
                <div class="stat-card">
                    <div class="stat-icon"><i class="fas fa-server"></i></div>
                    <div class="stat-info">
                        <h5>Сервер</h5>
                        <p class="stat-value">127.0.0.1:8000</p>
                    </div>
                </div>
            </div>
            <div class="connection-info">
                <h4>Активные соединения:</h4>
                <ul>
                    <li><i class="fas fa-check-circle"></i> HTTP: 127.0.0.1:8000</li>
                    <li><i class="fas fa-check-circle"></i> WebSocket: ws://127.0.0.1:8000</li>
                    <li><i class="fas fa-check-circle"></i> API: /api/*</li>
                </ul>
            </div>
        </div>
        
        <style>
            .network-stats {
                display: grid;
                grid-template-columns: repeat(2, 1fr);
                gap: 15px;
                margin-bottom: 30px;
            }
            .stat-card {
                background: rgba(0,212,255,0.1);
                padding: 20px;
                border-radius: 10px;
                border: 1px solid rgba(0,212,255,0.2);
                display: flex;
                align-items: center;
                gap: 15px;
            }
            .stat-icon {
                font-size: 2rem;
                color: #00d4ff;
            }
            .stat-info h5 {
                color: #a0aec0;
                margin-bottom: 5px;
            }
            .stat-value {
                color: #fff;
                font-weight: bold;
            }
            .connection-info ul {
                list-style: none;
                padding: 0;
            }
            .connection-info li {
                padding: 10px;
                background: rgba(255,255,255,0.05);
                margin-bottom: 10px;
                border-radius: 8px;
                display: flex;
                align-items: center;
                gap: 10px;
            }
            .connection-info li i {
                color: #00ff88;
            }
        </style>
    `);
}

function systemLogs() {
    showModal('Системные логи', `
        <div class="logs-viewer">
            <div class="logs-header">
                <h4>Последние записи логов</h4>
                <select class="log-filter">
                    <option>Все логи</option>
                    <option>Ошибки</option>
                    <option>Предупреждения</option>
                    <option>Информация</option>
                </select>
            </div>
            <div class="logs-content">
                <div class="log-entry info">
                    <span class="log-time">[12:30:45]</span>
                    <span class="log-message">Пользователь pexa6 вошел в систему</span>
                </div>
                <div class="log-entry success">
                    <span class="log-time">[12:31:10]</span>
                    <span class="log-message">Запущен модуль управления Linux</span>
                </div>
                <div class="log-entry warning">
                    <span class="log-time">[12:32:05]</span>
                    <span class="log-message">Попытка доступа к несуществующему модулю</span>
                </div>
            </div>
        </div>
        
        <style>
            .logs-viewer {
                background: #1a1a1a;
                border-radius: 10px;
                overflow: hidden;
                font-family: 'Courier New', monospace;
            }
            .logs-header {
                background: #333;
                padding: 15px;
                display: flex;
                justify-content: space-between;
                align-items: center;
            }
            .log-filter {
                background: #444;
                color: #fff;
                border: 1px solid #555;
                padding: 5px 10px;
                border-radius: 5px;
            }
            .logs-content {
                padding: 15px;
                max-height: 300px;
                overflow-y: auto;
            }
            .log-entry {
                padding: 10px;
                margin-bottom: 5px;
                border-radius: 5px;
                display: flex;
                gap: 15px;
            }
            .log-entry.info {
                background: rgba(0, 123, 255, 0.1);
                border-left: 4px solid #007bff;
            }
            .log-entry.success {
                background: rgba(40, 167, 69, 0.1);
                border-left: 4px solid #28a745;
            }
            .log-entry.warning {
                background: rgba(255, 193, 7, 0.1);
                border-left: 4px solid #ffc107;
            }
            .log-time {
                color: #a0aec0;
                min-width: 70px;
            }
            .log-message {
                color: #fff;
            }
        </style>
    `);
}

// Модальное окно
function showModal(title, content) {
    document.getElementById('modalTitle').textContent = title;
    document.getElementById('modalBody').innerHTML = content;
    document.getElementById('modal').classList.remove('hidden');
}

function closeModal() {
    document.getElementById('modal').classList.add('hidden');
}

// Инициализация
document.addEventListener('DOMContentLoaded', function() {
    console.log('Cerberus Dashboard loaded');

    // Обновляем время
    updateDashboardTime();
    setInterval(updateDashboardTime, 1000);

    // Закрытие модального окна по клику вне его
    document.getElementById('modal')?.addEventListener('click', function(e) {
        if (e.target === this) {
            closeModal();
        }
    });

    // Закрытие модального окна по ESC
    document.addEventListener('keydown', function(e) {
        if (e.key === 'Escape') {
            closeModal();
        }
    });
});

// Добавь в dashboard.js
class NotificationSystem {
    constructor() {
        this.container = this.createContainer();
        this.queue = [];
    }

    createContainer() {
        const div = document.createElement('div');
        div.className = 'notifications-container';
        document.body.appendChild(div);
        return div;
    }

    show(type, title, message, duration = 5000) {
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        notification.innerHTML = `
            <div class="notification-icon">
                ${this.getIcon(type)}
            </div>
            <div class="notification-content">
                <h4>${title}</h4>
                <p>${message}</p>
            </div>
            <button class="notification-close" onclick="this.parentElement.remove()">
                &times;
            </button>
        `;

        this.container.appendChild(notification);

        // Автоматическое удаление
        setTimeout(() => {
            if (notification.parentElement) {
                notification.classList.add('fade-out');
                setTimeout(() => notification.remove(), 300);
            }
        }, duration);
    }

    getIcon(type) {
        const icons = {
            success: '✅',
            error: '❌',
            warning: '⚠️',
            info: 'ℹ️',
            terminal: '🖥️',
            security: '🛡️',
            network: '🌐'
        };
        return icons[type] || icons.info;
    }
}

// Использование:
const notifications = new NotificationSystem();

// Пример уведомлений
notifications.show('success', 'Вход выполнен', 'Добро пожаловать, pexa6!');
notifications.show('info', 'Мониторинг запущен', 'Система мониторит ресурсы');
notifications.show('terminal', 'Терминал готов', 'Подключение установлено');


// В dashboard.js добавь:
function initTheme() {
    const theme = localStorage.getItem('cerberus-theme') || 'dark';
    document.documentElement.setAttribute('data-theme', theme);

    // Кнопка переключения темы
    const themeToggle = document.createElement('button');
    themeToggle.className = 'theme-toggle';
    themeToggle.innerHTML = theme === 'dark' ? '☀️' : '🌙';
    themeToggle.title = 'Сменить тему';
    themeToggle.onclick = toggleTheme;

    document.querySelector('.nav-right')?.prepend(themeToggle);
}

function toggleTheme() {
    const current = document.documentElement.getAttribute('data-theme');
    const newTheme = current === 'dark' ? 'light' : 'dark';

    document.documentElement.setAttribute('data-theme', newTheme);
    localStorage.setItem('cerberus-theme', newTheme);

    this.innerHTML = newTheme === 'dark' ? '☀️' : '🌙';

    notifications.show('info', 'Тема изменена',
        `Переключено на ${newTheme === 'dark' ? 'темную' : 'светлую'} тему`);
}

// Добавь кнопки экспорта
function addExportButtons() {
    const exportHTML = `
    <div class="export-panel">
        <h4><i class="fas fa-download"></i> Экспорт данных</h4>
        <div class="export-buttons">
            <button class="export-btn" onclick="exportJSON()">
                <i class="fas fa-code"></i> JSON
            </button>
            <button class="export-btn" onclick="exportCSV()">
                <i class="fas fa-file-csv"></i> CSV
            </button>
            <button class="export-btn" onclick="exportText()">
                <i class="fas fa-file-alt"></i> Текст
            </button>
            <button class="export-btn" onclick="copyToClipboard()">
                <i class="fas fa-copy"></i> Копировать
            </button>
        </div>
    </div>
    `;

    document.querySelector('.dashboard')?.insertAdjacentHTML('beforeend', exportHTML);
}

// Функции экспорта
async function exportJSON() {
    const data = await fetch('/api/system/stats').then(r => r.json());
    const blob = new Blob([JSON.stringify(data, null, 2)], {type: 'application/json'});
    downloadBlob(blob, 'cerberus-stats.json');
}

async function exportCSV() {
    const data = await fetch('/api/system/processes').then(r => r.json());
    let csv = 'PID,Имя,Пользователь,CPU%,Память%\n';
    data.processes.forEach(p => {
        csv += `${p.pid},${p.name},${p.username},${p.cpu_percent},${p.memory_percent}\n`;
    });

    const blob = new Blob([csv], {type: 'text/csv'});
    downloadBlob(blob, 'processes.csv');
}

function downloadBlob(blob, filename) {
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);

    notifications.show('success', 'Экспорт завершен', `Файл ${filename} скачан`);
}