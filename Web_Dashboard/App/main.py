from fastapi import FastAPI, Request, Form, HTTPException, Depends
from fastapi.responses import HTMLResponse, RedirectResponse, JSONResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.security import HTTPBasic, HTTPBasicCredentials
import secrets
from datetime import datetime, timedelta
import uvicorn
from config import USER_CREDENTIALS, SESSION_SECRET, MODULES, ActivityLogger
import psutil
import json
import platform

# Создаем приложение
app = FastAPI(
    title="Cerberus Security Control",
    description="Центр управления безопасностью",
    version="2.0.0"
)

# Настройка статики и шаблонов
app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")

# Хранилище сессий (в реальном проекте используй базу данных или Redis)
sessions = {}


# ========== АВТОРИЗАЦИЯ ==========

def create_session(username: str) -> str:
    """Создание новой сессии"""
    session_id = secrets.token_urlsafe(32)
    sessions[session_id] = {
        "username": username,
        "created": datetime.now(),
        "expires": datetime.now() + timedelta(hours=1)
    }
    return session_id


def verify_session(session_id: str) -> bool:
    """Проверка валидности сессии"""
    if session_id not in sessions:
        return False

    session = sessions[session_id]
    if datetime.now() > session["expires"]:
        del sessions[session_id]
        return False

    # Обновляем время истечения
    session["expires"] = datetime.now() + timedelta(hours=1)
    return True


def get_username_from_session(session_id: str) -> str:
    """Получить имя пользователя из сессии"""
    if session_id in sessions:
        return sessions[session_id]["username"]
    return None


# ========== МАРШРУТЫ ==========

@app.get("/", response_class=HTMLResponse)
async def login_page(request: Request):
    """Страница входа"""
    return templates.TemplateResponse("login.html", {"request": request})


@app.post("/login")
async def login(username: str = Form(...), password: str = Form(...)):
    """Обработка входа"""
    if username in USER_CREDENTIALS and USER_CREDENTIALS[username] == password:
        session_id = create_session(username)
        response = RedirectResponse(url="/dashboard", status_code=303)
        response.set_cookie(key="session_id", value=session_id, httponly=True)
        return response
    else:
        raise HTTPException(status_code=401, detail="Неверный логин или пароль")


@app.get("/dashboard", response_class=HTMLResponse)
async def dashboard_page(request: Request):
    """Панель управления"""
    session_id = request.cookies.get("session_id")

    if not session_id or not verify_session(session_id):
        return RedirectResponse(url="/")

    username = get_username_from_session(session_id)
    return templates.TemplateResponse(
        "dashboard.html",
        {
            "request": request,
            "username": username,
            "modules": MODULES
        }
    )


@app.get("/modules/{module_id}", response_class=HTMLResponse)
async def module_page(request: Request, module_id: str):
    """Страница модуля"""
    session_id = request.cookies.get("session_id")

    if not session_id or not verify_session(session_id):
        return RedirectResponse(url="/")

    if module_id not in MODULES:
        raise HTTPException(status_code=404, detail="Модуль не найден")

    return templates.TemplateResponse(
        "modules.html",
        {
            "request": request,
            "module": MODULES[module_id],
            "module_id": module_id
        }
    )


@app.post("/logout")
async def logout():
    """Выход из системы"""
    response = RedirectResponse(url="/")
    response.delete_cookie("session_id")
    return response


# ========== API ENDPOINTS ==========

@app.get("/api/status")
async def check_status():
    """Проверка статуса сервера"""
    return {
        "status": "online",
        "timestamp": datetime.now().isoformat(),
        "service": "Cerberus Control",
        "version": "2.0.0"
    }


@app.get("/api/time")
async def server_time():
    """Время сервера"""
    return {
        "server_time": datetime.now().isoformat(),
        "formatted": datetime.now().strftime("%d.%m.%Y %H:%M:%S"),
        "timezone": "UTC+2"
    }


@app.get("/api/user")
async def get_user_info(request: Request):
    """Информация о текущем пользователе"""
    session_id = request.cookies.get("session_id")

    if not session_id or not verify_session(session_id):
        raise HTTPException(status_code=401, detail="Не авторизован")

    username = get_username_from_session(session_id)
    return {
        "username": username,
        "login_time": sessions[session_id]["created"].isoformat(),
        "session_expires": sessions[session_id]["expires"].isoformat()
    }


# Заглушки для функций модулей
@app.post("/api/module/{module_id}/{function_id}")
async def execute_module_function(module_id: str, function_id: str, request: Request):
    """Выполнение функции модуля"""
    session_id = request.cookies.get("session_id")

    if not session_id or not verify_session(session_id):
        raise HTTPException(status_code=401, detail="Не авторизован")

    # Пока заглушка - возвращаем сообщение
    return {
        "status": "info",
        "message": f"Функция '{function_id}' модуля '{module_id}' пока не реализована",
        "timestamp": datetime.now().isoformat(),
        "module": module_id,
        "function": function_id
    }


activity_logger = ActivityLogger()


@app.get("/api/activity/logs")
async def get_activity_logs(limit: int = 50):
    """Получить журнал активности"""
    logs = []
    try:
        with open('activity.log', 'r', encoding='utf-8') as f:
            for line in f.readlines()[-limit:]:
                logs.append(json.loads(line.strip()))
    except FileNotFoundError:
        pass

    return {"logs": logs}


@app.get("/api/system/stats")
async def system_stats():
    """Реальная статистика системы"""
    return {
        "cpu_percent": psutil.cpu_percent(interval=1),
        "memory_percent": psutil.virtual_memory().percent,
        "disk_percent": psutil.disk_usage('/').percent,
        "boot_time": datetime.fromtimestamp(psutil.boot_time()).isoformat(),
        "os": platform.system(),
        "platform": platform.platform(),
        "process_count": len(psutil.pids()),
        "timestamp": datetime.now().isoformat()
    }


@app.get("/api/system/processes")
async def system_processes(limit: int = 20):
    """Список реальных процессов"""
    processes = []
    for proc in psutil.process_iter(['pid', 'name', 'username', 'cpu_percent', 'memory_percent']):
        try:
            processes.append(proc.info)
        except:
            continue
        if len(processes) >= limit:
            break
    return {"processes": processes}


# ========== ЗАПУСК ==========

if __name__ == "__main__":
    print("=" * 60)
    print("🔥 Cerberus Security Control System v2.0")
    print("🔑 Логин: pexa6 | Пароль: 1055")
    print("🌐 Веб-интерфейс: http://127.0.0.1:8000")
    print("📊 Панель управления: http://127.0.0.1:8000/dashboard")
    print("=" * 60)

    uvicorn.run(
        "main:app",
        host="127.0.0.1",
        port=8000,
        reload=True
    )