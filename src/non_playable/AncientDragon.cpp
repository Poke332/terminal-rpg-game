#include "../../include/non_playable/AncientDragon.h"
#include "../../include/skills/Skill.h"
#include "../../include/passive/Passive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/PercentModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include "../../include/Ids.h"

#include <iostream>
#include <random>
#include <string>

using namespace Ids;

static const char* LATIN_NAMES[] = {
    "Ignis", "Ferrum", "Umbra", "Nox", "Sol",
    "Luna", "Terra", "Ventus", "Aqua", "Pyxis",
    "Aether", "Draco", "Rex", "Mortis", "Vita",
    "Caelum", "Vertex", "Aegis", "Veritas", "Fortuna"
};

const char* AncientDragon::randomLatinName() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 19);
    return LATIN_NAMES[dist(rng)];
}

const char* AncientDragon::elementName(Element elem) {
    switch (elem) {
        case Element::INFERNO: return "Inferno";
        case Element::FROST: return "Frost";
        case Element::STORM: return "Storm";
        case Element::SHADOW: return "Shadow";
        case Element::PRIMORDIAL: return "Primordial";
        default: return "Unknown";
    }
}

// ========== INFERNO DRAGON SKILLS ==========

class FlameClaw : public Skill {
public:
    FlameClaw() : Skill("Flame Claw", "Slashes with burning claws, applying Burning for 3 turns", SkillType::single_cast_enemy, 8.4f, 0.28f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 5.0f + dmg * 0.1f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDmg, 3));
        std::cout << colorize("Flaw Claw! Burning applied!", Color::RED) << std::endl;
    }
};

class InfernoBreath : public Skill {
public:
    InfernoBreath() : Skill("Inferno Breath", "Breathes searing flames for massive damage", SkillType::single_cast_enemy, 12.6f, 0.35f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Inferno Breath! " + std::to_string(static_cast<int>(dmg)) + " fire damage!", Color::RED) << std::endl;
    }
};

class MagmaEruption : public Skill {
public:
    MagmaEruption() : Skill("Magma Eruption", "Erupts magma from below, dealing damage and reducing armor by 10 for 3 turns", SkillType::single_cast_enemy, 10.5f, 0.32f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-10.0f, 3));
        std::cout << colorize("Magma Eruption! Armor reduced by 10!", Color::RED) << std::endl;
    }
};

class InfernoFireball : public Skill {
public:
    InfernoFireball() : Skill("Dragon Fireball", "Launches a massive fireball dealing high damage and applying Burning for 4 turns", SkillType::single_cast_enemy, 14.0f, 0.35f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float dotDmg = 8.0f + dmg * 0.15f;
        target.addStatusEffect(std::make_unique<DamageOverTime>(EffectName::burning, "\xF0\x9F\x94\xA5", dotDmg, 4));
        std::cout << colorize("Dragon Fireball! Massive fire damage!", Color::RED) << std::endl;
    }
};

class InfernoUltimate : public Skill {
public:
    InfernoUltimate() : Skill("Dragon's Wrath", "ULTIMATE - Unleashes apocalyptic fire for enormous damage and heals 30%", SkillType::single_cast_enemy, 35.0f, 0.7f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("DRAGON'S WRATH! " + std::to_string(static_cast<int>(dmg)) + " APOCALYPTIC FIRE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::RED) << std::endl;
    }
};

class DragonScales : public Passive {
public:
    DragonScales() : Passive("Dragon Scales", "+30% max HP, +10% armor", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.3f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        float armorBonus = owner.getStat(Stat::armor) * 0.1f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }
};

class FlameAura : public Passive {
public:
    FlameAura() : Passive("Flame Aura", "Reflects 15% of incoming damage back to attacker", 1) {}
    void onTakeDamage(Character& owner, float& damage) override {
        // Flame aura effect - damage reflection is handled conceptually
    }
};

// ========== FROST DRAGON SKILLS ==========

class FrostBite : public Skill {
public:
    FrostBite() : Skill("Frost Bite", "Bites with frozen fangs, Chilling the target (-15% ATK, -50% crit) for 3 turns", SkillType::single_cast_enemy, 8.4f, 0.28f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-15.0f, 3));
        target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-50.0f, 3));
        std::cout << colorize("Frost Bite! Chilled for 3 turns!", Color::CYAN) << std::endl;
    }
};

