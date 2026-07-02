#include "../../include/playable/mage/MageEvoPassive.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>

SpellAmplifier::SpellAmplifier()
    : Passive("Spell Amplifier", "Every 3rd spell cast deals 40% more damage", 1) {}

void SpellAmplifier::onUnlock(Character& owner) {
    std::cout << colorize("Spell Amplifier unlocked! Every 3rd spell is amplified!", Color::GREEN) << std::endl;
}

void SpellAmplifier::onAttack(Character& owner, Character& target, float& damage) {
    spellCount_++;
    if (spellCount_ >= 3) {
        damage *= 1.4f;
        spellCount_ = 0;
        std::cout << colorize("Spell Amplifier! Damage boosted by 40%!", Color::MAGENTA) << std::endl;
    }
}

ElementalMastery::ElementalMastery()
    : Passive("Elemental Mastery", "Spells ignore 25% of enemy armor", 1) {}

void ElementalMastery::onUnlock(Character& owner) {
    std::cout << colorize("Elemental Mastery unlocked! Spells penetrate 25% armor!", Color::GREEN) << std::endl;
}

void ElementalMastery::onAttack(Character& owner, Character& target, float& damage) {
    float armor = target.getStat("armor");
    float ignored = armor * 0.25f;
    damage += ignored;
}
