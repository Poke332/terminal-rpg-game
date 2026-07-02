#include "../../include/non_playable/CrystalGolem.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class CrystalSlam : public Skill {
public:
    CrystalSlam() : Skill("Crystal Slam", "Slams with crystalline fists, dealing damage and reducing armor by 8 for 3 turns", SkillType::single_cast_enemy, 14.0f, 0.4f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-8.0f, 3));
        std::cout << colorize("Crystal Slam! " + std::to_string(static_cast<int>(dmg)) + " damage! Armor reduced by 8!", Color::CYAN) << std::endl;
    }
};

class ReflectiveShield : public Skill {
public:
    ReflectiveShield() : Skill("Reflective Shield", "Hardens crystal body, permanently increasing armor by 5", SkillType::self_cast, 0.0f, 0.0f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        user.modifyStat(Stat::armor, std::make_unique<AddModifier>(5.0f));
        std::cout << colorize("Reflective Shield! Armor permanently increased by 5!", Color::CYAN) << std::endl;
    }
};

class PrismaticBeam : public Skill {
public:
    PrismaticBeam() : Skill("Prismatic Beam", "Fires a devastating beam of crystal energy", SkillType::single_cast_enemy, 18.0f, 0.5f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Prismatic Beam! " + std::to_string(static_cast<int>(dmg)) + " crystal damage!", Color::CYAN) << std::endl;
    }
};

class CrystalNova : public Skill {
public:
    CrystalNova() : Skill("Crystal Nova", "ULTIMATE - Detonates a nova of crystal shards for massive damage and heals 25%", SkillType::single_cast_enemy, 38.0f, 0.75f, 9) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.25f;
        user.heal(healAmt);
        std::cout << colorize("CRYSTAL NOVA! " + std::to_string(static_cast<int>(dmg)) + " crystal damage! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::CYAN) << std::endl;
    }
};

class CrystalBody : public Passive {
public:
    CrystalBody() : Passive("Crystal Body", "+45% max HP, +15% armor", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.45f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        float armorBonus = owner.getStat(Stat::armor) * 0.15f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }
};

CrystalGolem::CrystalGolem(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 320.0f);
    registerStat(Stat::max_hp, 320.0f);
    registerStat(Stat::armor, 22.0f);
    registerStat(Stat::attack, 24.0f);
    registerStat(Stat::crit_chance, 0.08f);
    registerStat(Stat::crit_damage, 0.4f);
    setExpValue(350);
    setBoss(true);

    skillSlots[0] = std::make_unique<CrystalSlam>();
    skillSlots[1] = std::make_unique<ReflectiveShield>();
    skillSlots[2] = std::make_unique<PrismaticBeam>();

    addPassive(std::make_unique<CrystalBody>());
}

std::string CrystalGolem::className() const { return "Crystal Golem"; }
