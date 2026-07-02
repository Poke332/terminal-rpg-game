#include "../../include/non_playable/AncientDragon.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class ClawSwipe : public Skill {
public:
    ClawSwipe() : Skill("Claw Swipe", "Slashes with massive claws, reducing target armor by 8 for 3 turns", "single_cast_enemy", 10.0f, 0.4f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-8.0f, 3));
        std::cout << colorize("Claw Swipe! Armor reduced by 8 for 3 turns!", Color::RED) << std::endl;
    }
};

class DragonBreath : public Skill {
public:
    DragonBreath() : Skill("Dragon Breath", "Breathes searing flames for high damage", "single_cast_enemy", 15.0f, 0.5f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Dragon Breath! " + std::to_string(static_cast<int>(dmg)) + " fire damage!", Color::RED) << std::endl;
    }
};

class WorldEnder : public Skill {
public:
    WorldEnder() : Skill("World Ender", "ULTIMATE - Channels apocalyptic power for enormous damage and heals 30%", "single_cast_enemy", 50.0f, 1.0f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("WORLD ENDER! " + std::to_string(static_cast<int>(dmg)) + " APOCALYPTIC DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class DragonScales : public Passive {
public:
    DragonScales() : Passive("Dragon Scales", "+50% max HP, +20% armor", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.5f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        float armorBonus = owner.getStat(Stat::armor) * 0.2f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }
};

AncientDragon::AncientDragon(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 500.0f);
    registerStat(Stat::max_hp, 500.0f);
    registerStat(Stat::armor, 20.0f);
    registerStat(Stat::attack, 40.0f);
    registerStat(Stat::crit_chance, 0.15f);
    registerStat(Stat::crit_damage, 1.0f);
    setExpValue(800);
    setBoss(true);

    skillSlots[0] = std::make_unique<ClawSwipe>();
    skillSlots[1] = std::make_unique<DragonBreath>();
    skillSlots[2] = std::make_unique<WorldEnder>();

    addPassive(std::make_unique<DragonScales>());
}

std::string AncientDragon::className() const { return "Ancient Dragon"; }
