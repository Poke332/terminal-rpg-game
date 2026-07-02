#include "../../include/non_playable/OrcShamanLord.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class LightningBolt : public Skill {
public:
    LightningBolt() : Skill("Lightning Bolt", "Hurls a bolt of lightning at the target", SkillType::single_cast_enemy, 12.0f, 0.4f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Lightning Bolt! " + std::to_string(static_cast<int>(dmg)) + " lightning damage!", Color::YELLOW) << std::endl;
    }
};

class HealingWave : public Skill {
public:
    HealingWave() : Skill("Healing Wave", "Channels a wave of healing energy, restoring 30% of max HP", SkillType::self_cast, 0.0f, 0.0f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float healAmt = user.getStat(Stat::max_hp) * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("Healing Wave! Restored " + std::to_string(static_cast<int>(healAmt)) + " HP!", Color::GREEN) << std::endl;
    }
};

class OrcChainLightning : public Skill {
public:
    OrcChainLightning() : Skill("Chain Lightning", "Launches chain lightning that arcs between targets, reducing armor by 6 for 3 turns", SkillType::single_cast_enemy, 15.0f, 0.45f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-6.0f, 3));
        std::cout << colorize("Chain Lightning! " + std::to_string(static_cast<int>(dmg)) + " damage! Armor reduced by 6!", Color::YELLOW) << std::endl;
    }
};

class StormsFury : public Skill {
public:
    StormsFury() : Skill("Storm's Fury", "ULTIMATE - Calls down the fury of the storm for massive damage and heals 30%", SkillType::single_cast_enemy, 35.0f, 0.7f, 9) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("STORM'S FURY! " + std::to_string(static_cast<int>(dmg)) + " storm damage! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::YELLOW) << std::endl;
    }
};

class ShamanisticFury : public Passive {
public:
    ShamanisticFury() : Passive("Shamanistic Fury", "+20% attack, +10% crit chance", 1) {}
    void onUnlock(Character& owner) override {
        float atkBonus = owner.getStat(Stat::attack) * 0.2f;
        owner.modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
        owner.modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.10f));
    }
};

OrcShamanLord::OrcShamanLord(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 220.0f);
    registerStat(Stat::max_hp, 220.0f);
    registerStat(Stat::armor, 10.0f);
    registerStat(Stat::attack, 28.0f);
    registerStat(Stat::crit_chance, 0.12f);
    registerStat(Stat::crit_damage, 0.6f);
    setExpValue(250);
    setBoss(true);

    skillSlots[0] = std::make_unique<LightningBolt>();
    skillSlots[1] = std::make_unique<HealingWave>();
    skillSlots[2] = std::make_unique<OrcChainLightning>();

    addPassive(std::make_unique<ShamanisticFury>());
}

std::string OrcShamanLord::className() const { return "Orc Shaman Lord"; }
