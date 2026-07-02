#include "../../include/non_playable/GoblinOverlord.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class WarBanner : public Skill {
public:
    WarBanner() : Skill("War Banner", "Plants a war banner, permanently increasing attack by 8", SkillType::self_cast, 0.0f, 0.0f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::attack, std::make_unique<AddModifier>(8.0f));
        std::cout << colorize("War Banner planted! Attack permanently increased by 8!", Color::YELLOW) << std::endl;
    }
};

class GoblinRally : public Skill {
public:
    GoblinRally() : Skill("Goblin Rally", "Rallies goblin allies to attack, dealing damage", SkillType::single_cast_enemy, 14.0f, 0.4f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Goblin Rally! Allies swarm the target for " + std::to_string(static_cast<int>(dmg)) + " damage!", Color::GREEN) << std::endl;
    }
};

class Execute : public Skill {
public:
    Execute() : Skill("Execute", "Attempts to finish off a weakened target. Deals double damage if target is below 50% HP", SkillType::single_cast_enemy, 10.0f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        if (target.getStat(Stat::hp) < target.getStat(Stat::max_hp) * 0.5f) {
            dmg *= 2.0f;
            std::cout << colorize("EXECUTE! Target is below 50% HP! Double damage for " + std::to_string(static_cast<int>(dmg)) + "!", Color::RED) << std::endl;
        } else {
            std::cout << colorize("Execute! " + std::to_string(static_cast<int>(dmg)) + " damage!", Color::RED) << std::endl;
        }
        target.takeDamage(dmg);
    }
};

class OverlordsFrenzy : public Skill {
public:
    OverlordsFrenzy() : Skill("Overlord's Frenzy", "ULTIMATE - Unleashes a frenzied assault for massive damage and heals 40%", SkillType::single_cast_enemy, 25.0f, 0.5f, 8) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.4f;
        user.heal(healAmt);
        std::cout << colorize("OVERLORD'S FRENZY! Dealt " + std::to_string(static_cast<int>(dmg)) + " and healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class OverlordsPresence : public Passive {
public:
    OverlordsPresence() : Passive("Overlord's Presence", "+25% max HP, +8% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.25f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.08f));
    }
};

GoblinOverlord::GoblinOverlord(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 180.0f);
    registerStat(Stat::max_hp, 180.0f);
    registerStat(Stat::armor, 7.0f);
    registerStat(Stat::attack, 22.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(150);
    setBoss(true);

    skillSlots[0] = std::make_unique<WarBanner>();
    skillSlots[1] = std::make_unique<GoblinRally>();
    skillSlots[2] = std::make_unique<Execute>();

    addPassive(std::make_unique<OverlordsPresence>());
}

std::string GoblinOverlord::className() const { return "Goblin Overlord"; }
