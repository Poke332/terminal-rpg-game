#include "../../include/playable/mage/Sorcerer.h"
#include "../../include/playable/mage/MageEvoSkills.h"
#include "../../include/playable/mage/MageEvoPassive.h"
#include "../../include/passive/MagePassive.h"
#include "../../include/playable/mage/Archmage.h"
#include "../../include/utils.h"
#include <iostream>

Sorcerer::Sorcerer(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 110.0f);
        registerStat("max_hp", 110.0f);
        registerStat("armor", 4.0f);
        registerStat("attack", 25.0f);
        registerStat("crit_chance", 0.15f);
        registerStat("crit_damage", 0.6f);

        skillSlots[0] = std::make_unique<Inferno>();
        skillSlots[1] = std::make_unique<ArcaneBarrage>();
        skillSlots[2] = std::make_unique<GlacierNova>();

        evolution_ = 1;
        resourceName_ = "Focus";
        maxResource_ = 100;

        addPassive(std::make_unique<ArcanePower>());
}

std::string Sorcerer::className() const {
    return "Sorcerer";
}

void Sorcerer::useAbility(int slot, Character& target) {
    Player::useAbility(slot, target);
    gainResource(20);
    std::cout << colorize("Focus +20! [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
}

void Sorcerer::checkPassiveUnlock() {
    if (getLevel() == 10 && passives.size() < 2) {
        addPassive(std::make_unique<SpellAmplifier>());
    }
}

void Sorcerer::onCombatAction() {
    // Focus is gained when casting skills - handled in useAbility override
}

bool Sorcerer::canEvolve() const {
    return evolution_ < 2 && level_ >= 20;
}

void Sorcerer::evolve() {
    std::cout << colorize("=== EVOLUTION ===", Color::MAGENTA) << std::endl;
    std::cout << colorize("Sorcerer has evolved into Archmage!", Color::MAGENTA) << std::endl;
    Character::evolve();
}
