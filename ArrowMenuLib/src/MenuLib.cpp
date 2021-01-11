#include "../include/MenuLib.h"

#include <windows.h>

Menu::~Menu() {
    for (Option* option : options)
        delete option;
}

void Menu::addOption(Option* option) {
    options.push_back(option);
}

void Menu::setTitle(std::string menuTitle) {
    title = std::move(menuTitle);
}

void Menu::setDescription(std::string menuDescription) {
    description = std::move(menuDescription);
}

void Menu::setFooter(std::string menuFooter) {
    footer = std::move(menuFooter);
}


void Menu::display(Menu* previousMenu) {
    exited = false;

    if (previousMenu != nullptr)
        sPreviousMenu = previousMenu;

    showCursor(false);
    renderOptions();

    while (true) {
        Sleep(100);
        if (GetAsyncKeyState(VK_UP) && selectedIndex > 0) {
            --selectedIndex;
            renderOptions();
        }
        if (GetAsyncKeyState(VK_DOWN) && selectedIndex < options.size() - 1) {
            ++selectedIndex;
            renderOptions();
        }
        if (GetAsyncKeyState(VK_ESCAPE) && sPreviousMenu != nullptr) {
            sPreviousMenu->display();
            break;
        }
        if (options[selectedIndex]->update())
            renderOptions();
        if (exited) break;
    }
}

void Menu::renderOptions() {
    system("cls");

    if (!title.empty()) {
        setColor(3);
        for (int i = 0; i < title.length(); ++i) {
            std::cout << "-";
        }
        std::cout << "\n";

        std::cout << title <<  "\n";

        for (int i = 0; i < title.length(); ++i) {
            std::cout << "-";
        }
        std::cout << "\n";
        setColor(7);
    }

    if (!description.empty()) {
        setColor(3);

        std::cout << description << "\n";

        setColor(7);
    }

    for (int i = 0; i < options.size(); ++i)
        options[i]->render(i == selectedIndex);

    if (!footer.empty()) {
        setColor(3);

        std::cout << footer;

        setColor(7);
    }
}

void Menu::exit() {
    system("cls");
    exited = true;
}