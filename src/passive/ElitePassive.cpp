#include "../include/passive/ElitePassive.h"
#include "../include/Character.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>

EliteResilience::EliteResilience()
    : Passive("Elite Resilience", "+20% max HP, +5% damage reduction", 1) {}

void EliteResilience::onUnlock(Character& owner) {
    float hpBonus = owner.getStat("max_hp") * 0.2f;
    owner.modifyStat("max_hp", std::make_unique<AddModifier>(hpBonus));
    owner.modifyStat("hp", std::make_unique<AddModifier>(hpBonus));
    owner.modifyStat("damage_reduction", std::make_unique<AddModifier>(0.05f));
}
