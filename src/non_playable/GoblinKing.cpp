#include "../../include/non_playable/GoblinKing.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class RoyalStrike : public Skill {
public:
    RoyalStrike() : Skill("Royal Strike", "A powerful blow that reduces the target's attack by 5", SkillType::single_cast_enemy, 10.0f, 0.3f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<AddModifier>(-5.0f, 3));
        std::cout << colorize("Royal Strike! Target attack reduced by 5 for 3 turns!", Color::RED) << std::endl;
    }
};

class Command : public Skill {
public:
    Command() : Skill("Command", "Boosts own attack by 10", SkillType::self_cast, 0.0f, 0.0f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::attack, std::make_unique<AddModifier>(10.0f));
        std::cout << colorize("Command! Attack increased by 10!", Color::YELLOW) << std::endl;
    }
};

class GoblinFrenzy : public Skill {
public:
    GoblinFrenzy() : Skill("Goblin Frenzy", "ULTIMATE - Massive damage and heals for 50% of damage dealt", SkillType::single_cast_enemy, 20.0f, 0.5f, 8) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.5f;
        user.heal(healAmt);
        std::cout << colorize("GOBLIN FRENZY! Dealt " + std::to_string(static_cast<int>(dmg)) + " and healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class KingsAuthority : public Passive {
public:
    KingsAuthority() : Passive("King's Authority", "+30% max HP, +10% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.3f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.10f));
    }
};

GoblinKing::GoblinKing(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 200.0f);
    registerStat(Stat::max_hp, 200.0f);
    registerStat(Stat::armor, 8.0f);
    registerStat(Stat::attack, 25.0f);
    registerStat(Stat::crit_chance, 0.1f);
    registerStat(Stat::crit_damage, 0.5f);
    setExpValue(200);
    setBoss(true);

    skillSlots[0] = std::make_unique<RoyalStrike>();
    skillSlots[1] = std::make_unique<Command>();
    skillSlots[2] = std::make_unique<GoblinFrenzy>();

    addPassive(std::make_unique<KingsAuthority>());
}

std::string GoblinKing::className() const { return "Goblin King"; }
