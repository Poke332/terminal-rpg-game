#include "DivineSmite.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

DivineSmite::DivineSmite()
    : Skill("Divine Smite",
            "Channels divine power to smite an enemy, damage scales with healing bonus",
            "single_cast_enemy", 8.0f, 0.2f, 3) {}

void DivineSmite::skillImplementation(Character& user, Character& target) {
    float baseDmg = getFinalDamage(user.getAtkValue());
    float healingBonus = user.getStat("healing_bonus_percentage");
    float healBase = user.getStat("healing_bonus_base");
    float skillDamage = baseDmg * (1.0f + healingBonus) + healBase;
    target.takeDamage(skillDamage);
    std::cout << colorize("Divine Smite! Holy light burns the enemy!", Color::YELLOW) << std::endl;
}
