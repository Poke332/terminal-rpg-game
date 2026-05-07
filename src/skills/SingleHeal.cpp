#include "../../include/skills/SingleHeal.h"
#include "../../include/Character.h"

#include <iostream>

SingleHeal::SingleHeal()
    : Skill("Healing Touch", 
            "Conjures divine power and heal a chosen teammate, This skill can only be used by a Priest",
            "single_cast_ally",
            10.0f,
            0.0f,
            5) {}

void SingleHeal::skillImplementation(Character& user, Character& target) {
    float userBaseHeal = user.getStat("healing_bonus_base");
    float userPercentHeal = user.getStat("healing_bonus_percentage");
    float baseAttack = user.getStat("attack");
    float healTotal = (baseScale + userBaseHeal + baseAttack) * (1 + userPercentHeal + percentScale);
    target.heal(healTotal);
    std::cout << "You cast healing on an ally!" << std::endl;
}