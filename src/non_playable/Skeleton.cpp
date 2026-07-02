#include "../../include/non_playable/Skeleton.h"
#include "../../include/skills/Execute.h"
#include "../../include/Ids.h"

using namespace Ids;

Skeleton::Skeleton(const std::string& n) : Enemy(n, "undead") {
    registerStat(Stat::hp, 50.0f);
    registerStat(Stat::max_hp, 50.0f);
    registerStat(Stat::armor, 0.0f);
    registerStat(Stat::attack, 18.0f);
    registerStat(Stat::crit_chance, 0.3f);
    registerStat(Stat::crit_damage, 1.0f);
    setExpValue(30);

    skillSlots[0] = std::make_unique<Execute>();
}

std::string Skeleton::className() const { return "Skeleton"; }
