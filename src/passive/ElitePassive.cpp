#include "../include/passive/ElitePassive.h"
#include "../include/Character.h"
#include "../include/Ids.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>

using namespace Ids;

EliteResilience::EliteResilience()
    : Passive("Elite Resilience", "+20% max HP, +5% damage reduction", 1) {}

void EliteResilience::onUnlock(Character& owner) {
    float hpBonus = owner.getStat(Stat::max_hp) * 0.2f;
    owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
    owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
    owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.05f));
}
