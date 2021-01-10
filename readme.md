# Menu System
A simple and easy to use library for creating console  with arrow navigation in c++.
## Menu class
`.addOption(Option* option)` - Used for adding any type of option that inherits from the `Option` class.

`.setTitle(std::string title)` - Used for setting the title of the menu. The title is decorated by dashes below and above and it is blue.

`.setDescription(std::string description)` - Used for setting the description of the menu. It has a blue text color as well and it is below the title.

`.setFooter` - Used for setting the footer of the menu. It appears below all options and it is blue as well.

`.display(Menu* previousMenu = nullptr)` - The method used for displaying your menu. Use it on your main menu at the end of your main function. The previousMenu parameter is used by some options and setting anything manually is *not recommended*. **Warning: This will put your program in an infinite loop and all text previously written to the console will be overwritten. (Use `.setTitle`, `.setDescription` and `.setFooter` for displaying text)**

`.exit()` - Used for exiting the display loop of a menu. Mainly used by options and using it manually is *not recommended*.
## Options
`FunctionOption (std::string label, Menu* origin, Func target, Args&... args)` - Used for execution a function when enter is pressed while it is selected. Primarily meant to be used with functions that display text, otherwise you will just get a blank screen after executing the function. Use escape to go back to the menu once done.

 - **label:** The string displayed inside the menu.
 - **origin:** Pointer to the Menu object which it is getting added to. Used for navigation.
 - **target:** The function itself.
 - **...args:** The arguments of the target function. (See main.cpp for reference)

`MenuOption (std::string label, Menu* origin, Menu* target)` - Used for navigating to the next menu. Use escape to back from there.

 - **label:** The string displayed inside the menu.
 - **origin:** Pointer to the Menu object which it is getting added to. Used for navigation.
 - **target:** Pointer to the `Menu` it is leading to. *Do not use the `new` keyword when setting this argument (Unless you want a memory leak and a not functioning option ofc)*

`ListOption (std::string label, unsigned int& index, std::vector<std::string> items)` - Used for selecting an item from a vector. Use the sideways arrows to select one.

 - **label:** The string displayed inside the menu.
 - **index:** The index of the item shown currently.
 - **items:** The vector containing the items.

`ValueOption<T> (std::string label, T& value, T minValue, T maxValue, T changeRate = 1)` - Used for changing the value of any numeric type or bool. Use the sideways arrows to change the value.

 - **label:** The string displayed inside the menu.
 - **value:** The value itself.
 - **minValue:** The minimum value that can be set using this option.
 - **maxValue:** The maximum value that can be set using this option.
 - **changeRate:** The amount it changes when using the sideways arrows once.

`ValueOption<bool> (std::string label, bool& value)` - Special type of the value option.

 - **label:** The string displayed inside the menu.
 - **value:** The bool value.
##Utilities
`setColor(int k)` - Used for setting the text color in the console. Basically the same as `SetConsoleTextAttribute`.

`showCursor(bool status)` - Used for hiding/showing the cursor in the consle.

`clearConsoleInputBuffer()` - Used for clearing all the keypresses in the console input buffer. **Always use this before using std::cin in your code, otherwise it will end up looking weird.**