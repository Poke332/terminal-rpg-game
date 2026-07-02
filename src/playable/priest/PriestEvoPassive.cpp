#include "../../include/playable/priest/PriestEvoPassive.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

DivineAegis::DivineAegis()
    : Passive("Divine Aegis", "Healing an ally below 30% HP boosts the heal by 50%", 1) {}

void DivineAegis::onUnlock(Character& owner) {
    std::cout << colorize("Divine Aegis unlocked! Low HP allies receive stronger heals!", Color::GREEN) << std::endl;
}

Sanctuary::Sanctuary()
    : Passive("Sanctuary", "All party members take 5% less damage", 1) {}

void Sanctuary::onUnlock(Character& owner) {
    owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.05f));
    std::cout << colorize("Sanctuary unlocked! All allies take 5% less damage!", Color::GREEN) << std::endl;
}
