#include "../../include/skills/SingleHeal.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

SingleHeal::SingleHeal()
    : Skill("Healing Touch", 
            "Conjures divine power and heals a chosen teammate. This skill can only be used by a Priest",
            SkillType::single_cast_ally,
            10.0f,
            0.0f,
            5) {}

void SingleHeal::skillImplementation(Character& user, Character& target) {
    float userBaseHeal = user.getStat(Stat::healing_bonus_base);
    float userPercentHeal = user.getStat(Stat::healing_bonus_pct);
    float baseAttack = user.getStat(Stat::attack);
    float healTotal = (baseScale + userBaseHeal + baseAttack) * (1 + userPercentHeal + percentScale);
    target.heal(healTotal);
    std::cout << colorize("You cast healing on " + target.className() + "!", Color::GREEN) << std::endl;
}
