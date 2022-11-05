#include "magic_show.h"
#include "windows.h"

void gotoxy(short x, short y) {
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void display_magic(const std::string &content) {
    gotoxy(0, 0);
    std::cout << content;
}