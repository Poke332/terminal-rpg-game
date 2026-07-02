#include "../../include/non_playable/Slime.h"
#include "../../include/skills/CorrosiveSpit.h"

Slime::Slime(const std::string& n) : Enemy(n, "slime") {
    registerStat("hp", 40.0f);
    registerStat("max_hp", 40.0f);
    registerStat("armor", 0.0f);
    registerStat("attack", 8.0f);
    registerStat("crit_chance", 0.05f);
    registerStat("crit_damage", 0.5f);
    setExpValue(15);

    skillSlots[0] = std::make_unique<CorrosiveSpit>();
}

std::string Slime::className() const { return "Slime"; }
