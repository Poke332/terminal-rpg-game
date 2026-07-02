#include "../../include/non_playable/VoidKing.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class RealityWarp : public Skill {
public:
    RealityWarp() : Skill("Reality Warp", "Warps reality, reducing target ATK by 15% and armor by 8", SkillType::single_cast_enemy, 18.0f, 0.5f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-15.0f, 3));
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-8.0f, 3));
        std::cout << colorize("Reality Warp! ATK reduced by 15%, armor reduced by 8!", Color::MAGENTA) << std::endl;
    }
};

class VoidShield : public Skill {
public:
    VoidShield() : Skill("Void Shield", "Creates a void shield, gaining +10 armor permanently", SkillType::self_cast, 0.0f, 0.0f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::armor, std::make_unique<AddModifier>(10.0f));
        std::cout << colorize("Void Shield! Armor increased by 10!", Color::MAGENTA) << std::endl;
    }
};

class DarkPulse : public Skill {
public:
    DarkPulse() : Skill("Dark Pulse", "Emits a pulse of dark energy for high damage", SkillType::single_cast_enemy, 22.0f, 0.55f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Dark Pulse! " + std::to_string(static_cast<int>(dmg)) + " void damage!", Color::MAGENTA) << std::endl;
    }
};

class Oblivion : public Skill {
public:
    Oblivion() : Skill("Oblivion", "ULTIMATE - Casts the target into oblivion for massive damage and heals 30%", SkillType::single_cast_enemy, 55.0f, 1.1f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("OBLIVION! " + std::to_string(static_cast<int>(dmg)) + " VOID ANNIHILATION! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::MAGENTA) << std::endl;
    }
};

class VoidPresence : public Passive {
public:
    VoidPresence() : Passive("Void Presence", "+60% max HP, +15% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.6f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.15f));
    }
};

VoidKing::VoidKing(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 500.0f);
    registerStat(Stat::max_hp, 500.0f);
    registerStat(Stat::armor, 18.0f);
    registerStat(Stat::attack, 40.0f);
    registerStat(Stat::crit_chance, 0.15f);
    registerStat(Stat::crit_damage, 0.8f);
    setExpValue(700);
    setBoss(true);

    skillSlots[0] = std::make_unique<RealityWarp>();
    skillSlots[1] = std::make_unique<VoidShield>();
    skillSlots[2] = std::make_unique<DarkPulse>();
    skillSlots[3] = std::make_unique<Oblivion>();

    addPassive(std::make_unique<VoidPresence>());
}

std::string VoidKing::className() const { return "Void King"; }