class IceLance : public Skill {
public:
    IceLance() : Skill("Ice Lance", "Hurls a piercing lance of ice for high damage", SkillType::single_cast_enemy, 11.2f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Ice Lance! " + std::to_string(static_cast<int>(dmg)) + " ice damage!", Color::CYAN) << std::endl;
    }
};

class Blizzard : public Skill {
public:
    Blizzard() : Skill("Blizzard", "Summons a blizzard, dealing damage and reducing attack by 20% for 3 turns", SkillType::aoe_enemy, 12.6f, 0.32f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-20.0f, 3));
        std::cout << colorize("Blizzard! Attack reduced by 20%!", Color::CYAN) << std::endl;
    }
};

class FrostNova : public Skill {
public:
    FrostNova() : Skill("Frost Nova", "Erupts a nova of frost, dealing damage and freezing target (-30% ATK, -100% crit) for 2 turns", SkillType::single_cast_enemy, 14.0f, 0.35f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-30.0f, 2));
        target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-100.0f, 2));
        std::cout << colorize("Frost Nova! Frozen solid!", Color::CYAN) << std::endl;
    }
};

class AbsoluteZero : public Skill {
public:
    AbsoluteZero() : Skill("Absolute Zero", "ULTIMATE - Freezes reality itself for enormous damage and applies deep freeze", SkillType::single_cast_enemy, 35.0f, 0.7f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-40.0f, 3));
        target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-100.0f, 3));
        float healAmt = dmg * 0.25f;
        user.heal(healAmt);
        std::cout << colorize("ABSOLUTE ZERO! " + std::to_string(static_cast<int>(dmg)) + " FROZEN DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::CYAN) << std::endl;
    }
};

class IceArmor : public Passive {
public:
    IceArmor() : Passive("Ice Armor", "+30% armor, enemies deal 20% less damage", 1) {}
    void onUnlock(Character& owner) override {
        float armorBonus = owner.getStat(Stat::armor) * 0.3f;
        owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.20f));
    }
};

class Frostbite : public Passive {
public:
    Frostbite() : Passive("Frostbite", "Attacks apply Chilled for 1 turn", 1) {}
    void onAttack(Character& owner, Character& target, float& damage) override {
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-10.0f, 1));
    }
};

// ========== STORM DRAGON SKILLS ==========

class LightningClaw : public Skill {
public:
    LightningClaw() : Skill("Lightning Claw", "Strikes with electrified claws, dealing bonus damage", SkillType::single_cast_enemy, 9.8f, 0.32f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Lightning Claw! " + std::to_string(static_cast<int>(dmg)) + " electric damage!", Color::YELLOW) << std::endl;
    }
};

class ChainLightning : public Skill {
public:
    ChainLightning() : Skill("Chain Lightning", "Hurls chain lightning, dealing high damage and reducing armor by 8 for 2 turns", SkillType::single_cast_enemy, 11.2f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-8.0f, 2));
        std::cout << colorize("Chain Lightning! Armor reduced by 8!", Color::YELLOW) << std::endl;
    }
};

class ThunderStorm : public Skill {
public:
    ThunderStorm() : Skill("Thunder Storm", "Summons a storm of thunder, dealing damage and reducing crit chance by 30%", SkillType::aoe_enemy, 12.6f, 0.32f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::crit_chance, std::make_unique<PercentModifier>(-30.0f, 3));
        std::cout << colorize("Thunder Storm! Crit reduced by 30%!", Color::YELLOW) << std::endl;
    }
};

class StormArcaneBlast : public Skill {
public:
    StormArcaneBlast() : Skill("Arcane Tempest", "Unleashes a tempest of arcane energy for massive damage", SkillType::single_cast_enemy, 15.4f, 0.39f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Arcane Tempest! " + std::to_string(static_cast<int>(dmg)) + " storm damage!", Color::YELLOW) << std::endl;
    }
};

class JudgmentOfStorm : public Skill {
public:
    JudgmentOfStorm() : Skill("Judgment of Storm", "ULTIMATE - Calls down divine lightning for enormous damage and heals 25%", SkillType::single_cast_enemy, 38.5f, 0.77f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.25f;
        user.heal(healAmt);
        std::cout << colorize("JUDGMENT OF STORM! " + std::to_string(static_cast<int>(dmg)) + " DIVINE LIGHTNING! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::YELLOW) << std::endl;
    }
};

class StaticField : public Passive {
public:
    StaticField() : Passive("Static Field", "+25% crit chance, +15% crit damage", 1) {}
    void onUnlock(Character& owner) override {
        owner.modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.25f));
        owner.modifyStat(Stat::crit_damage, std::make_unique<AddModifier>(0.15f));
    }
};

