#include "../../include/non_playable/Lich.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"

#include <iostream>

class LichSoulDrain : public Skill {
public:
    LichSoulDrain() : Skill("Soul Drain", "Drains life force, dealing damage and healing for 50% of damage dealt", "single_cast_enemy", 8.0f, 0.3f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.5f;
        user.heal(healAmt);
        std::cout << colorize("Soul Drain! Healed for " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class LichShadowBolt : public Skill {
public:
    LichShadowBolt() : Skill("Shadow Bolt", "Hurls dark energy for massive damage", "single_cast_enemy", 15.0f, 0.5f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Shadow Bolt! " + std::to_string(static_cast<int>(dmg)) + " dark damage!", Color::RED) << std::endl;
    }
};

class SoulStorm : public Skill {
public:
    SoulStorm() : Skill("Soul Storm", "ULTIMATE - Summons a storm of souls for massive damage", "single_cast_enemy", 40.0f, 0.8f, 10) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("SOUL STORM! " + std::to_string(static_cast<int>(dmg)) + " unholy damage!", Color::RED) << std::endl;
    }
};

class Undying : public Passive {
public:
    Undying() : Passive("Undying", "+40% max HP, +15% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat("max_hp") * 0.4f;
        owner.modifyStat("max_hp", std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat("hp", std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat("damage_reduction", std::make_unique<AddModifier>(0.15f));
    }
};

Lich::Lich(const std::string& n) : Enemy(n, "boss") {
    registerStat("hp", 250.0f);
    registerStat("max_hp", 250.0f);
    registerStat("armor", 5.0f);
    registerStat("attack", 35.0f);
    registerStat("crit_chance", 0.2f);
    registerStat("crit_damage", 1.0f);
    setExpValue(500);
    setBoss(true);

    skillSlots[0] = std::make_unique<LichSoulDrain>();
    skillSlots[1] = std::make_unique<LichShadowBolt>();
    skillSlots[2] = std::make_unique<SoulStorm>();

    addPassive(std::make_unique<Undying>());
}

std::string Lich::className() const { return "Lich"; }
