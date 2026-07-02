#include "../../include/items/AttackScroll.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>

AttackScroll::AttackScroll(int count) : Item("Attack Scroll", count) {}

void AttackScroll::useItem(Character& target) {
    target.modifyStat("attack", std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("Permanently increased " + target.className() + "'s attack by 5!", Color::YELLOW) << std::endl;
}
