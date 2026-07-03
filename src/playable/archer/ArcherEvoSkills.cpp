#include "../../include/playable/archer/ArcherEvoSkills.h"
#include "../../include/Character.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include <iostream>
#include <random>
#include "../../include/Ids.h"

using namespace Ids;

// Evo 1 Skills

DeadlyShot::DeadlyShot()
    : Skill("Deadly Shot",
            "Strikes with lethal precision, bonus damage to enemies below 60% HP, always crits below 40% HP",
            SkillType::single_cast_enemy, 18.0f, 0.15f, 3) {}

void DeadlyShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float enemyHp = target.getStat(Stat::hp);
    float enemyMaxHp = target.getStat(Stat::max_hp);
    if (enemyHp < enemyMaxHp * 0.6f) {
        skillDamage *= 1.5f;
        std::cout << colorize("BONUS DAMAGE to weakened target!", Color::YELLOW) << std::endl;
    }
    if (enemyHp < enemyMaxHp * 0.4f) {
        skillDamage *= 2.0f;
        std::cout << colorize("CRITICAL FINISHER!", Color::RED) << std::endl;
    }
    target.takeDamage(skillDamage);
    std::cout << colorize("Deadly Shot! A lethal arrow finds its mark!", Color::GREEN) << std::endl;
}

ArrowStorm::ArrowStorm()
    : Skill("Arrow Storm",
            "Launches a devastating storm of arrows with 60% crit chance",
            SkillType::aoe_enemy, 15.0f, 0.35f, 5) {}

void ArrowStorm::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < 60) {
        skillDamage *= 2.0f;
        std::cout << colorize("CRITICAL VOLLEY!", Color::RED) << std::endl;
    }
    target.takeDamage(skillDamage);
    std::cout << colorize("Arrow Storm! A torrent of arrows rains down!", Color::YELLOW) << std::endl;
}

SwiftVolley::SwiftVolley()
    : Skill("Swift Volley",
            "Fires two swift arrows in rapid succession, each dealing 60% damage. 1 turn cooldown.",
            SkillType::single_cast_enemy, 0.0f, 0.6f, 1) {}

void SwiftVolley::skillImplementation(Character& user, Character& target) {
    float baseDmg = user.getAtkValue();
    float hit1 = (baseScale + baseDmg) * (1.0f + 0.6f) * 0.6f;
    float hit2 = hit1;
    target.takeDamage(hit1);
    target.takeDamage(hit2);
    std::cout << colorize("Swift Volley! Two arrows strike in rapid succession!", Color::GREEN) << std::endl;
}

// Evo 2 Skills

ExecutionersShot::ExecutionersShot()
    : Skill("Executioner's Shot",
            "A shot of execution, bonus damage below 70% HP, always crits below 50%, +50% crit damage below 30%",
            SkillType::single_cast_enemy, 22.0f, 0.2f, 3) {}

void ExecutionersShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    float enemyHp = target.getStat(Stat::hp);
    float enemyMaxHp = target.getStat(Stat::max_hp);
    if (enemyHp < enemyMaxHp * 0.7f) {
        skillDamage *= 1.5f;
        std::cout << colorize("BONUS DAMAGE to weakened target!", Color::YELLOW) << std::endl;
    }
    if (enemyHp < enemyMaxHp * 0.5f) {
        skillDamage *= 2.0f;
        std::cout << colorize("CRITICAL FINISHER!", Color::RED) << std::endl;
    }
    if (enemyHp < enemyMaxHp * 0.3f) {
        skillDamage *= 1.5f;
        std::cout << colorize("EXECUTION BONUS!", Color::RED) << std::endl;
    }
    target.takeDamage(skillDamage);
    std::cout << colorize("Executioner's Shot! The arrow of judgment!", Color::RED) << std::endl;
}

TempestVolley::TempestVolley()
    : Skill("Tempest Volley",
            "Unleashes a tempest of arrows with 80% crit chance and applies Vulnerable (+10% damage taken for 2 turns)",
            SkillType::aoe_enemy, 18.0f, 0.4f, 5) {}

void TempestVolley::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < 80) {
        skillDamage *= 2.0f;
        std::cout << colorize("CRITICAL TEMPEST!", Color::RED) << std::endl;
    }
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-3.0f, 2));
    std::cout << colorize("Tempest Volley! Arrows tear through the enemy! Vulnerable for 2T!", Color::YELLOW) << std::endl;
}

RapidFire::RapidFire()
    : Skill("Rapid Fire",
            "Fires three arrows in rapid succession, each dealing 50% damage. No cooldown.",
            SkillType::single_cast_enemy, 0.0f, 0.5f, 0) {}

void RapidFire::skillImplementation(Character& user, Character& target) {
    float baseDmg = user.getAtkValue();
    for (int i = 0; i < 3; i++) {
        float hit = (baseScale + baseDmg) * (1.0f + 0.5f) * 0.5f;
        target.takeDamage(hit);
    }
    std::cout << colorize("Rapid Fire! Three arrows fly in quick succession!", Color::GREEN) << std::endl;
}

PerfectShot::PerfectShot()
    : Skill("Perfect Shot",
            "Takes aim and fires a perfect shot with 100% crit rate dealing 500% ATK damage. Requires 5 focus.",
            SkillType::single_cast_enemy, 0.0f, 5.0f, 0) {}

void PerfectShot::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("PERFECT SHOT! The arrow of destiny finds its mark!", Color::RED) << std::endl;
}
