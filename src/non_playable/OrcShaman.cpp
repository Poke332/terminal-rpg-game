#include "../../include/non_playable/OrcShaman.h"
#include "../../include/skills/ShadowBolt.h"
#include "../../include/Ids.h"

using namespace Ids;

OrcShaman::OrcShaman(const std::string& n) : Enemy(n, "orc") {
    registerStat(Stat::hp, 80.0f);
    registerStat(Stat::max_hp, 80.0f);
    registerStat(Stat::armor, 2.0f);
    registerStat(Stat::attack, 12.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.75f);
    setExpValue(40);

    skillSlots[0] = std::make_unique<ShadowBolt>();
}

std::string OrcShaman::className() const { return "Orc Shaman"; }
