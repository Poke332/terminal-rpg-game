#include "../../include/non_playable/Orc.h"
#include "../../include/Ids.h"

using namespace Ids;

Orc::Orc(const std::string& n) : Enemy(n, "orc") {
    registerStat(Stat::hp, 120.0f);
    registerStat(Stat::max_hp, 120.0f);
    registerStat(Stat::armor, 5.0f);
    registerStat(Stat::attack, 20.0f);
    registerStat(Stat::crit_chance, 0.05f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(35);
}

std::string Orc::className() const { return "Orc"; }