class Thunderlord : public Passive {
public:
    Thunderlord() : Passive("Thunderlord", "Attacks have 20% chance to deal double damage", 1) {}
    void onAttack(Character& owner, Character& target, float& damage) override {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 99);
        if (dist(rng) < 20) {
            damage *= 2.0f;
            std::cout << colorize("Thunderlord! Double damage!", Color::YELLOW) << std::endl;
        }
    }
};

// ========== SHADOW DRAGON SKILLS ==========

class ShadowStrike : public Skill {
public:
    ShadowStrike() : Skill("Shadow Strike", "Strikes from the shadows, dealing damage and reducing attack by 10%", SkillType::single_cast_enemy, 9.8f, 0.28f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-10.0f, 2));
        std::cout << colorize("Shadow Strike! Attack reduced by 10%!", Color::MAGENTA) << std::endl;
    }
};

class DarkPulse : public Skill {
public:
    DarkPulse() : Skill("Dark Pulse", "Emits a pulse of dark energy for high damage", SkillType::single_cast_enemy, 11.2f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Dark Pulse! " + std::to_string(static_cast<int>(dmg)) + " dark damage!", Color::MAGENTA) << std::endl;
    }
};

class CurseOfDarkness : public Skill {
public:
    CurseOfDarkness() : Skill("Curse of Darkness", "Curses the target, reducing all stats by 15% for 3 turns", SkillType::single_cast_enemy, 8.4f, 0.25f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-15.0f, 3));
        target.modifyStat(Stat::armor, std::make_unique<PercentModifier>(-15.0f, 3));
        std::cout << colorize("Curse of Darkness! Stats reduced by 15%!", Color::MAGENTA) << std::endl;
    }
};

class ShadowBolt : public Skill {
public:
    ShadowBolt() : Skill("Shadow Bolt", "Hurls a bolt of shadow energy for massive damage", SkillType::single_cast_enemy, 14.0f, 0.35f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Shadow Bolt! " + std::to_string(static_cast<int>(dmg)) + " shadow damage!", Color::MAGENTA) << std::endl;
    }
};

class VoidRequiem : public Skill {
public:
    VoidRequiem() : Skill("Void Requiem", "ULTIMATE - Channels the void for enormous damage and heals 35%", SkillType::single_cast_enemy, 33.6f, 0.67f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.35f;
        user.heal(healAmt);
        std::cout << colorize("VOID REQUIEM! " + std::to_string(static_cast<int>(dmg)) + " VOID DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::MAGENTA) << std::endl;
    }
};

class ShadowCloak : public Passive {
public:
    ShadowCloak() : Passive("Shadow Cloak", "20% dodge chance, +15% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.15f));
    }
};

class CurseOfWeakness : public Passive {
public:
    CurseOfWeakness() : Passive("Curse of Weakness", "Enemies deal 15% less damage", 1) {}
    void onUnlock(Character& owner) override {
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.15f));
    }
};

// ========== PRIMORDIAL DRAGON SKILLS ==========

class TectonicSlam : public Skill {
public:
    TectonicSlam() : Skill("Tectonic Slam", "Slams the ground with earth-shattering force, reducing armor by 12 for 3 turns", SkillType::single_cast_enemy, 10.5f, 0.32f, 2) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-12.0f, 3));
        std::cout << colorize("Tectonic Slam! Armor reduced by 12!", Color::GREEN) << std::endl;
    }
};

class BoulderCrush : public Skill {
public:
    BoulderCrush() : Skill("Boulder Crush", "Hurls a massive boulder for high damage", SkillType::single_cast_enemy, 12.6f, 0.35f, 3) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Boulder Crush! " + std::to_string(static_cast<int>(dmg)) + " earth damage!", Color::GREEN) << std::endl;
    }
};

class Earthquake : public Skill {
public:
    Earthquake() : Skill("Earthquake", "Causes an earthquake, dealing damage and reducing attack by 20% for 3 turns", SkillType::aoe_enemy, 14.0f, 0.35f, 5) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        target.modifyStat(Stat::attack, std::make_unique<PercentModifier>(-20.0f, 3));
        std::cout << colorize("Earthquake! Attack reduced by 20%!", Color::GREEN) << std::endl;
    }
};

class PrimordialArcaneBlast : public Skill {
public:
    PrimordialArcaneBlast() : Skill("Primordial Force", "Channels primordial energy for massive damage", SkillType::single_cast_enemy, 15.4f, 0.39f, 4) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        std::cout << colorize("Primordial Force! " + std::to_string(static_cast<int>(dmg)) + " primal damage!", Color::GREEN) << std::endl;
    }
};

