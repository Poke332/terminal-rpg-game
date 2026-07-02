#include "../../include/items/AttackScroll.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"
#include <iostream>

using namespace Ids;

AttackScroll::AttackScroll(int count) : Item(ItemName::attack_scroll, count) {}

void AttackScroll::useItem(Character& target) {
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("Permanently increased " + target.className() + "'s attack by 5!", Color::YELLOW) << std::endl;
}
