#include "../../include/playable/archer/Sniper.h"
#include "../../include/playable/archer/ArcherEvoSkills.h"
#include "../../include/playable/archer/ArcherEvoPassive.h"
#include "../../include/passive/ArcherPassive.h"
#include "../../include/utils.h"
#include <iostream>
#include <random>
#include "../../include/Ids.h"

using namespace Ids;

Sniper::Sniper(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 120.0f);
        registerStat(Stat::max_hp, 120.0f);
        registerStat(Stat::armor, 3.0f);
        registerStat(Stat::attack, 30.0f);
        registerStat(Stat::damage_bonus, 0.12f);
        registerStat(Stat::crit_chance, 0.35f);
        registerStat(Stat::crit_damage, 1.5f);

        skillSlots[0] = std::make_unique<ExecutionersShot>();
        skillSlots[1] = std::make_unique<TempestVolley>();
        skillSlots[2] = std::make_unique<RapidFire>();

        evolution_ = 2;
        resourceName_ = Resource::focus;
        maxResource_ = 5;

        addPassive(std::make_unique<KeenEye>());
}

std::string Sniper::className() const {
    return "Sniper";
}

void Sniper::attack(Character& target) {
    Character::attack(target);
    if (target.isAlive()) {
        gainResource(1);
        std::cout << colorize("Focus +1! [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
    }
}

void Sniper::checkPassiveUnlock() {
    if (getLevel() == 5 && passives.size() < 2) {
        addPassive(std::make_unique<HuntersInstinct>());
    }
    if (getLevel() == 15 && passives.size() < 3) {
        addPassive(std::make_unique<EagleVision>());
    }
    if (getLevel() == 20) {
        setUltimateSkill(std::make_unique<PerfectShot>());
        std::cout << colorize("ULTIMATE UNLOCKED: Perfect Shot!", Color::MAGENTA) << std::endl;
    }
}

void Sniper::onCombatAction() {
    // Focus is gained on attack
}

void Sniper::takeDamage(float d) {
    Character::takeDamage(d);
    resource_ = 0;
    std::cout << colorize("Focus lost! Took damage!", Color::YELLOW) << std::endl;
}
