#include "../../include/non_playable/FireElementalLord.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class Fireball : public Skill {
public:
    Fireball() : Skill("Fireball", "Hurls a fireball at the target, applying Burning for 3 turns", SkillType::single_cast_enemy, 9.8f, 0.28f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 5.0f + dmg * 0.1f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDmg, 3));
        std::cout << colorize("Fireball! Burning applied for 3 turns!", Color::RED) << std::endl;
    }
};

class MagmaPool : public Skill {
public:
    MagmaPool() : Skill("Magma Pool", "Creates a pool of magma, reducing armor by 10", SkillType::single_cast_enemy, 12.6f, 0.35f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-10.0f, 3));
        std::cout << colorize("Magma Pool! Armor reduced by 10!", Color::RED) << std::endl;
    }
};

class Immolate : public Skill {
public:
    Immolate() : Skill("Immolate", "Engulfs the target in flames, applying Burning for 4 turns", SkillType::single_cast_enemy, 8.4f, 0.25f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 4.0f + dmg * 0.08f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDmg, 4));
        std::cout << colorize("Immolate! Burning applied for 4 turns!", Color::RED) << std::endl;
    }
};

class Eruption : public Skill {
public:
    Eruption() : Skill("Eruption", "ULTIMATE - Causes a volcanic eruption for massive damage and heals 25%", SkillType::aoe_enemy, 31.5f, 0.63f, 10) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.25f;
        user.heal(healAmt);
        std::cout << colorize("ERUPTION! " + std::to_string(static_cast<int>(dmg)) + " VOLCANIC FURY! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class ImmuneToBurning : public Passive {
public:
    ImmuneToBurning() : Passive("Immune to Burning", "+50% max HP, +10% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.5f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.10f));
    }
};

FireElementalLord::FireElementalLord(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 400.0f);
    registerStat(Stat::max_hp, 400.0f);
    registerStat(Stat::armor, 15.0f);
    registerStat(Stat::attack, 35.0f);
    registerStat(Stat::crit_chance, 0.12f);
    registerStat(Stat::crit_damage, 0.7f);
    setExpValue(500);
    setBoss(true);

    skillSlots[0] = std::make_unique<Fireball>();
    skillSlots[1] = std::make_unique<MagmaPool>();
    skillSlots[2] = std::make_unique<Immolate>();
    skillSlots[3] = std::make_unique<Eruption>();

    addPassive(std::make_unique<ImmuneToBurning>());
}

std::string FireElementalLord::className() const { return "Fire Elemental Lord"; }
