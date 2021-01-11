#ifndef MENUSYSTEM_MENULIB_H
#define MENUSYSTEM_MENULIB_H

#include <vector>

#include "MenuOptions.h"

class Menu {
public:
    ~Menu();

    void addOption(Option* option);

    void setTitle(std::string menuTitle);
    void setDescription(std::string menuDescription);
    void setFooter(std::string menuFooter);

    void display(Menu* previousMenu = nullptr);
    void exit();

private:
    std::vector<Option*> options;

    std::string title;
    std::string description;
    std::string footer;

    bool exited;
    int selectedIndex = 0;
    Menu* sPreviousMenu = nullptr;

    void renderOptions();
};

#endif //MENUSYSTEM_MENULIB_H