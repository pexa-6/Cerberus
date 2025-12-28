// Обновление времени клиента
function updateClientTime() {
    const now = new Date();
    const timeString = now.toLocaleTimeString('ru-RU', {
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit'
    });

    const clientTimeElement = document.getElementById('clientTime');
    if (clientTimeElement) {
        clientTimeElement.textContent = timeString;
    }
}

// Проверка статуса сервера
async function checkServerStatus() {
    const resultCard = document.getElementById('statusResult');
    const resultTitle = document.getElementById('resultTitle');
    const resultIcon = document.getElementById('resultIcon');
    const resultContent = document.getElementById('resultContent');

    // Показываем карточку
    resultCard.classList.remove('hidden');

    // Показываем загрузку
    resultIcon.textContent = '⏳';
    resultTitle.textContent = 'Проверка статуса...';
    resultContent.innerHTML = '<div class="loading">Запрос отправляется...</div>';

    try {
        const response = await fetch('/api/status');
        const data = await response.json();

        // Форматируем результат
        resultIcon.textContent = '✅';
        resultTitle.textContent = 'Статус сервера';
        resultContent.innerHTML = `
            <div class="status-success">
                <div class="status-line">
                    <strong>Статус:</strong>
                    <span class="status-value online">${data.status.toUpperCase()}</span>
                </div>
                <div class="status-line">
                    <strong>Сервис:</strong>
                    <span>${data.service}</span>
                </div>
                <div class="status-line">
                    <strong>Версия:</strong>
                    <span>${data.version}</span>
                </div>
                <div class="status-line">
                    <strong>Время сервера:</strong>
                    <span>${new Date(data.timestamp).toLocaleString('ru-RU')}</span>
                </div>
                <div class="status-line">
                    <strong>Запрос:</strong>
                    <span class="timestamp">${new Date().toLocaleTimeString()}</span>
                </div>
            </div>
            
            <style>
                .status-success {
                    display: flex;
                    flex-direction: column;
                    gap: 12px;
                }
                .status-line {
                    display: flex;
                    justify-content: space-between;
                    padding: 8px 0;
                    border-bottom: 1px solid rgba(255,255,255,0.1);
                }
                .status-line:last-child {
                    border-bottom: none;
                }
                .status-value {
                    font-weight: bold;
                    padding: 4px 12px;
                    border-radius: 20px;
                }
                .status-value.online {
                    background: rgba(0, 255, 136, 0.2);
                    color: #00ff88;
                }
                .timestamp {
                    color: #00d4ff;
                    font-weight: 600;
                }
                .loading {
                    text-align: center;
                    padding: 20px;
                    color: #718096;
                }
            </style>
        `;

    } catch (error) {
        resultIcon.textContent = '❌';
        resultTitle.textContent = 'Ошибка';
        resultContent.innerHTML = `
            <div class="status-error">
                <p><strong>Не удалось подключиться к серверу</strong></p>
                <p>Ошибка: ${error.message}</p>
                <p>Убедитесь что сервер запущен по адресу:</p>
                <code>http://127.0.0.1:8000</code>
            </div>
            
            <style>
                .status-error {
                    color: #ff6b6b;
                }
                code {
                    display: block;
                    background: rgba(255, 107, 107, 0.1);
                    padding: 10px;
                    border-radius: 8px;
                    margin-top: 10px;
                    font-family: monospace;
                }
            </style>
        `;
    }
}

