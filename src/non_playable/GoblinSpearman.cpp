#include "../../include/non_playable/GoblinSpearman.h"

GoblinSpearman::GoblinSpearman(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 60.0f);
    registerStat("max_hp", 60.0f);
    registerStat("armor", 2.0f);
    registerStat("attack", 12.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 0.5f);
}

std::string GoblinSpearman::className() const { return "Goblin Spearman"; }