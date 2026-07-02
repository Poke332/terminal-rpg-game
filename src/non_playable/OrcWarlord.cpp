#include "../../include/non_playable/OrcWarlord.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"

#include <iostream>

class WarStomp : public Skill {
public:
    WarStomp() : Skill("War Stomp", "Stomps the ground, dealing damage and reducing target armor by 5 for 3 turns", "single_cast_enemy", 10.0f, 0.3f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat("armor", std::make_unique<AddModifier>(-5.0f, 3));
        std::cout << colorize("War Stomp! Target armor reduced by 5 for 3 turns!", Color::RED) << std::endl;
    }
};

class Bloodthirst : public Skill {
public:
    Bloodthirst() : Skill("Bloodthirst", "Attacks viciously and heals for 30% of damage dealt", "single_cast_enemy", 8.0f, 0.3f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("Bloodthirst! Healed for " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class WarlordsWrath : public Skill {
public:
    WarlordsWrath() : Skill("Warlord's Wrath", "ULTIMATE - Unleashes devastating power for enormous damage", "single_cast_enemy", 30.0f, 0.6f, 9) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("WARLORD'S WRATH! " + std::to_string(static_cast<int>(dmg)) + " devastating damage!", Color::RED) << std::endl;
    }
};

class WarlordsWill : public Passive {
public:
    WarlordsWill() : Passive("Warlord's Will", "+20% attack, +10% crit chance", 1) {}
    void onUnlock(Character& owner) override {
        float atkBonus = owner.getStat("attack") * 0.2f;
        owner.modifyStat("attack", std::make_unique<AddModifier>(atkBonus));
        owner.modifyStat("crit_chance", std::make_unique<AddModifier>(0.10f));
    }
};

OrcWarlord::OrcWarlord(const std::string& n) : Enemy(n, "boss") {
    registerStat("hp", 300.0f);
    registerStat("max_hp", 300.0f);
    registerStat("armor", 12.0f);
    registerStat("attack", 30.0f);
    registerStat("crit_chance", 0.1f);
    registerStat("crit_damage", 0.75f);
    setExpValue(350);
    setBoss(true);

    skillSlots[0] = std::make_unique<WarStomp>();
    skillSlots[1] = std::make_unique<Bloodthirst>();
    skillSlots[2] = std::make_unique<WarlordsWrath>();

    addPassive(std::make_unique<WarlordsWill>());
}

std::string OrcWarlord::className() const { return "Orc Warlord"; }
