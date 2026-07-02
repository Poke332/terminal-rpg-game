#include "../../include/skills/ShieldBash.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

ShieldBash::ShieldBash()
    : Skill("Shield Bash",
            "Slams the enemy with your shield, dealing damage and Weakening them for 3 turns (-3 ATK)",
            SkillType::single_cast_enemy, 5.0f, 0.2f, 2) {}

void ShieldBash::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(-3.0f, 3));
    std::cout << colorize("Shield Bash! Enemy Weakened for 3 turns! (-3 ATK)", Color::YELLOW) << std::endl;
}
