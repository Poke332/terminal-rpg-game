#include "../../include/non_playable/DarkKnight.h"
#include "../../include/skills/SoulDrain.h"

DarkKnight::DarkKnight(const std::string& n) : Enemy(n, "undead") {
    registerStat("hp", 100.0f);
    registerStat("max_hp", 100.0f);
    registerStat("armor", 8.0f);
    registerStat("attack", 15.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 0.75f);
    setExpValue(45);

    skillSlots[0] = std::make_unique<SoulDrain>();
}

std::string DarkKnight::className() const { return "Dark Knight"; }
