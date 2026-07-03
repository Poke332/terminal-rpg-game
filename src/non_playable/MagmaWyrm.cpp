#include "../../include/non_playable/MagmaWyrm.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class LavaBite : public Skill {
public:
    LavaBite() : Skill("Lava Bite", "Bites with molten fangs, applying Burning for 3 turns", SkillType::single_cast_enemy, 11.2f, 0.32f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 5.0f + dmg * 0.1f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDmg, 3));
        std::cout << colorize("Lava Bite! Burning applied for 3 turns!", Color::RED) << std::endl;
    }
};

class ArmorMelt : public Skill {
public:
    ArmorMelt() : Skill("Armor Melt", "Melts the target's armor, reducing it by 12", SkillType::single_cast_enemy, 9.8f, 0.28f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-12.0f, 3));
        std::cout << colorize("Armor Melt! Armor reduced by 12!", Color::RED) << std::endl;
    }
};

class MagmaBreath : public Skill {
public:
    MagmaBreath() : Skill("Magma Breath", "Breathes a torrent of magma for high damage", SkillType::single_cast_enemy, 14.0f, 0.35f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Magma Breath! " + std::to_string(static_cast<int>(dmg)) + " fire damage!", Color::RED) << std::endl;
    }
};

class VolcanicFury : public Skill {
public:
    VolcanicFury() : Skill("Volcanic Fury", "ULTIMATE - Erupts with volcanic fury for massive damage and heals 30%", SkillType::aoe_enemy, 33.6f, 0.67f, 11) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("VOLCANIC FURY! " + std::to_string(static_cast<int>(dmg)) + " MAGMA DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class MoltenScales : public Passive {
public:
    MoltenScales() : Passive("Molten Scales", "+55% max HP, +18% armor", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.55f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        float armorBonus = owner.getStat(Stat::armor) * 0.18f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }
};

MagmaWyrm::MagmaWyrm(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 450.0f);
    registerStat(Stat::max_hp, 450.0f);
    registerStat(Stat::armor, 25.0f);
    registerStat(Stat::attack, 32.0f);
    registerStat(Stat::crit_chance, 0.12f);
    registerStat(Stat::crit_damage, 0.7f);
    setExpValue(550);
    setBoss(true);

    skillSlots[0] = std::make_unique<LavaBite>();
    skillSlots[1] = std::make_unique<ArmorMelt>();
    skillSlots[2] = std::make_unique<MagmaBreath>();
    skillSlots[3] = std::make_unique<VolcanicFury>();

    addPassive(std::make_unique<MoltenScales>());
}

std::string MagmaWyrm::className() const { return "Magma Wyrm"; }
