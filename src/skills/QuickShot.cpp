#include "QuickShot.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

QuickShot::QuickShot()
    : Skill("Quick Shot",
            "Fires a swift arrow with reduced power but minimal cooldown",
            "single_cast_enemy", 0.0f, 0.6f, 1) {}

void QuickShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("Quick Shot! An arrow flies swift and true!", Color::GREEN) << std::endl;
}
