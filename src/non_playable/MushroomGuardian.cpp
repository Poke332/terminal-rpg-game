#include "../../include/non_playable/MushroomGuardian.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

class SporeShot : public Skill {
public:
    SporeShot() : Skill("Spore Shot", "Fires a cluster of spores that deal damage and apply Spore Rot for 3 turns", SkillType::single_cast_enemy, 10.0f, 0.35f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 4.0f + dmg * 0.1f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::spore_rot, "\xF0\x9F\x8D\x84", dotDmg, 3));
        std::cout << colorize("Spore Shot! Spore Rot applied!", Color::GREEN) << std::endl;
    }
};

class ToxicCloud : public Skill {
public:
    ToxicCloud() : Skill("Toxic Cloud", "Releases a toxic cloud, dealing damage and reducing target attack by 10% for 3 turns", SkillType::single_cast_enemy, 14.0f, 0.4f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-10.0f, 3));
        std::cout << colorize("Toxic Cloud! " + std::to_string(static_cast<int>(dmg)) + " damage! Attack reduced by 10%!", Color::GREEN) << std::endl;
    }
};

class FungalBloom : public Skill {
public:
    FungalBloom() : Skill("Fungal Bloom", "ULTIMATE - Erupts in a massive fungal bloom for damage and heals 50%", SkillType::single_cast_enemy, 30.0f, 0.6f, 8) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.5f;
        user.heal(healAmt);
        std::cout << colorize("FUNGAL BLOOM! " + std::to_string(static_cast<int>(dmg)) + " damage! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::GREEN) << std::endl;
    }
};

class MyceliumNetwork : public Passive {
public:
    MyceliumNetwork() : Passive("Mycelium Network", "+40% max HP, +10% armor", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.4f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        float armorBonus = owner.getStat(Stat::armor) * 0.1f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }
};

MushroomGuardian::MushroomGuardian(const std::string& n) : Enemy(n, "boss") {
    registerStat(Stat::hp, 280.0f);
    registerStat(Stat::max_hp, 280.0f);
    registerStat(Stat::armor, 15.0f);
    registerStat(Stat::attack, 20.0f);
    registerStat(Stat::crit_chance, 0.08f);
    registerStat(Stat::crit_damage, 0.4f);
    setExpValue(300);
    setBoss(true);

    skillSlots[0] = std::make_unique<SporeShot>();
    skillSlots[1] = std::make_unique<ToxicCloud>();
    skillSlots[2] = std::make_unique<FungalBloom>();

    addPassive(std::make_unique<MyceliumNetwork>());
}

std::string MushroomGuardian::className() const { return "Mushroom Guardian"; }
