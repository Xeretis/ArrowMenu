//
// Created by user on 1/2/2021.
//

#include "MenuSystem.h"

#include <windows.h>

Menu::~Menu() {
    for (MenuOption* option : options)
        delete option;
}

void Menu::addOption(MenuOption *newOption) {
    options.push_back(newOption);
}

void Menu::display(Menu *previousMenu) {

    if (previousMenu != nullptr)
        savedPreviousMenu = previousMenu;

    drawOptions();

    while (true) {
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
                goto Break;
    }
    Break: ;
}

void Menu::drawOptions() {
    system("cls");
    for (int i = 0; i < options.size(); ++i)
        options[i]->draw(i == selectedOption);
}
