#include "RainOfArrows.h"
#include "../Character.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>
#include <random>

using namespace Ids;

RainOfArrows::RainOfArrows()
    : Skill("Rain of Arrows",
            "Launches a volley of arrows with increased crit chance, devastating the target",
            SkillType::single_cast_enemy, 12.0f, 0.3f, 5) {}

void RainOfArrows::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < 40) {
        skillDamage *= 2.0f;
        std::cout << colorize("CRITICAL VOLLEY!", Color::RED) << std::endl;
    }

    target.takeDamage(skillDamage);
    std::cout << colorize("Rain of Arrows! Arrows shower down upon the enemy!", Color::YELLOW) << std::endl;
}
