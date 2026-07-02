#include "../../include/skills/PrecisionShot.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

PrecisionShot::PrecisionShot()
    : Skill("Precision Shot", 
            "Strikes the enemy with a strong arrow, deals more damage to enemies below 50% hp",
            SkillType::single_cast_enemy,
            15.0f,
            0.1f,
            3) {}

void PrecisionShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float enemyHp = target.getStat("hp");
    float enemyMaxHp = target.getStat("max_hp");
    if (enemyHp < enemyMaxHp / 2.0f) {
        skillDamage *= 1.5f;
        std::cout << colorize("BONUS DAMAGE to weakened target!", Color::YELLOW) << std::endl;
    }    
    target.takeDamage(skillDamage);
    std::cout << colorize("You struck the enemy with a precision arrow!", Color::GREEN) << std::endl;
}
