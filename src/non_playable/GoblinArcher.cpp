#include "../../include/non_playable/GoblinArcher.h"
#include "../../include/skills/PowerShot.h"
#include "../../include/Ids.h"

using namespace Ids;

GoblinArcher::GoblinArcher(const std::string& n) : Enemy(n, "goblin") {
    registerStat(Stat::hp, 55.0f);
    registerStat(Stat::max_hp, 55.0f);
    registerStat(Stat::armor, 0.0f);
    registerStat(Stat::attack, 15.0f);
    registerStat(Stat::crit_chance, 0.25f);
    registerStat(Stat::crit_damage, 1.0f);
    setExpValue(30);

    skillSlots[0] = std::make_unique<PowerShot>();
}

std::string GoblinArcher::className() const { return "Goblin Archer"; }
