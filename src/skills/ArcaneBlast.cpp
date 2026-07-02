#include "ArcaneBlast.h"
#include "../Character.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

ArcaneBlast::ArcaneBlast()
    : Skill("Arcane Blast",
            "Unleashes a concentrated blast of arcane energy dealing massive damage",
            SkillType::single_cast_enemy, 15.0f, 0.5f, 4) {}

void ArcaneBlast::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("Arcane Blast! Raw magical energy engulfs the enemy!", Color::CYAN) << std::endl;
}
