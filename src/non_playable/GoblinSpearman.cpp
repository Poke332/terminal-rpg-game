#include "../../include/non_playable/GoblinSpearman.h"
#include "../../include/skills/PiercingThrust.h"
#include "../../include/Ids.h"

using namespace Ids;

GoblinSpearman::GoblinSpearman(const std::string& n) : Enemy(n, "goblin") {
    registerStat(Stat::hp, 60.0f);
    registerStat(Stat::max_hp, 60.0f);
    registerStat(Stat::armor, 2.0f);
    registerStat(Stat::attack, 12.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(25);

    skillSlots[0] = std::make_unique<PiercingThrust>();
}

std::string GoblinSpearman::className() const { return "Goblin Spearman"; }
