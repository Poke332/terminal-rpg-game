#include "../../include/playable/archer/Ranger.h"
#include "../../include/playable/archer/ArcherEvoSkills.h"
#include "../../include/playable/archer/ArcherEvoPassive.h"
#include "../../include/passive/ArcherPassive.h"
#include "../../include/playable/archer/Sniper.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

Ranger::Ranger(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 100.0f);
        registerStat(Stat::max_hp, 100.0f);
        registerStat(Stat::armor, 2.0f);
        registerStat(Stat::attack, 24.0f);
        registerStat(Stat::damage_bonus, 0.08f);
        registerStat(Stat::crit_chance, 0.30f);
        registerStat(Stat::crit_damage, 1.2f);

        skillSlots[0] = std::make_unique<DeadlyShot>();
        skillSlots[1] = std::make_unique<ArrowStorm>();
        skillSlots[2] = std::make_unique<SwiftVolley>();

        evolution_ = 1;
        resourceName_ = Resource::focus;
        maxResource_ = 5;

        addPassive(std::make_unique<KeenEye>());
}

std::string Ranger::className() const {
    return "Ranger";
}

void Ranger::attack(Character& target) {
    Character::attack(target);
    if (target.isAlive()) {
        gainResource(1);
        std::cout << colorize("Focus +1! [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
    }
}

void Ranger::checkPassiveUnlock() {
    if (getLevel() == 10 && passives.size() < 2) {
        addPassive(std::make_unique<HuntersInstinct>());
    }
}

void Ranger::onCombatAction() {
    // Focus is gained on attack - handled in attack override
}

bool Ranger::canEvolve() const {
    return evolution_ < 2 && level_ >= 20;
}

void Ranger::evolve() {
    std::cout << colorize("=== EVOLUTION ===", Color::MAGENTA) << std::endl;
    std::cout << colorize("Ranger has evolved into Sniper!", Color::MAGENTA) << std::endl;
    Character::evolve();
}
