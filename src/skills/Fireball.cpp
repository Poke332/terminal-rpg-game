#include "../../include/skills/Fireball.h"
#include "../../include/Character.h"

#include <iostream>

Fireball::Fireball()
    : Skill("Fireball", 
            "Conjures a fireball to strike the enemy",
            "single_cast_enemy",
            10.0f,
            0.3f,
            3) {}

void Fireball::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << "You conjured a blazing fireball!" << std::endl;
}