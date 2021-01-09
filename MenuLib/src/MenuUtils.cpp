#include "../include/MenuUtils.h"

#include <windows.h>

void setColor(int k) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

void showCursor(bool status) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = status;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clearConsoleInputBuffer()
{
    auto ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearingVar1,256,&ClearingVar2);
    delete[] ClearingVar1;
}