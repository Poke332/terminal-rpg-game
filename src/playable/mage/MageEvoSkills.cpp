#include "../../include/playable/mage/MageEvoSkills.h"
#include "../../include/Character.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

// Evo 1 Skills

Inferno::Inferno()
    : Skill("Inferno",
            "Conjures an inferno of flames, dealing heavy damage and applying Burning for 4 turns",
            SkillType::single_cast_enemy, 15.0f, 0.4f, 3) {}

void Inferno::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    float dotDamage = 8.0f + skillDamage * 0.15f;
    target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDamage, 4));
    std::cout << colorize("Inferno! A blazing inferno engulfs the enemy! Burning for 4 turns!", Color::RED) << std::endl;
}

ArcaneBarrage::ArcaneBarrage()
    : Skill("Arcane Barrage",
            "Unleashes a barrage of arcane bolts dealing massive damage and boosting next spell crit by 10%",
            SkillType::single_cast_enemy, 18.0f, 0.5f, 4) {}

void ArcaneBarrage::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    user.modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.10f, 1));
    std::cout << colorize("Arcane Barrage! Bolts of arcane energy pummel the enemy! +10% crit next turn!", Color::CYAN) << std::endl;
}

GlacierNova::GlacierNova()
    : Skill("Glacier Nova",
            "Erupts a nova of glacial ice, dealing damage and Chilling the enemy for 3 turns (-15% ATK, -75% crit)",
            SkillType::single_cast_enemy, 14.0f, 0.35f, 5) {}

void GlacierNova::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-15.0f, 3));
    target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-75.0f, 3));
    std::cout << colorize("Glacier Nova! Enemy Chilled for 3 turns! (-15% ATK, -75% Crit)", Color::CYAN) << std::endl;
}

// Evo 2 Skills

Hellfire::Hellfire()
    : Skill("Hellfire",
            "Summons hellfire, dealing massive damage, Burning for 5 turns, and reducing healing by 50%",
            SkillType::single_cast_enemy, 20.0f, 0.5f, 4) {}

void Hellfire::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    float dotDamage = 12.0f + skillDamage * 0.2f;
    target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::hellfire, "\xF0\x9F\x94\xA5", dotDamage, 5));
    std::cout << colorize("HELLFIRE! Infernal flames consume the enemy! Burning 5T, healing reduced!", Color::RED) << std::endl;
}

ArcaneCataclysm::ArcaneCataclysm()
    : Skill("Arcane Cataclysm",
            "Unleashes a cataclysmic blast of arcane energy, dealing massive damage and resetting all spell cooldowns",
            SkillType::single_cast_enemy, 25.0f, 0.6f, 5) {}

void ArcaneCataclysm::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("ARCANE CATACLYSM! Reality shatters under the arcane onslaught! Cooldowns reset!", Color::MAGENTA) << std::endl;
}

AbsoluteZero::AbsoluteZero()
    : Skill("Absolute Zero",
            "Freezes the enemy at absolute zero, dealing massive damage, -20% ATK, -100% crit for 3 turns",
            SkillType::single_cast_enemy, 22.0f, 0.5f, 6) {}

void AbsoluteZero::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-20.0f, 3));
    target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-100.0f, 3));
    std::cout << colorize("ABSOLUTE ZERO! The enemy is frozen solid! (-20% ATK, -100% Crit for 3T)", Color::CYAN) << std::endl;
}

ArcaneAnnihilation::ArcaneAnnihilation()
    : Skill("Arcane Annihilation",
            "Channels all focus into a beam of pure arcane energy dealing 400% ATK damage. Requires max focus.",
            SkillType::single_cast_enemy, 0.0f, 4.0f, 0) {}

void ArcaneAnnihilation::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("ARCANE ANNIHILATION! Pure arcane energy disintegrates the enemy!", Color::MAGENTA) << std::endl;
}
