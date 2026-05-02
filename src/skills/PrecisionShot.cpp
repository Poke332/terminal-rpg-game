#include "../../include/skills/PrecisionShot.h"
#include "../../include/Character.h"

#include <iostream>

PrecisionShot::PrecisionShot()
    : Skill("Precision Shot", 
            "Strikes the enemy with a strong arrow, this skill deals more damage to enemies below 50% hp",
            "single_cast_enemy",
            15.0f,
            0.1f,
            3) {}

void PrecisionShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float enemyHp = target.getStat("hp");
    float enemyMaxHp = target.getStat("max_hp");
    if (enemyHp < enemyMaxHp/2.0) {
        skillDamage *= 1.5;
    }    
    target.takeDamage(skillDamage);
    std::cout << "You striked the enemy with an arrow!" << std::endl;
}