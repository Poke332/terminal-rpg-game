#include "ShadowBolt.h"
#include "../Character.h"
#include "../utils.h"
#include <iostream>

ShadowBolt::ShadowBolt()
    : Skill("Shadow Bolt",
            "Hurls a bolt of dark energy at the target",
            "single_cast_enemy", 10.0f, 0.4f, 3) {}

void ShadowBolt::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("Shadow Bolt! Dark energy engulfs the target!", Color::RED) << std::endl;
}
