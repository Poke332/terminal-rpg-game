#include "../../include/playable/priest/Priest.h"
#include "../../include/skills/SingleHeal.h"
#include "../../include/skills/DivineSmite.h"
#include "../../include/skills/Blessing.h"
#include "../../include/passive/PriestPassive.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

Priest::Priest(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 100.0f);
        registerStat(Stat::max_hp, 100.0f);
        registerStat(Stat::armor, 4.0f);
        registerStat(Stat::attack, 10.0f);
        registerStat(Stat::crit_chance, 0.05f);
        registerStat(Stat::crit_damage, 0.5f);
        registerStat(Stat::healing_bonus_pct, 0.1f);
        registerStat(Stat::healing_bonus_base, 5.0f);

        skillSlots[0] = std::make_unique<SingleHeal>();
        skillSlots[1] = std::make_unique<DivineSmite>();
        skillSlots[2] = std::make_unique<Blessing>();

        addPassive(std::make_unique<HolyBlessing>());
}

std::string Priest::className() const {
    return "Priest";
}

int Priest::heal(float h) {
    float newHeal = (h * (1.0f + getStat(Stat::healing_bonus_pct)) + getStat(Stat::healing_bonus_base));
    return Character::heal(newHeal);
}

void Priest::checkPassiveUnlock() {}
