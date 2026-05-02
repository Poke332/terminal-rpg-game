#include "../../include/playable/Archer.h"
#include "../../include/skills/PrecisionShot.h"
#include <iostream>

Archer::Archer(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 90.0f);
        registerStat("max_hp", 90.0f);
        registerStat("armor", 0.0f);
        registerStat("attack", 20.0f);
        registerStat("damage_bonus", 0.05f);
        registerStat("crit_chance", 0.25f);
        registerStat("crit_damage", 1.0f);

        skillSlots[0] = std::make_unique<PrecisionShot>();
}

std::string Archer::className() const {
    return "Archer";
}