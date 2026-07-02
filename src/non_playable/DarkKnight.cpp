#include "../../include/non_playable/DarkKnight.h"
#include "../../include/skills/SoulDrain.h"
#include "../../include/Ids.h"

using namespace Ids;

DarkKnight::DarkKnight(const std::string& n) : Enemy(n, "undead") {
    registerStat(Stat::hp, 100.0f);
    registerStat(Stat::max_hp, 100.0f);
    registerStat(Stat::armor, 8.0f);
    registerStat(Stat::attack, 15.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.75f);
    setExpValue(45);

    skillSlots[0] = std::make_unique<SoulDrain>();
}

std::string DarkKnight::className() const { return "Dark Knight"; }
