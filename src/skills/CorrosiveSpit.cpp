#include "../../include/skills/CorrosiveSpit.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

CorrosiveSpit::CorrosiveSpit()
    : Skill("Corrosive Spit",
            "Spits acidic bile that deals damage and Corrodes the target for 3 turns (-5 armor)",
            SkillType::single_cast_enemy, 0.0f, 0.1f, 2) {}

void CorrosiveSpit::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-5.0f, 3));
    std::cout << colorize("Corrosive Spit! Enemy Corroded for 3 turns! (-5 Armor)", Color::GREEN) << std::endl;
}
