#include <windows.h>
#include <iostream>
#include <utility>

#include "MenuOptions.h"
#include "../MenuSystem.h"

//****parent class
void MenuOption::draw(bool isSelected) { }

bool MenuOption::update(bool isSelected) { return false; }
//****end of parent class

//****LinkOption
LinkOption::LinkOption(std::string label, voidFunctionT1 nextFunction, Menu* thisMenu) : label(std::move(label)), nextFunctionT1(nextFunction), thisMenu(thisMenu) { }

LinkOption::LinkOption(std::string label, Menu *nextMenu, Menu* thisMenu) : label(std::move(label)), nextMenu(nextMenu), thisMenu(thisMenu) { }

LinkOption::LinkOption(std::string label, voidFunctionT2 nextFunction, std::vector<std::any> args, Menu* thisMenu) : label(std::move(label)), nextFunctionT2(nextFunction), args(std::move(args)), thisMenu(thisMenu) { }

void LinkOption::draw(bool isSelected) {
    if (isSelected) {
        setColor(63);

        std::cout << label << "\n";

        setColor(7);
    } else
        std::cout << label << "\n";
}

bool LinkOption::update(bool isSelected) {
    if (GetAsyncKeyState(VK_RETURN) && isSelected) {
        if (nextFunctionT1 != nullptr) {
            system("cls");
            nextFunctionT1();
            backUpdate();
            return true;
        } else if (nextFunctionT2 != nullptr) {
            system("cls");
            nextFunctionT2(args);
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

//****IntOption
IntOption::IntOption(std::string label, int &variable, int minValue, int maxValue, int changeRate) : label(std::move(label)), variable(variable), minValue(minValue), maxValue(maxValue), changeRate(changeRate) {
    if (minValue > variable)
        this->minValue = variable;
    if (maxValue < variable)
        this->maxValue = variable;
}

void IntOption::draw(bool isSelected) {
    if (isSelected) {
        setColor(63);

        std::cout << label << " [" << variable << "]\n";

        setColor(7);
    } else
        std::cout << label << " [" << variable << "]\n";
}

bool IntOption::update(bool isSelected) {
    if(isSelected && (GetAsyncKeyState(VK_RIGHT) && maxValue-variable >= changeRate))
        variable += changeRate;
    if(isSelected && (GetAsyncKeyState(VK_LEFT) && variable-minValue >= changeRate))
        variable -= changeRate;
    return false;
}
//****end of IntOption

//****BoolOption
BoolOption::BoolOption(std::string label, bool &variable) : label(std::move(label)), variable(variable) { }

void BoolOption::draw(bool isSelected) {
    if (isSelected) {
        setColor(63);

        std::cout << label << " [" << std::boolalpha << variable << "]\n";

        setColor(7);
    } else
        std::cout << label << " [" << std::boolalpha << variable << "]\n";
}

bool BoolOption::update(bool isSelected) {
    if (isSelected && (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)))
        variable = !variable;
    return false;
}
//****end of BoolOption