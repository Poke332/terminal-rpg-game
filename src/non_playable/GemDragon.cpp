#include "../../include/non_playable/GemDragon.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class GemRay : public Skill {
public:
    GemRay() : Skill("Gem Ray", "Fires a concentrated beam of gemstone energy", SkillType::single_cast_enemy, 16.0f, 0.45f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Gem Ray! " + std::to_string(static_cast<int>(dmg)) + " prismatic damage!", Color::CYAN) << std::endl;
    }
};

class StatDrain : public Skill {
public:
    StatDrain() : Skill("Stat Drain", "Drains the target's power, reducing ATK by 12%", SkillType::single_cast_enemy, 12.0f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float atkReduction = target.getStat(Stat::attack) * 0.12f;
        target.modifyStat(Stat::attack, std::make_unique<AddModifier>(-atkReduction, 3));
        std::cout << colorize("Stat Drain! Target ATK reduced by 12%!", Color::MAGENTA) << std::endl;
    }
};

class PrismaticBreath : public Skill {
public:
    PrismaticBreath() : Skill("Prismatic Breath", "Breathes a cone of prismatic energy for high damage", SkillType::single_cast_enemy, 20.0f, 0.5f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Prismatic Breath! " + std::to_string(static_cast<int>(dmg)) + " prismatic damage!", Color::CYAN) << std::endl;
    }
};

class DragonsHoard : public Skill {
public:
    DragonsHoard() : Skill("Dragon's Hoard", "ULTIMATE - Unleashes the power of a dragon's hoard for massive damage and heals 30%", SkillType::single_cast_enemy, 42.0f, 0.85f, 10) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("DRAGON'S HOARD! " + std::to_string(static_cast<int>(dmg)) + " PRISMATIC FURY! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::CYAN) << std::endl;
    }
};

class GemstoneAura : public Passive {
public:
    GemstoneAura() : Passive("Gemstone Aura", "+40% max HP, +12% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.4f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.12f));
    }
};

GemDragon::GemDragon(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 380.0f);
    registerStat(Stat::max_hp, 380.0f);
    registerStat(Stat::armor, 20.0f);
    registerStat(Stat::attack, 30.0f);
    registerStat(Stat::crit_chance, 0.15f);
    registerStat(Stat::crit_damage, 0.8f);
    setExpValue(450);
    setBoss(true);

    skillSlots[0] = std::make_unique<GemRay>();
    skillSlots[1] = std::make_unique<StatDrain>();
    skillSlots[2] = std::make_unique<PrismaticBreath>();
    skillSlots[3] = std::make_unique<DragonsHoard>();

    addPassive(std::make_unique<GemstoneAura>());
}

std::string GemDragon::className() const { return "Gem Dragon"; }
