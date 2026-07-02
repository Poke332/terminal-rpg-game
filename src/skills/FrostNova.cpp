#include "../../include/skills/FrostNova.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

FrostNova::FrostNova()
    : Skill("Frost Nova",
            "Erupts a nova of frost, dealing damage and Chilling the enemy for 3 turns (-10% ATK, -50% crit)",
            SkillType::single_cast_enemy, 10.0f, 0.3f, 5) {}

void FrostNova::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-10.0f, 3));
    target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-50.0f, 3));
    std::cout << colorize("Frost Nova! Enemy Chilled for 3 turns! (-10% ATK, -50% Crit)", Color::CYAN) << std::endl;
}
