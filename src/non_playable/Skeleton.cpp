#include "../../include/non_playable/Skeleton.h"
#include "../../include/skills/Execute.h"

Skeleton::Skeleton(const std::string& n) : Enemy(n, "undead") {
    registerStat("hp", 50.0f);
    registerStat("max_hp", 50.0f);
    registerStat("armor", 0.0f);
    registerStat("attack", 18.0f);
    registerStat("crit_chance", 0.3f);
    registerStat("crit_damage", 1.0f);
    setExpValue(30);

    skillSlots[0] = std::make_unique<Execute>();
}

std::string Skeleton::className() const { return "Skeleton"; }
