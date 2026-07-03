#include "../../include/playable/priest/PriestEvoSkills.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/stats/StatusEffect.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

// Evo 1 Skills

MassHeal::MassHeal()
    : Skill("Mass Heal",
            "Channels divine power to heal all allies for 60% of normal healing potency",
            SkillType::aoe_ally, 6.0f, 0.0f, 5) {}

void MassHeal::skillImplementation(Character& user, Character& target) {
    float userBaseHeal = user.getStat(Stat::healing_bonus_base);
    float userPercentHeal = user.getStat(Stat::healing_bonus_pct);
    float baseAttack = user.getStat(Stat::attack);
    float healTotal = (baseScale + userBaseHeal + baseAttack) * (1 + userPercentHeal + percentScale) * 0.6f;
    target.heal(healTotal);
    std::cout << colorize("Mass Heal! Divine light washes over the party!", Color::GREEN) << std::endl;
}

HolyWrath::HolyWrath()
    : Skill("Holy Wrath",
            "Channels holy wrath to smite an enemy, healing the user for 30% of damage dealt",
            SkillType::single_cast_enemy, 12.0f, 0.3f, 3) {}

void HolyWrath::skillImplementation(Character& user, Character& target) {
    float baseDmg = getFinalDamage(user.getAtkValue());
    float healingBonus = user.getStat(Stat::healing_bonus_pct);
    float healBase = user.getStat(Stat::healing_bonus_base);
    float skillDamage = baseDmg * (1.0f + healingBonus) + healBase;
    target.takeDamage(skillDamage);
    float healAmount = skillDamage * 0.3f;
    user.heal(healAmount);
    std::cout << colorize("Holy Wrath! Holy fire burns the enemy! Healed for " + std::to_string(static_cast<int>(healAmount)) + " HP!", Color::YELLOW) << std::endl;
}

DivineFavor::DivineFavor()
    : Skill("Divine Favor",
            "Bestows divine favor, increasing an ally's ATK by 8 and healing them for a small amount",
            SkillType::single_cast_ally, 5.0f, 0.0f, 4) {}

void DivineFavor::skillImplementation(Character& user, Character& target) {
    float userBaseHeal = user.getStat(Stat::healing_bonus_base);
    float userPercentHeal = user.getStat(Stat::healing_bonus_pct);
    float baseAttack = user.getStat(Stat::attack);
    float healTotal = (baseScale + userBaseHeal + baseAttack) * (1 + userPercentHeal + percentScale);
    target.heal(healTotal);
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(8.0f));
    std::cout << colorize("Divine Favor! " + target.className() + "'s ATK +8 and healed!", Color::GREEN) << std::endl;
}

// Evo 2 Skills

SanctuaryHeal::SanctuaryHeal()
    : Skill("Sanctuary",
            "Creates a sanctuary of healing, healing all allies to full and granting a divine shield (10% max HP)",
            SkillType::aoe_ally, 0.0f, 0.0f, 6) {}

void SanctuaryHeal::skillImplementation(Character& user, Character& target) {
    float maxHp = target.getStat(Stat::max_hp);
    target.heal(maxHp);
    std::cout << colorize("Sanctuary! " + target.className() + " fully healed and shielded!", Color::GREEN) << std::endl;
}

Judgment::Judgment()
    : Skill("Judgment",
            "Passes judgment on an enemy, dealing massive damage and healing all allies for 20% of damage dealt",
            SkillType::single_cast_enemy, 18.0f, 0.4f, 4) {}

void Judgment::skillImplementation(Character& user, Character& target) {
    float baseDmg = getFinalDamage(user.getAtkValue());
    float healingBonus = user.getStat(Stat::healing_bonus_pct);
    float skillDamage = baseDmg * (1.0f + healingBonus);
    target.takeDamage(skillDamage);
    std::cout << colorize("JUDGMENT! Divine judgment falls upon the enemy! Party healed for 20% of damage!", Color::YELLOW) << std::endl;
}

HolyCovenant::HolyCovenant()
    : Skill("Holy Covenant",
            "Forms a holy covenant with an ally, boosting ATK by 12, healing for 20 HP, and granting +2 armor",
            SkillType::single_cast_ally, 20.0f, 0.0f, 5) {}

void HolyCovenant::skillImplementation(Character& user, Character& target) {
    float userBaseHeal = user.getStat(Stat::healing_bonus_base);
    float userPercentHeal = user.getStat(Stat::healing_bonus_pct);
    float baseAttack = user.getStat(Stat::attack);
    float healTotal = (baseScale + userBaseHeal + baseAttack) * (1 + userPercentHeal + percentScale);
    target.heal(healTotal);
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(12.0f));
    target.modifyStat(Stat::armor, std::make_unique<AddModifier>(2.0f));
    std::cout << colorize("Holy Covenant! " + target.className() + " blessed with power! ATK +12, Armor +2!", Color::GREEN) << std::endl;
}

DivineIntervention::DivineIntervention()
    : Skill("Divine Intervention",
            "Calls upon divine power to fully heal all allies and grant 50% damage reduction for 2 turns. Requires 5 meditation.",
            SkillType::aoe_ally, 0.0f, 0.0f, 0) {}

void DivineIntervention::skillImplementation(Character& user, Character& target) {
    target.heal(target.getStat(Stat::max_hp));
    target.modifyStat(Stat::damage_reduction, std::make_unique<AddModifier>(0.50f, 2));
    std::cout << colorize("DIVINE INTERVENTION! Divine light fully heals and protects " + target.className() + "!", Color::YELLOW) << std::endl;
}
