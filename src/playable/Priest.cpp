#include "../../include/playable/Priest.h"
#include "../../include/skills/SingleHeal.h"
#include <iostream>

Priest::Priest(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 100.0f);
        registerStat("max_hp", 100.0f);
        registerStat("armor", 4.0f);
        registerStat("attack", 10.0f);
        registerStat("crit_chance", 0.05f);
        registerStat("crit_damage", 0.5f);
        registerStat("healing_bonus_percentage", 0.1f);
        registerStat("healing_bonus_base", 5.0f);

        skillSlots[0] = std::make_unique<SingleHeal>();
}

std::string Priest::className() const {
    return "Priest";
}

int Priest::heal(float h) {
    float newHeal = (h * (1.0f+getStat("healing_bonus_percentage")) + getStat("healing_bonus_base"));
    return Character::heal(newHeal);
}