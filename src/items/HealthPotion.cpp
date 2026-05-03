#include "../../include/items/HealthPotion.h"

#include <iostream>

HealthPotion::HealthPotion(int count) : Item("Health Potion", count) {}

void HealthPotion::useItem(Character& target) {
    target.heal(20.0f);
    std::cout << "Healed " << target.className() << " by 20hp!" << std::endl;
}