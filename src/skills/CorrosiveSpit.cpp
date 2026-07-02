#include "../../include/skills/CorrosiveSpit.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>

CorrosiveSpit::CorrosiveSpit()
    : Skill("Corrosive Spit",
            "Spits acidic bile that deals damage and Corrodes the target for 3 turns (-5 armor)",
            "single_cast_enemy", 0.0f, 0.1f, 2) {}

void CorrosiveSpit::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat("armor", std::make_unique<AddModifier>(-5.0f, 3));
    std::cout << colorize("Corrosive Spit! Enemy Corroded for 3 turns! (-5 Armor)", Color::GREEN) << std::endl;
}
