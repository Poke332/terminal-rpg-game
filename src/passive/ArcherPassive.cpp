#include "../include/passive/ArcherPassive.h"
#include "../include/Character.h"
#include "../include/Ids.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>
#include <random>

using namespace Ids;

KeenEye::KeenEye() : Passive("Keen Eye", "+5% crit chance", 15) {}

void KeenEye::onUnlock(Character& owner) {
    owner.modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.05f));
    std::cout << colorize("Keen Eye unlocked! +5% Crit Chance", Color::GREEN) << std::endl;
}

EaglesPrecision::EaglesPrecision() : Passive("Eagle's Precision", "+15% crit damage, +5% damage bonus", 30) {}

void EaglesPrecision::onUnlock(Character& owner) {
    owner.modifyStat(Stat::crit_damage, std::make_unique<AddModifier>(0.15f));
    owner.modifyStat(Stat::damage_bonus, std::make_unique<AddModifier>(0.05f));
    std::cout << colorize("Eagle's Precision unlocked! +15% Crit DMG, +5% DMG Bonus", Color::GREEN) << std::endl;
}

ShadowStalker::ShadowStalker() : Passive("Shadow Stalker", "+10% crit chance. 15% chance to deal double damage on attacks.", 45) {}

void ShadowStalker::onUnlock(Character& owner) {
    owner.modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.10f));
    std::cout << colorize("Shadow Stalker unlocked! +10% Crit. 15% double damage chance!", Color::GREEN) << std::endl;
}

void ShadowStalker::onAttack(Character& owner, Character& target, float& damage) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < 15) {
        damage *= 2.0f;
        std::cout << colorize("Shadow Stalker! Double damage!", Color::RED) << std::endl;
    }
}
