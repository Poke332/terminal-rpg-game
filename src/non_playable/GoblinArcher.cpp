#include "../../include/non_playable/GoblinArcher.h"

GoblinArcher::GoblinArcher(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 55.0f);
    registerStat("max_hp", 55.0f);
    registerStat("armor", 0.0f);
    registerStat("attack", 15.0f);
    registerStat("crit_chance", 0.25f);
    registerStat("crit_damage", 1.0f);
}

std::string GoblinArcher::className() const { return "Goblin Archer"; }