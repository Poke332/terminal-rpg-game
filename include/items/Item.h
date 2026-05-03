#pragma once

#include <string>
#include "../Character.h"

class Item {
protected:
    std::string name;
    int usable;
    int cap;
public:
    Item(const std::string& name, int count);

    int getUsable();
    int getCapacity();
    std::string getName();

    void incrementCapacity();
    void decrementUsable();
    void addUsable(int amount);

    virtual void useItem(Character& target) = 0;
};