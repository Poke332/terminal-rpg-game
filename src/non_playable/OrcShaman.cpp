#include "../../include/non_playable/OrcShaman.h"
#include "../../include/skills/ShadowBolt.h"

OrcShaman::OrcShaman(const std::string& n) : Enemy(n, "orc") {
    registerStat("hp", 80.0f);
    registerStat("max_hp", 80.0f);
    registerStat("armor", 2.0f);
    registerStat("attack", 12.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 0.75f);
    setExpValue(40);

    skillSlots[0] = std::make_unique<ShadowBolt>();
}

std::string OrcShaman::className() const { return "Orc Shaman"; }