class WorldBreaker : public Skill {
public:
    WorldBreaker() : Skill("World Breaker", "ULTIMATE - Shatters the earth for enormous damage and heals 30%", SkillType::single_cast_enemy, 36.4f, 0.74f, 12) {}
    void skillImplementation(Character& user, Character& target) override {
        float dmg = getFinalDamage(user.getAtkValue());
        target.takeDamage(dmg);
        float healAmt = dmg * 0.3f;
        user.heal(healAmt);
        std::cout << colorize("WORLD BREAKER! " + std::to_string(static_cast<int>(dmg)) + " CATASTROPHIC DAMAGE! Healed " + std::to_string(static_cast<int>(healAmt)) + "!", Color::GREEN) << std::endl;
    }
};

class PrimordialShield : public Passive {
public:
    PrimordialShield() : Passive("Primordial Shield", "+60% max HP, +10% damage reduction", 1) {}
    void onUnlock(Character& owner) override {
        float hpBonus = owner.getStat(Stat::max_hp) * 0.6f;
        owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
        owner.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.10f));
    }
};

class AncientPower : public Passive {
public:
    AncientPower() : Passive("Ancient Power", "+30% attack scaling", 1) {}
    void onUnlock(Character& owner) override {
        float atkBonus = owner.getStat(Stat::attack) * 0.3f;
        owner.modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
    }
};

// ========== CONSTRUCTOR ==========

AncientDragon::AncientDragon(Element elem, const std::string& latinName)
    : Enemy(latinName, "boss"), element_(elem), latinName_(latinName) {

    displayName_ = std::string(elementName(element_)) + " Dragon";

    registerStat(Stat::hp, 300.0f);
    registerStat(Stat::max_hp, 300.0f);
    registerStat(Stat::armor, 15.0f);
    registerStat(Stat::attack, 30.0f);
    registerStat(Stat::crit_chance, 0.15f);
    registerStat(Stat::crit_damage, 1.0f);
    setExpValue(800);
    setBoss(true);

    switch (element_) {
        case Element::INFERNO:
            skillSlots[0] = std::make_unique<FlameClaw>();
            skillSlots[1] = std::make_unique<InfernoBreath>();
            skillSlots[2] = std::make_unique<MagmaEruption>();
            skillSlots[3] = std::make_unique<InfernoFireball>();
            addPassive(std::make_unique<DragonScales>());
            addPassive(std::make_unique<FlameAura>());
            break;
        case Element::FROST:
            skillSlots[0] = std::make_unique<FrostBite>();
            skillSlots[1] = std::make_unique<IceLance>();
            skillSlots[2] = std::make_unique<Blizzard>();
            skillSlots[3] = std::make_unique<FrostNova>();
            addPassive(std::make_unique<IceArmor>());
            addPassive(std::make_unique<Frostbite>());
            break;
        case Element::STORM:
            skillSlots[0] = std::make_unique<LightningClaw>();
            skillSlots[1] = std::make_unique<ChainLightning>();
            skillSlots[2] = std::make_unique<ThunderStorm>();
            skillSlots[3] = std::make_unique<StormArcaneBlast>();
            addPassive(std::make_unique<StaticField>());
            addPassive(std::make_unique<Thunderlord>());
            break;
        case Element::SHADOW:
            skillSlots[0] = std::make_unique<ShadowStrike>();
            skillSlots[1] = std::make_unique<DarkPulse>();
            skillSlots[2] = std::make_unique<CurseOfDarkness>();
            skillSlots[3] = std::make_unique<ShadowBolt>();
            addPassive(std::make_unique<ShadowCloak>());
            addPassive(std::make_unique<CurseOfWeakness>());
            break;
        case Element::PRIMORDIAL:
            skillSlots[0] = std::make_unique<TectonicSlam>();
            skillSlots[1] = std::make_unique<BoulderCrush>();
            skillSlots[2] = std::make_unique<Earthquake>();
            skillSlots[3] = std::make_unique<PrimordialArcaneBlast>();
            addPassive(std::make_unique<PrimordialShield>());
            addPassive(std::make_unique<AncientPower>());
            break;
    }
}

std::string AncientDragon::className() const { return displayName_; }

void AncientDragon::useAbility(int slot, Character& target) {
    Skill* skill = getSkill(slot);
    if (skill) skill->execute(*this, target);
}
