#include <windows.h>
#include <iostream>

#include "MenuOptions.h"
#include "../MenuSystem.h"

//****parent class
void MenuOption::draw(bool isSelected) { }

bool MenuOption::update(bool isSelected) { return false; }
//****end of parent class

//****LinkOption
LinkOption::LinkOption(voidFunctionType nextFunction, Menu* thisMenu) : nextFunction(nextFunction), thisMenu(thisMenu) { }

LinkOption::LinkOption(Menu *nextMenu, Menu* thisMenu) : nextMenu(nextMenu), thisMenu(thisMenu) { }

void LinkOption::draw(bool isSelected) {
    if (isSelected) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);

        std::cout << "selected option" << "\n";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    } else
        std::cout << "not selected option" << "\n";
}

bool LinkOption::update(bool isSelected) {
    if (GetAsyncKeyState(VK_RETURN) && isSelected) {
        if (nextFunction != nullptr) {
            system("cls");
            nextFunction();
            backUpdate();
            return true;
        } else {
            system("cls");
            nextMenu->display(thisMenu);
            return true;
        }
    }
    return false;
}

void LinkOption::backUpdate() {
    while (true) {
        //check for escape to go back to the menu
        if(GetAsyncKeyState(VK_ESCAPE)) {
            thisMenu->display();
            break;
        }
        //remove enter from iostream to avoid unwanted actions when returning to the menu
        if(GetAsyncKeyState(VK_RETURN))
            clearConsoleInputBuffer();
    }
}
//****end of LinkOption