#include "../../include/playable/mage/Mage.h"
#include "../../include/skills/Fireball.h"
#include "../../include/skills/ArcaneBlast.h"
#include "../../include/skills/FrostNova.h"
#include "../../include/passive/MagePassive.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

Mage::Mage(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 100.0f);
        registerStat(Stat::max_hp, 100.0f);
        registerStat(Stat::armor, 3.0f);
        registerStat(Stat::attack, 20.0f);
        registerStat(Stat::crit_chance, 0.1f);
        registerStat(Stat::crit_damage, 0.5f);

        skillSlots[0] = std::make_unique<Fireball>();
        skillSlots[1] = std::make_unique<ArcaneBlast>();
        skillSlots[2] = std::make_unique<FrostNova>();

        addPassive(std::make_unique<ArcanePower>());
}

std::string Mage::className() const {
    return "Mage";
}

void Mage::checkPassiveUnlock() {}
