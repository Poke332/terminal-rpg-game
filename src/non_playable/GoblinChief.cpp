#include "../../include/non_playable/GoblinChief.h"
#include "../../include/skills/Frenzy.h"
#include "../../include/Ids.h"

using namespace Ids;

GoblinChief::GoblinChief(const std::string& n) : Enemy(n, "goblin") {
    registerStat(Stat::hp, 100.0f);
    registerStat(Stat::max_hp, 100.0f);
    registerStat(Stat::armor, 10.0f);
    registerStat(Stat::attack, 18.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 1.0f);
    setExpValue(50);

    skillSlots[0] = std::make_unique<Frenzy>();
}

std::string GoblinChief::className() const { return "Goblin Chief"; }
