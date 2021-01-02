#ifndef MENUSYSTEM_MENUSYSTEM_H
#define MENUSYSTEM_MENUSYSTEM_H

#include <vector>

#include "Options/MenuOptions.h"

//****Menu
class Menu {
public:
    //destructor
    ~Menu();

    //public methods
    void addOption(MenuOption* newOption);
    void display(Menu* previousMenu = nullptr);
private:
    //option related variables
    std::vector<MenuOption*> options;
    int selectedOption = 0;

    //navigation related variables
    Menu* savedPreviousMenu = nullptr;

    //private methods
    void drawOptions();
};
//****end of Menu

//****uils
void clearConsoleInputBuffer();
void showCursor(bool status);
void setColor(int k);
//****end of utils

#endif