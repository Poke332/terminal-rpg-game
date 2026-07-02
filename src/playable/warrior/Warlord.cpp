#include "../../include/playable/warrior/Warlord.h"
#include "../../include/playable/warrior/WarriorEvoSkills.h"
#include "../../include/playable/warrior/WarriorEvoPassive.h"
#include "../../include/passive/WarriorPassive.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include <random>
#include "../../include/Ids.h"

using namespace Ids;

Warlord::Warlord(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 180.0f);
        registerStat(Stat::max_hp, 180.0f);
        registerStat(Stat::armor, 10.0f);
        registerStat(Stat::attack, 22.0f);
        registerStat(Stat::block_chance, 0.55f);
        registerStat(Stat::damage_reduction, 0.12f);
        registerStat(Stat::crit_chance, 0.10f);
        registerStat(Stat::crit_damage, 0.7f);

        skillSlots[0] = std::make_unique<Bulwark>();
        skillSlots[1] = std::make_unique<WarDrums>();
        skillSlots[2] = std::make_unique<CrushingBlow>();

        evolution_ = 2;
        resourceName_ = Resource::rage;
        maxResource_ = 100;

        addPassive(std::make_unique<IronWill>());
}

std::string Warlord::className() const {
    return "Warlord";
}

void Warlord::takeDamage(float d) {
    for (auto& p : passives) p->onTakeDamage(*this, d);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < static_cast<int>(getStat(Stat::block_chance) * 100) || guaranteeBlock) {
        guaranteeBlock = false;
        std::cout << "Damage blocked! Dmg taken has been reduced by 85%" << std::endl;
        Character::takeDamage(d * 0.15f);
        gainResource(8);
        return;
    }
    Character::takeDamage(d);
    gainResource(static_cast<int>(d / 4.0f));
}

void Warlord::setGuaranteeBlock(bool v) { guaranteeBlock = v; }

void Warlord::checkPassiveUnlock() {
    if (getLevel() == 5 && passives.size() < 2) {
        addPassive(std::make_unique<FuryUnleashed>());
    }
    if (getLevel() == 15 && passives.size() < 3) {
        addPassive(std::make_unique<WarlordsPresence>());
    }
    if (getLevel() == 20) {
        setUltimateSkill(std::make_unique<TitansStrike>());
        std::cout << colorize("ULTIMATE UNLOCKED: Titan's Strike!", Color::MAGENTA) << std::endl;
    }
}

void Warlord::onCombatAction() {
    // Rage is built in takeDamage
}