// Проверка времени сервера
async function checkServerTime() {
    const resultCard = document.getElementById('statusResult');
    const resultTitle = document.getElementById('resultTitle');
    const resultIcon = document.getElementById('resultIcon');
    const resultContent = document.getElementById('resultContent');

    // Показываем карточку
    resultCard.classList.remove('hidden');

    // Показываем загрузку
    resultIcon.textContent = '⏳';
    resultTitle.textContent = 'Получение времени...';
    resultContent.innerHTML = '<div class="loading">Запрос времени сервера...</div>';

    try {
        const response = await fetch('/api/time');
        const data = await response.json();

        const serverTime = new Date(data.server_time);
        const clientTime = new Date();
        const timeDiff = Math.abs(serverTime - clientTime);

        // Форматируем результат
        resultIcon.textContent = '⏰';
        resultTitle.textContent = 'Время сервера';
        resultContent.innerHTML = `
            <div class="time-info">
                <div class="time-display">
                    <div class="server-time">
                        <h4>Серверное время:</h4>
                        <div class="time-value">${data.formatted}</div>
                        <small>${serverTime.toLocaleTimeString('ru-RU', {timeZoneName: 'short'})}</small>
                    </div>
                    
                    <div class="client-time">
                        <h4>Ваше время:</h4>
                        <div class="time-value">${clientTime.toLocaleString('ru-RU')}</div>
                        <small>${clientTime.toLocaleTimeString('ru-RU', {timeZoneName: 'short'})}</small>
                    </div>
                </div>
                
                <div class="time-stats">
                    <div class="stat-item">
                        <span class="stat-label">Разница:</span>
                        <span class="stat-value">${timeDiff} мс</span>
                    </div>
                    <div class="stat-item">
                        <span class="stat-label">Часовой пояс:</span>
                        <span class="stat-value">${data.timezone}</span>
                    </div>
                    <div class="stat-item">
                        <span class="stat-label">Текущая дата:</span>
                        <span class="stat-value">${serverTime.toLocaleDateString('ru-RU', { 
                            weekday: 'long', 
                            year: 'numeric', 
                            month: 'long', 
                            day: 'numeric' 
                        })}</span>
                    </div>
                </div>
                
                <div class="time-footer">
                    <small>Запрос выполнен: ${new Date().toLocaleTimeString()}</small>
                </div>
            </div>
            
            <style>
                .time-info {
                    display: flex;
                    flex-direction: column;
                    gap: 20px;
                }
                .time-display {
                    display: grid;
                    grid-template-columns: 1fr 1fr;
                    gap: 20px;
                    margin-bottom: 20px;
                }
                .server-time, .client-time {
                    background: rgba(0, 212, 255, 0.1);
                    padding: 20px;
                    border-radius: 12px;
                    border: 1px solid rgba(0, 212, 255, 0.2);
                }
                .server-time h4, .client-time h4 {
                    color: #00d4ff;
                    margin-bottom: 10px;
                    font-size: 0.9rem;
                }
                .time-value {
                    font-size: 1.3rem;
                    font-weight: bold;
                    color: #fff;
                    margin-bottom: 5px;
                    font-family: 'Courier New', monospace;
                }
                .time-stats {
                    display: flex;
                    flex-direction: column;
                    gap: 12px;
                    background: rgba(255, 255, 255, 0.05);
                    padding: 15px;
                    border-radius: 10px;
                }
                .stat-item {
                    display: flex;
                    justify-content: space-between;
                    padding: 8px 0;
                    border-bottom: 1px solid rgba(255, 255, 255, 0.1);
                }
                .stat-item:last-child {
                    border-bottom: none;
                }
                .stat-label {
                    color: #a0aec0;
                }
                .stat-value {
                    color: #fff;
                    font-weight: 600;
                }
                .time-footer {
                    text-align: center;
                    color: #718096;
                    font-size: 0.9rem;
                    padding-top: 15px;
                    border-top: 1px solid rgba(255, 255, 255, 0.1);
                }
            </style>
        `;

    } catch (error) {
        resultIcon.textContent = '❌';
        resultTitle.textContent = 'Ошибка';
        resultContent.innerHTML = `
            <div class="time-error">
                <p><strong>Не удалось получить время сервера</strong></p>
                <p>Ошибка: ${error.message}</p>
                <p>Проверьте подключение к серверу</p>
            </div>
        `;
    }
}

// Закрытие карточки результатов
function closeResult() {
    const resultCard = document.getElementById('statusResult');
    resultCard.classList.add('hidden');
}

// Обработка формы входа
document.getElementById('loginForm')?.addEventListener('submit', async function(e) {
    e.preventDefault();

    const username = document.getElementById('username').value.trim();
    const password = document.getElementById('password').value.trim();

    if (!username || !password) {
        alert('Введите логин и пароль');
        return;
    }

    // Показываем загрузку
    const submitBtn = this.querySelector('button[type="submit"]');
    const originalText = submitBtn.innerHTML;
    submitBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Вход в систему...';
    submitBtn.disabled = true;

    try {
        // Отправляем данные на сервер
        const formData = new FormData();
        formData.append('username', username);
        formData.append('password', password);

        const response = await fetch('/login', {
            method: 'POST',
            body: formData
        });

        if (response.ok) {
            // Успешный вход - переходим на дашборд
            window.location.href = '/dashboard';
        } else {
            const error = await response.json();
            alert(`Ошибка входа: ${error.detail}`);

            // Возвращаем кнопку в исходное состояние
            submitBtn.innerHTML = originalText;
            submitBtn.disabled = false;
        }

    } catch (error) {
        alert(`Ошибка сети: ${error.message}`);

        // Возвращаем кнопку в исходное состояние
        submitBtn.innerHTML = originalText;
        submitBtn.disabled = false;
    }
});

// Инициализация
document.addEventListener('DOMContentLoaded', function() {
    console.log('Cerberus Auth System loaded');

    // Обновляем время клиента каждую секунду
    updateClientTime();
    setInterval(updateClientTime, 1000);

    // Автофокус на поле логина
    document.getElementById('username')?.focus();
});