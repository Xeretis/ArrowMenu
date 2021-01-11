#include "../include/MenuOptions.h"

#include "../include/MenuLib.h"

void Option::render(bool isSelected) { }

bool Option::update() { return false; }

void FunctionOption::render(bool isSelected) {
    if (isSelected) {
        setColor(63);
        std::cout << label << "\n";
        setColor(7);
    } else
        std::cout << label << "\n";
}

bool FunctionOption::update() {
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT)) { } //? Used to "catch" these keypresses so they won't cause problems when switching options
    if (GetAsyncKeyState(VK_RETURN)) {
        origin->exit();
        showCursor(true);
        functionCall();
        escCheck();
    }
    return false;
}

void FunctionOption::escCheck() {
    while (true) {
        Sleep(100);
        if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_RETURN)) { } //? Used to "catch" these keypresses so they won't cause problems when returning to the menu
        if (GetAsyncKeyState(VK_ESCAPE)) {
            origin->display();
            return;
        }
    }
}

MenuOption::MenuOption(std::string label, Menu* origin, Menu* target) : label(std::move(label)), origin(origin), target(target) { }

void MenuOption::render(bool isSelected) {
    if (isSelected) {
        setColor(63);
        std::cout << label << "\n";
        setColor(7);
    } else
        std::cout << label << "\n";
}

bool MenuOption::update() {
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT)) { } //? Used to "catch" these keypresses so they won't cause problems when switching options
    if (GetAsyncKeyState(VK_RETURN)) {
        origin->exit();
        target->display(origin);
    }
    return false;
}

ListOption::ListOption(std::string label, unsigned int &index, std::vector<std::string> items) : label(std::move(label)), index(index), items(std::move(items)) { }

void ListOption::render(bool isSelected) {
    //? check if index went over the limit
    if (index > items.size() - 1)
        index = items.size() - 1;

    if (isSelected) {
        setColor(63);
        std::cout << label << " [" << items[index] << "]\n";
        setColor(7);
    } else
        std::cout << label << " [" << items[index] << "]\n";
}

bool ListOption::update() {
    if (GetAsyncKeyState(VK_RETURN)) { } //? Used to "catch" this keypress so it won't cause problems when switching options
    if (GetAsyncKeyState(VK_LEFT) && index > 0) {
        --index;
        return true;
    } else if (GetAsyncKeyState(VK_RIGHT) && index < items.size() - 1) {
        ++index;
        return true;
    } else
        return false;
}