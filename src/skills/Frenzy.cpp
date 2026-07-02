#include "Frenzy.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

Frenzy::Frenzy()
    : Skill("Frenzy",
            "Enters a frenzied state, dealing damage and healing self for 20% of damage dealt",
            "single_cast_enemy", 8.0f, 0.3f, 4) {}

void Frenzy::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    float healAmount = skillDamage * 0.2f;
    user.heal(healAmount);
    std::cout << colorize("Frenzy! Healed for " + std::to_string(static_cast<int>(healAmount)) + " HP!", Color::RED) << std::endl;
}
