#include "PiercingThrust.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

PiercingThrust::PiercingThrust()
    : Skill("Piercing Thrust",
            "Thrusts the spear at a weak point, completely ignoring armor",
            "single_cast_enemy", 8.0f, 0.2f, 3) {}

void PiercingThrust::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float armor = target.getStat("armor");
    target.takeDamage(skillDamage + armor);
    std::cout << colorize("Piercing Thrust! The spear bypasses all armor!", Color::RED) << std::endl;
}
