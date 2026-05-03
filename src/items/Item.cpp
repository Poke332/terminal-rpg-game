#include "../../include/items/Item.h"

Item::Item(const std::string& name, int count) : name(name), usable(count), cap(count) {}

int Item::getUsable() { return usable; }
int Item::getCapacity() { return cap; }
std::string Item::getName() { return name; }

void Item::incrementCapacity() { cap++; }
void Item::decrementUsable() { usable--; }
void Item::addUsable(int amount) { usable = std::min(cap, usable+amount); }