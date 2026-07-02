#include "../../include/playable/mage/Archmage.h"
#include "../../include/playable/mage/MageEvoSkills.h"
#include "../../include/playable/mage/MageEvoPassive.h"
#include "../../include/passive/MagePassive.h"
#include "../../include/utils.h"
#include <iostream>

Archmage::Archmage(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 130.0f);
        registerStat("max_hp", 130.0f);
        registerStat("armor", 5.0f);
        registerStat("attack", 32.0f);
        registerStat("crit_chance", 0.20f);
        registerStat("crit_damage", 0.8f);

        skillSlots[0] = std::make_unique<Hellfire>();
        skillSlots[1] = std::make_unique<ArcaneCataclysm>();
        skillSlots[2] = std::make_unique<AbsoluteZero>();

        evolution_ = 2;
        resourceName_ = "Focus";
        maxResource_ = 100;

        addPassive(std::make_unique<ArcanePower>());
}

std::string Archmage::className() const {
    return "Archmage";
}

void Archmage::useAbility(int slot, Character& target) {
    Player::useAbility(slot, target);
    gainResource(20);
    std::cout << colorize("Focus +20! [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
}

void Archmage::checkPassiveUnlock() {
    if (getLevel() == 5 && passives.size() < 2) {
        addPassive(std::make_unique<SpellAmplifier>());
    }
    if (getLevel() == 15 && passives.size() < 3) {
        addPassive(std::make_unique<ElementalMastery>());
    }
    if (getLevel() == 20) {
        setUltimateSkill(std::make_unique<ArcaneAnnihilation>());
        std::cout << colorize("ULTIMATE UNLOCKED: Arcane Annihilation!", Color::MAGENTA) << std::endl;
    }
}

void Archmage::onCombatAction() {
    // Focus is gained when casting skills
}
