#include "../include/passive/MagePassive.h"
#include "../include/Character.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>

ArcanePower::ArcanePower() : Passive("Arcane Power", "+5 attack", 15) {}

void ArcanePower::onUnlock(Character& owner) {
    owner.modifyStat("attack", std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("Arcane Power unlocked! +5 Attack", Color::GREEN) << std::endl;
}

BurningInsight::BurningInsight() : Passive("Burning Insight", "+5% crit chance, +10% crit damage", 30) {}

void BurningInsight::onUnlock(Character& owner) {
    owner.modifyStat("crit_chance", std::make_unique<AddModifier>(0.05f));
    owner.modifyStat("crit_damage", std::make_unique<AddModifier>(0.10f));
    std::cout << colorize("Burning Insight unlocked! +5% Crit, +10% Crit DMG", Color::GREEN) << std::endl;
}

GrandMagus::GrandMagus() : Passive("Grand Magus", "+10 attack, +5% crit damage", 45) {}

void GrandMagus::onUnlock(Character& owner) {
    owner.modifyStat("attack", std::make_unique<AddModifier>(10.0f));
    owner.modifyStat("crit_damage", std::make_unique<AddModifier>(0.05f));
    std::cout << colorize("Grand Magus unlocked! +10 Attack, +5% Crit DMG", Color::GREEN) << std::endl;
}
