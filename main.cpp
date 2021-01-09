#include "MenuLib.h"

void getNumbers(int& a, int& b, bool& hasNumbers) {

    clearConsoleInputBuffer();

    setColor(3);
    std::cout << "First number: ";
    std::cin >> a;

    system("cls");

    std::cout << "Second number: ";
    std::cin >> b;

    system("cls");

    if (GetAsyncKeyState(VK_ESCAPE)) { } //? Catch wild escapes to make sure the next cout gets displayed before exiting

    std::cout << "You can exit now.";
    setColor(7);
    hasNumbers = true;
}

void multiplyNumbers(int a, int b, bool hasNumbers) {
    setColor(3);
    if (hasNumbers)
        std::cout << "The result is: " << a * b;
    else
        std::cout << "You have to give some numbers first.";
    setColor(7);
}

void showItem(int index, std::vector<std::string> items) {
    setColor(3);
    std::cout << "You have " << items[index] << " selected.";
    setColor(7);
}

void showValues(int a, double b, bool c) {
    setColor(3);
    std::cout << "The int is " << a << ", the double is " << b << " and the bool is " << std::boolalpha << c;
    setColor(7);
}

int main() {

    SetConsoleTitle("Demo app");

    Menu mainMenu;
    Menu firstScreen;
    Menu fOption;
    Menu mOption;
    Menu lOption;
    Menu vOption;

    mainMenu.setTitle("  Welcome to the demo app  ");
    mainMenu.setDescription("  This demo will show you\nthe features of the library\n");

    mainMenu.addOption(new MenuOption ("   Continue(Press Enter)   ", &mainMenu, &firstScreen));

    firstScreen.setTitle("  The navigation controls  ");
    firstScreen.setFooter("\nUse the up and down arrow\nkeys to switch between\noptions and use escape to\ngo back");

    firstScreen.addOption(new MenuOption("\n         Next page         ", &firstScreen, &fOption));
    firstScreen.addOption(new MenuOption("         Next page         ", &firstScreen, &fOption));

    fOption.setTitle("   #1 The FunctionOption   ");
    fOption.setDescription("The FunctionOption\nexecutes a given function.\nThe function can return\nanything and it can have\nany amount of arguments\n");
    fOption.setFooter("\nChose the first option to\nset two numbers and\ncome back with escape.\nChose the second option\nto multiply them with\neach other");

    int a, b;
    bool hasNumbers;

    fOption.addOption(new FunctionOption("       Input numbers       ", &fOption, getNumbers, a, b, hasNumbers));
    fOption.addOption(new FunctionOption("   Do the multiplication   ", &fOption, multiplyNumbers, a, b, hasNumbers));
    fOption.addOption(new MenuOption("         Next page         ", &fOption, &mOption));

    mOption.setTitle("     #2 The MenuOption     ");
    mOption.setDescription("The MenuOption takes you to\nan other page when you\npress enter just like all\nthese next page options\nbefore\n");

    mOption.addOption(new MenuOption("         Next page         ", &mOption, &lOption));

    lOption.setTitle("     #3 The ListOption     ");
    lOption.setDescription("The ListOption allows you\nto chose between a vector\nof strings\n");
    lOption.setFooter("\nUse the sideways arrows to\nselect an item. There is a\nFunctionOption telling you\nwich one you selected");

    int index = 0;
    std::vector<std::string> items = {"item1", "item2", "item3"};

    lOption.addOption(new ListOption("Select an item     ", index, items));
    lOption.addOption(new FunctionOption("       Selected item       ", &lOption, showItem, index, items));
    lOption.addOption(new MenuOption("         Next page         ", &lOption, &vOption));

    vOption.setTitle("  Finally The ValueOption  ");
    vOption.setDescription("The ValueOption is the most\n\"diverse\" option of them\nall. It allows you to\nchange the value of any\nnumeric type or a bool\n");
    vOption.setFooter("\nUse the sideways arrows to\nchange the values");

    int intValue = 1;
    double doubleValue = 1.0;
    bool boolValue = true;

    vOption.addOption(new ValueOption<int>("Int                    ", intValue, 0, 10));
    vOption.addOption(new ValueOption<double>("Double              ", doubleValue, 0.0, 10.0, 0.25));
    vOption.addOption(new ValueOption<bool>("Bool               ", boolValue));
    vOption.addOption(new FunctionOption("        Show values        ", &vOption, showValues, intValue, doubleValue, boolValue));

    mainMenu.display();
    return 0;
}