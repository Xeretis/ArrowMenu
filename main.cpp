#include <iostream>
#include "MenuLib/MenuSystem.h"

void test1 () {
    std::cout << "test1\n";
}

int main() {
    Menu test;
    Menu test2;

    test.addOption(new LinkOption (test1, &test));
    test.addOption(new LinkOption (&test2, &test));

    test2.addOption(new LinkOption (test1, &test2));

    test.display();
    return 0;
}
