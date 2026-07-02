#include "../../include/non_playable/Orc.h"

Orc::Orc(const std::string& n) : Enemy(n, "orc") {
    registerStat("hp", 120.0f);
    registerStat("max_hp", 120.0f);
    registerStat("armor", 5.0f);
    registerStat("attack", 20.0f);
    registerStat("crit_chance", 0.05f);
    registerStat("crit_damage", 0.5f);
    setExpValue(35);
}

std::string Orc::className() const { return "Orc"; }
