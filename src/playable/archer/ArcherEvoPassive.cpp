#include "../../include/playable/archer/ArcherEvoPassive.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include <random>

HuntersInstinct::HuntersInstinct()
    : Passive("Hunter's Instinct", "First attack on each enemy deals 30% more damage", 1) {}

void HuntersInstinct::onUnlock(Character& owner) {
    std::cout << colorize("Hunter's Instinct unlocked! First strike deals bonus damage!", Color::GREEN) << std::endl;
}

void HuntersInstinct::onAttack(Character& owner, Character& target, float& damage) {
    float enemyHp = target.getStat("hp");
    float enemyMaxHp = target.getStat("max_hp");
    if (enemyHp >= enemyMaxHp * 0.9f) {
        damage *= 1.3f;
        std::cout << colorize("Hunter's Instinct! First strike bonus!", Color::YELLOW) << std::endl;
    }
}

EagleVision::EagleVision()
    : Passive("Eagle Vision", "Critical hits against full-HP enemies deal 100% bonus crit damage", 1) {}

void EagleVision::onUnlock(Character& owner) {
    std::cout << colorize("Eagle Vision unlocked! Devastating crits on fresh targets!", Color::GREEN) << std::endl;
}

void EagleVision::onAttack(Character& owner, Character& target, float& damage) {
    float enemyHp = target.getStat("hp");
    float enemyMaxHp = target.getStat("max_hp");
    if (enemyHp >= enemyMaxHp * 0.95f) {
        damage *= 1.25f;
        std::cout << colorize("Eagle Vision! Devastating opening shot!", Color::YELLOW) << std::endl;
    }
}
