#include "../../include/non_playable/GoblinChief.h"
#include "../../include/skills/Frenzy.h"

GoblinChief::GoblinChief(const std::string& n) : Enemy(n, "goblin") {
    registerStat("hp", 100.0f);
    registerStat("max_hp", 100.0f);
    registerStat("armor", 10.0f);
    registerStat("attack", 18.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 1.0f);
    setExpValue(50);

    skillSlots[0] = std::make_unique<Frenzy>();
}

std::string GoblinChief::className() const { return "Goblin Chief"; }
