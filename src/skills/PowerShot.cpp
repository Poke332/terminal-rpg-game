#include "PowerShot.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

PowerShot::PowerShot()
    : Skill("Power Shot",
            "Draws the bow to full strength for a powerful shot",
            "single_cast_enemy", 10.0f, 0.5f, 3) {}

void PowerShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("Power Shot! A devastating arrow strikes true!", Color::RED) << std::endl;
}
