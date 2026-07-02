#include "SoulDrain.h"
#include "../Character.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

SoulDrain::SoulDrain()
    : Skill("Soul Drain",
            "Drains the target's life force, dealing damage and healing the user for 50% of damage dealt",
            SkillType::single_cast_enemy, 8.0f, 0.3f, 4) {}

void SoulDrain::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    float healAmount = skillDamage * 0.5f;
    user.heal(healAmount);
    std::cout << colorize("Soul Drain! Healed for " + std::to_string(static_cast<int>(healAmount)) + " HP!", Color::RED) << std::endl;
}
