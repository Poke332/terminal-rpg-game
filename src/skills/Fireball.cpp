#include "../../include/skills/Fireball.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

Fireball::Fireball()
    : Skill("Fireball", 
            "Conjures a fireball to strike the enemy, applying Burning for 3 turns",
            SkillType::single_cast_enemy,
            10.0f,
            0.3f,
            3) {}

void Fireball::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    float dotDamage = 5.0f + skillDamage * 0.1f;
    target.addStatusEffect(std::make_unique<DamageOverTime>("Burning", "\xF0\x9F\x94\xA5", dotDamage, 3));
    std::cout << colorize("You conjured a blazing fireball! Burning applied!", Color::RED) << std::endl;
}
