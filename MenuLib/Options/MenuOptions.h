#ifndef MENUSYSTEM_MENUOPTIONS_H
#define MENUSYSTEM_MENUOPTIONS_H

class Menu; //forward declaration because MenuSystems.h can't be included

typedef void (*voidFunctionType)();

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
    explicit LinkOption(voidFunctionType nextFunction, Menu* thiMenu);
    explicit LinkOption(Menu* nextMenu, Menu* thisMenu);

    //override methods
    void draw (bool isSelected) override;
    bool update (bool isSelected) override;

private:
    //forward navigation
    voidFunctionType nextFunction = nullptr;
    Menu* nextMenu = nullptr;

    //backward navigation
    Menu* thisMenu;

    //private methods
    void backUpdate();
    static void clearConsoleInputBuffer();
};
//****end of LinkOption

#endif
