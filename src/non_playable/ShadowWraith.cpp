#include "../../include/non_playable/ShadowWraith.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class ShadowStrike : public Skill {
public:
    ShadowStrike() : Skill("Shadow Strike", "Strikes from the shadows, reducing target ATK by 10%", SkillType::single_cast_enemy, 16.0f, 0.45f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-10.0f, 3));
        std::cout << colorize("Shadow Strike! Target ATK reduced by 10%!", Color::MAGENTA) << std::endl;
    }
};

class PhaseShift : public Skill {
public:
    PhaseShift() : Skill("Phase Shift", "Shifts into the ethereal plane, gaining +8 armor permanently", SkillType::self_cast, 0.0f, 0.0f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::armor, std::make_unique<AddModifier>(8.0f));
        std::cout << colorize("Phase Shift! Armor increased by 8!", Color::MAGENTA) << std::endl;
    }
};

class VoidRend : public Skill {
public:
    VoidRend() : Skill("Void Rend", "Rends the target with void energy for high damage", SkillType::single_cast_enemy, 22.0f, 0.55f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Void Rend! " + std::to_string(static_cast<int>(dmg)) + " void damage!", Color::MAGENTA) << std::endl;
    }
};

class ShadowRequiem : public Skill {
public:
    ShadowRequiem() : Skill("Shadow Requiem", "ULTIMATE - Plays a requiem of shadows for massive damage and heals 35%", SkillType::single_cast_enemy, 50.0f, 1.0f, 11) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.35f;
        user.heal(healAmt);
        std::cout << colorize("SHADOW REQUIEM! " + std::to_string(static_cast<int>(dmg)) + " SHADOW DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::MAGENTA) << std::endl;
    }
};

class EtherealForm : public Passive {
public:
    EtherealForm() : Passive("Ethereal Form", "+30% max HP, +20% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.3f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.20f));
    }
};

ShadowWraith::ShadowWraith(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 350.0f);
    registerStat(Stat::max_hp, 350.0f);
    registerStat(Stat::armor, 10.0f);
    registerStat(Stat::attack, 38.0f);
    registerStat(Stat::crit_chance, 0.18f);
    registerStat(Stat::crit_damage, 0.9f);
    setExpValue(600);
    setBoss(true);

    skillSlots[0] = std::make_unique<ShadowStrike>();
    skillSlots[1] = std::make_unique<PhaseShift>();
    skillSlots[2] = std::make_unique<VoidRend>();
    skillSlots[3] = std::make_unique<ShadowRequiem>();

    addPassive(std::make_unique<EtherealForm>());
}

std::string ShadowWraith::className() const { return "Shadow Wraith"; }
