#include "WarCry.h"
#include "../Character.h"
#include "../stats/AddModifier.h"
#include "../stats/PercentModifier.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

WarCry::WarCry()
    : Skill("War Cry",
            "Taunts an enemy, forcing them to attack you and reducing their ATK by 30% for 2 turns",
            SkillType::single_cast_enemy, 0.0f, 0.0f, 4) {}

void WarCry::skillImplementation(Character& user, Character& target) {
    target.setTauntedByName(user.getName(), 2);
    target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-30.0f, 2));
    std::cout << colorize("War Cry! Taunted " + target.getName() + "! ATK reduced by 30% for 2 turns!", Color::YELLOW) << std::endl;
}
