#include "../../include/items/AttackScroll.h"
#include "../../include/stats/AddModifier.h"

#include <iostream>

AttackScroll::AttackScroll(int count) : Item("Attack Scroll", count) {}

void AttackScroll::useItem(Character& target) {
    target.modifyStat("attack", std::make_unique<AddModifier>(5.0f));
    std::cout << "Permanently increased " << target.className() << " attack stats by 5!" << std::endl;
}