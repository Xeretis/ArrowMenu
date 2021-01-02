#ifndef MENUSYSTEM_MENUOPTIONS_H
#define MENUSYSTEM_MENUOPTIONS_H

#include <string>
#include <any>
#include <vector>

class Menu; //forward declaration because MenuSystems.h can't be included

typedef void (*voidFunctionT1)();
typedef void (*voidFunctionT2)(std::vector<std::any>);

//****parent option
class MenuOption {
public:
    //default option methods
    virtual void draw (bool isSelected);
    virtual bool update (bool isSelected); //bool indicating whether the user has left the menu or not, if true dsplay loop is exited
};
//****end of parent option

//****LinkOption
class LinkOption : public MenuOption {
public:
    //constructors
    LinkOption(std::string label, voidFunctionT1 nextFunction, Menu* thiMenu);
    LinkOption(std::string label, voidFunctionT2 nextFunction, std::vector<std::any> args, Menu* thisMenu);
    LinkOption(std::string label, Menu* nextMenu, Menu* thisMenu);

//override methods
    void draw (bool isSelected) override;
    bool update (bool isSelected) override;

private:
    //option variables
    std::string label;
    std::vector<std::any> args;

    //forward navigation
    voidFunctionT1 nextFunctionT1 = nullptr;
    voidFunctionT2 nextFunctionT2 = nullptr;
    Menu* nextMenu = nullptr;

    //backward navigation
    Menu* thisMenu;

    //private methods
    void backUpdate();
};
//****end of LinkOption

//****IntOption
class IntOption : public MenuOption {
public:
    //constructor
    IntOption(std::string label, int& variable, int minValue, int maxValue, int changeRate = 1);

    //override methods
    void draw (bool isSelected) override;
    bool update (bool isSelected) override;

private:
    //option variables
    std::string label;
    int& variable;
    int minValue;
    int maxValue;
    int changeRate;
};
//****end of IntOption

#endif