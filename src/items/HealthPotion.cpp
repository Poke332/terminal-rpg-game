#include "../../include/items/HealthPotion.h"
#include "../../include/utils.h"
#include <iostream>

HealthPotion::HealthPotion(int count) : Item("Health Potion", count) {}

void HealthPotion::useItem(Character& target) {
    target.heal(20.0f);
    std::cout << colorize("Healed " + target.className() + " by 20hp!", Color::GREEN) << std::endl;
}
