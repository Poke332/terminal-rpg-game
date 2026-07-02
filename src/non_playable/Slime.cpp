#include "../../include/non_playable/Slime.h"
#include "../../include/skills/CorrosiveSpit.h"
#include "../../include/Ids.h"

using namespace Ids;

Slime::Slime(const std::string& n) : Enemy(n, "slime") {
    registerStat(Stat::hp, 40.0f);
    registerStat(Stat::max_hp, 40.0f);
    registerStat(Stat::armor, 0.0f);
    registerStat(Stat::attack, 8.0f);
    registerStat(Stat::crit_chance, 0.05f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(15);

    skillSlots[0] = std::make_unique<CorrosiveSpit>();
}

std::string Slime::className() const { return "Slime"; }
