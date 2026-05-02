#include "../../include/non_playable/GoblinChief.h"

GoblinChief::GoblinChief(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 100.0f);
    registerStat("max_hp", 100.0f);
    registerStat("armor", 10.0f);
    registerStat("attack", 18.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 1.0f);
}

std::string GoblinChief::className() const { return "Goblin Chief"; }