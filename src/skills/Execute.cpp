#include "Execute.h"
#include "../Character.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

Execute::Execute()
    : Skill("Execute",
            "Strikes with lethal precision, dealing 75% more damage to targets below 50% HP",
            SkillType::single_cast_enemy, 10.0f, 0.2f, 3) {}

void Execute::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float enemyHp = target.getStat(Stat::hp);
    float enemyMaxHp = target.getStat(Stat::max_hp);
    if (enemyHp < enemyMaxHp * 0.5f) {
        skillDamage *= 1.75f;
        std::cout << colorize("EXECUTE! Bonus damage to weakened target!", Color::RED) << std::endl;
    }
    target.takeDamage(skillDamage);
    std::cout << colorize("Execute! A crushing blow!", Color::RED) << std::endl;
}
