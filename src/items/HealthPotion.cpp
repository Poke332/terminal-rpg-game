#include "../../include/items/HealthPotion.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"
#include <iostream>

using namespace Ids;

HealthPotion::HealthPotion(int count) : Item(ItemName::health_potion, count) {}

void HealthPotion::useItem(Character& target) {
    target.heal(20.0f);
    std::cout << colorize("Healed " + target.className() + " by 20hp!", Color::GREEN) << std::endl;
}
