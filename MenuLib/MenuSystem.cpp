#include "MenuSystem.h"

#include <windows.h>

//****Menu
Menu::~Menu() {
    for (MenuOption* option : options)
        delete option;
}

void Menu::addOption(MenuOption *newOption) {
    options.push_back(newOption);
}

void Menu::display(Menu *previousMenu) {
    //set previous menu to be accessible in the future by saving it into a data member
    if (previousMenu != nullptr)
        savedPreviousMenu = previousMenu;

    showCursor(false);

    drawOptions();

    while (true) {
        drawOptions();
        Sleep(100);
        if (GetAsyncKeyState(VK_UP) && selectedOption > 0) {
            --selectedOption;
            drawOptions();
        }
        if (GetAsyncKeyState(VK_DOWN) && selectedOption < options.size() - 1) {
            ++selectedOption;
            drawOptions();
        }
        if (GetAsyncKeyState(VK_ESCAPE) && savedPreviousMenu != nullptr) {
            savedPreviousMenu->display();
            break;
        }
        for (int i = 0; i < options.size(); ++i)
            if (options[i]->update(i == selectedOption))
                goto BREAK;
    }
    BREAK: ; //used to break out of nested loop
}

void Menu::drawOptions() {
    system("cls");
    for (int i = 0; i < options.size(); ++i)
        options[i]->draw(i == selectedOption);
}
//****end of Menu

//****utils
void clearConsoleInputBuffer()
{
    auto ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearingVar1,256,&ClearingVar2);
    delete[] ClearingVar1;
}

void showCursor(bool status) {
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = status;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setColor(int k) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}
//****end of utils