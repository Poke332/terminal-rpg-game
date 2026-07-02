#include "../../include/playable/archer/Archer.h"
#include "../../include/skills/PrecisionShot.h"
#include "../../include/skills/RainOfArrows.h"
#include "../../include/skills/QuickShot.h"
#include "../../include/passive/ArcherPassive.h"
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
        skillSlots[1] = std::make_unique<RainOfArrows>();
        skillSlots[2] = std::make_unique<QuickShot>();

        addPassive(std::make_unique<KeenEye>());
}

std::string Archer::className() const {
    return "Archer";
}

void Archer::checkPassiveUnlock() {}
