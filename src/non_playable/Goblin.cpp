#include "../../include/non_playable/Goblin.h"
#include "../../include/Ids.h"

using namespace Ids;

Goblin::Goblin(const std::string& n) : Enemy(n, "goblin") {
    registerStat(Stat::hp, 50.0f);
    registerStat(Stat::max_hp, 50.0f);
    registerStat(Stat::armor, 0.0f);
    registerStat(Stat::attack, 8.0f);
    registerStat(Stat::crit_chance, 0.05f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(20);
}

std::string Goblin::className() const { return "Goblin"; }
