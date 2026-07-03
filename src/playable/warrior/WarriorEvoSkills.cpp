#include "../../include/playable/warrior/WarriorEvoSkills.h"
#include "../../include/playable/warrior/Warrior.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

// Evo 1 Skills

FortressStance::FortressStance()
    : Skill("Fortress Stance",
            "Raises your shield in a fortified stance, blocking 70% of next hit and gaining +2 armor for 2 turns",
            SkillType::self_cast, 0.0f, 0.0f, 3) {}

void FortressStance::skillImplementation(Character& user, Character& target) {
    Warrior* warrior = dynamic_cast<Warrior*>(&user);
    if (warrior) warrior->setGuaranteeBlock(true);
    user.modifyStat(Stat::armor, std::make_unique<AddModifier>(2.0f, 2));
    std::cout << colorize("Fortress Stance! Blocking 70% of next hit, +2 armor for 2 turns!", Color::CYAN) << std::endl;
}

BattleCry::BattleCry()
    : Skill("Battle Cry",
            "Lets out a powerful battle cry, boosting own ATK by 8 and all allies ATK by 3",
            SkillType::aoe_ally, 0.0f, 0.0f, 4) {}

void BattleCry::skillImplementation(Character& user, Character& target) {
    user.modifyStat(Stat::attack, std::make_unique<AddModifier>(8.0f));
    std::cout << colorize("Battle Cry! ATK +8!", Color::YELLOW) << std::endl;
}

PowerBash::PowerBash()
    : Skill("Power Bash",
            "Slams the enemy with your shield, dealing damage and Weakening them for 3 turns (-5 ATK)",
            SkillType::single_cast_enemy, 8.0f, 0.25f, 2) {}

void PowerBash::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(-5.0f, 3));
    std::cout << colorize("Power Bash! Enemy Weakened for 3 turns! (-5 ATK)", Color::YELLOW) << std::endl;
}

// Evo 2 Skills

Bulwark::Bulwark()
    : Skill("Bulwark",
            "Raises an impenetrable bulwark, blocking 85% of next hit, gaining +5 armor for 2 turns, and healing 10 HP",
            SkillType::self_cast, 0.0f, 0.0f, 4) {}

void Bulwark::skillImplementation(Character& user, Character& target) {
    Warrior* warrior = dynamic_cast<Warrior*>(&user);
    if (warrior) warrior->setGuaranteeBlock(true);
    user.modifyStat(Stat::armor, std::make_unique<AddModifier>(5.0f, 2));
    user.heal(10.0f);
    std::cout << colorize("Bulwark! Blocking 85%, +5 armor, healed 10 HP!", Color::CYAN) << std::endl;
}

WarDrums::WarDrums()
    : Skill("War Drums",
            "Beats of war echo across the battlefield, boosting own ATK by 12, party ATK by 5, and party armor by 1",
            SkillType::aoe_ally, 0.0f, 0.0f, 5) {}

void WarDrums::skillImplementation(Character& user, Character& target) {
    user.modifyStat(Stat::attack, std::make_unique<AddModifier>(12.0f));
    std::cout << colorize("War Drums! ATK +12! War drums empower the party!", Color::YELLOW) << std::endl;
}

CrushingBlow::CrushingBlow()
    : Skill("Crushing Blow",
            "Delivers a devastating blow, dealing massive damage, -8 ATK and -2 armor for 3 turns",
            SkillType::single_cast_enemy, 12.0f, 0.35f, 3) {}

void CrushingBlow::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    target.modifyStat(Stat::attack, std::make_unique<AddModifier>(-8.0f, 3));
    target.modifyStat(Stat::armor, std::make_unique<AddModifier>(-2.0f, 3));
    std::cout << colorize("Crushing Blow! Enemy crippled! (-8 ATK, -2 Armor for 3T)", Color::RED) << std::endl;
}

TitansStrike::TitansStrike()
    : Skill("Titan's Strike",
            "Channels all rage into a single devastating blow dealing 300% ATK damage. Requires max rage.",
            SkillType::single_cast_enemy, 0.0f, 3.0f, 0) {}

void TitansStrike::skillImplementation(Character& user, Character& target) {
    float skillDamage = getFinalDamage(user.getAtkValue());
    target.takeDamage(skillDamage);
    std::cout << colorize("TITAN'S STRIKE! Unleashed all rage in a devastating blow!", Color::RED) << std::endl;
}
