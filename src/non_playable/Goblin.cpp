#include "../../include/non_playable/Goblin.h"

Goblin::Goblin(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 50.0f);
    registerStat("max_hp", 50.0f);
    registerStat("armor", 0.0f);
    registerStat("attack", 8.0f);
    registerStat("crit_chance", 0.05f);
    registerStat("crit_damage", 0.5f);
    setExpValue(20);
}

std::string Goblin::className() const { return "Goblin"; }
