#include "../../include/non_playable/GoblinSpearman.h"
#include "../../include/skills/PiercingThrust.h"

GoblinSpearman::GoblinSpearman(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 60.0f);
    registerStat("max_hp", 60.0f);
    registerStat("armor", 2.0f);
    registerStat("attack", 12.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 0.5f);
    setExpValue(25);

    skillSlots[0] = std::make_unique<PiercingThrust>();
}

std::string GoblinSpearman::className() const { return "Goblin Spearman"; }
