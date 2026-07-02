#include "../include/passive/PriestPassive.h"
#include "../include/Character.h"
#include "../include/Ids.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>

using namespace Ids;

HolyBlessing::HolyBlessing() : Passive("Holy Blessing", "+5% healing bonus, +3 healing base", 15) {}

void HolyBlessing::onUnlock(Character& owner) {
    owner.modifyStat(Stat::healing_bonus_pct, std::make_unique<AddModifier>(0.05f));
    owner.modifyStat(Stat::healing_bonus_base, std::make_unique<AddModifier>(3.0f));
    std::cout << colorize("Holy Blessing unlocked! +5% Heal Bonus, +3 Heal Base", Color::GREEN) << std::endl;
}

DivineProtection::DivineProtection() : Passive("Divine Protection", "+3 armor, +20 max_hp", 30) {}

void DivineProtection::onUnlock(Character& owner) {
    owner.modifyStat(Stat::armor, std::make_unique<AddModifier>(3.0f));
    owner.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(20.0f));
    owner.modifyStat(Stat::hp, std::make_unique<AddModifier>(20.0f));
    std::cout << colorize("Divine Protection unlocked! +3 Armor, +20 HP", Color::GREEN) << std::endl;
}

MiracleWorker::MiracleWorker() : Passive("Miracle Worker", "+10% healing bonus, +5 healing base", 45) {}

void MiracleWorker::onUnlock(Character& owner) {
    owner.modifyStat(Stat::healing_bonus_pct, std::make_unique<AddModifier>(0.10f));
    owner.modifyStat(Stat::healing_bonus_base, std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("Miracle Worker unlocked! +10% Heal Bonus, +5 Heal Base", Color::GREEN) << std::endl;
}
