#ifndef MENUSYSTEM_MENUOPTIONS_H
#define MENUSYSTEM_MENUOPTIONS_H

#include <string>
#include <functional>
#include <iostream>
#include <windows.h>
#include <iomanip>

#include "MenuUtils.h"

class Menu; //? Necessary forward declaration

class Option {
public:
    virtual void render(bool isSelected);
    virtual bool update();
};

class FunctionOption : public Option {
public:
    template<typename Func, typename... Args>
    FunctionOption(std::string label, Menu* origin, Func target, Args&... args) : label(std::move(label)), origin(origin), functionCall([target, &args...](){ target(args...); }) { } //? Has to be defined here due to the unholy nature of templates.

    void render(bool isSelected) override;
    bool update() override;

private:
    std::string label;
    Menu* origin;
    std::function<void()> functionCall;

    void escCheck();
};

class MenuOption : public Option {
public:
    MenuOption(std::string label, Menu* origin, Menu* target);

    void render(bool isSelected) override;
    bool update() override;

private:
    std::string label;
    Menu* origin;
    Menu* target;
};

class ListOption : public Option {
public:
    ListOption(std::string label, unsigned int& index, std::vector<std::string> items);

    void render(bool isSelected) override;
    bool update() override;

private:
    std::string label;
    unsigned int& index;
    std::vector<std::string> items;
};

template<typename T>
class ValueOption : public Option {
public:
    ValueOption(std::string label, T& value, T minValue, T maxValue, T changeRate = 1) : label(std::move(label)), value(value), minValue(minValue), maxValue(maxValue), changeRate(changeRate) { }

    void render(bool isSelected) override {
        //? check if the limits changed and adjust them
        if(minValue > value)
            minValue = value;
        else if (maxValue < value)
            maxValue = value;

        if (isSelected) {
            setColor(63);
            std::cout << label << " [" << std::fixed << std::setprecision(2) << value << "]\n";
            setColor(7);
        } else
            std::cout << label << " [" << std::fixed << std::setprecision(2) << value << "]\n";
    }

    bool update() override {
        if (GetAsyncKeyState(VK_RETURN)) { } //? Used to "catch" this keypress so it won't cause problems when switching options
        if (GetAsyncKeyState(VK_RIGHT) && value + changeRate <= maxValue) {
            value += changeRate;
            return true;
        } else if (GetAsyncKeyState(VK_LEFT) && value - changeRate >= minValue) {
            value -= changeRate;
            return true;
        } else
            return false;
    }

private:
    std::string label;
    T& value;
    T minValue;
    T maxValue;
    T changeRate;
};

template <>
class ValueOption<bool> : public Option {
public:
    ValueOption(std::string label, bool& value) : label(std::move(label)), value(value) { }

    void render(bool isSelected) override {
        if (isSelected) {
            setColor(63);
            std::cout << label << (value ? "  [" : " [") << std::boolalpha << value << "]\n";
            setColor(7);
        } else
            std::cout << label << (value ? "  [" : " [") << std::boolalpha << value << "]\n";
    }

    bool update() override {
        if (GetAsyncKeyState(VK_RETURN)) { } //? Used to "catch" this keypress so it won't cause problems when switching options
        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT)) {
            value = !value;
            return true;
        } else
            return false;
    }

private:
    std::string label;
    bool& value;
};

#endif //MENUSYSTEM_MENUOPTIONS_H