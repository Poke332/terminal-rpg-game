#include "../../include/non_playable/SporeTitan.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class SporeBurst : public Skill {
public:
    SporeBurst() : Skill("Spore Burst", "Explodes with spores, dealing damage and applying Spore Rot for 3 turns", SkillType::single_cast_enemy, 12.0f, 0.4f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 5.0f + dmg * 0.1f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::spore_rot, "\xF0\x9F\x8D\x84", dotDmg, 3));
        std::cout << colorize("Spore Burst! Spore Rot applied!", Color::GREEN) << std::endl;
    }
};

class Enrage : public Skill {
public:
    Enrage() : Skill("Enrage", "Enters a rage, permanently increasing attack by 12", SkillType::self_cast, 0.0f, 0.0f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::attack, std::make_unique<AddModifier>(12.0f));
        std::cout << colorize("Enrage! Attack permanently increased by 12!", Color::RED) << std::endl;
    }
};

class TitansRoar : public Skill {
public:
    TitansRoar() : Skill("Titan's Roar", "Unleashes a deafening roar, dealing damage and reducing armor by 8 for 3 turns", SkillType::single_cast_enemy, 18.0f, 0.5f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-8.0f, 3));
        std::cout << colorize("Titan's Roar! " + std::to_string(static_cast<int>(dmg)) + " damage! Armor reduced by 8!", Color::RED) << std::endl;
    }
};

class TitansCall : public Skill {
public:
    TitansCall() : Skill("Titan's Call", "ULTIMATE - Calls upon primal titan power for massive damage and heals 35%", SkillType::single_cast_enemy, 40.0f, 0.8f, 10) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.35f;
        user.heal(healAmt);
        std::cout << colorize("TITAN'S CALL! " + std::to_string(static_cast<int>(dmg)) + " primal damage! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class ThickSpores : public Passive {
public:
    ThickSpores() : Passive("Thick Spores", "+50% max HP, +12% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.5f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.12f));
    }
};

SporeTitan::SporeTitan(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 350.0f);
    registerStat(Stat::max_hp, 350.0f);
    registerStat(Stat::armor, 18.0f);
    registerStat(Stat::attack, 25.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(400);
    setBoss(true);

    skillSlots[0] = std::make_unique<SporeBurst>();
    skillSlots[1] = std::make_unique<Enrage>();
    skillSlots[2] = std::make_unique<TitansRoar>();

    addPassive(std::make_unique<ThickSpores>());
}

std::string SporeTitan::className() const { return "Spore Titan"; }
