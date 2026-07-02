#include "../../include/playable/warrior/Berserker.h"
#include "../../include/playable/warrior/WarriorEvoSkills.h"
#include "../../include/playable/warrior/WarriorEvoPassive.h"
#include "../../include/passive/WarriorPassive.h"
#include "../../include/playable/warrior/Warlord.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>
#include <random>

Berserker::Berserker(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 140.0f);
        registerStat("max_hp", 140.0f);
        registerStat("armor", 7.0f);
        registerStat("attack", 18.0f);
        registerStat("block_chance", 0.5f);
        registerStat("damage_reduction", 0.08f);
        registerStat("crit_chance", 0.08f);
        registerStat("crit_damage", 0.6f);

        skillSlots[0] = std::make_unique<FortressStance>();
        skillSlots[1] = std::make_unique<BattleCry>();
        skillSlots[2] = std::make_unique<PowerBash>();

        evolution_ = 1;
        resourceName_ = "Rage";
        maxResource_ = 100;

        addPassive(std::make_unique<IronWill>());
}

std::string Berserker::className() const {
    return "Berserker";
}

void Berserker::takeDamage(float d) {
    for (auto& p : passives) p->onTakeDamage(*this, d);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < static_cast<int>(getStat("block_chance") * 100) || guaranteeBlock) {
        guaranteeBlock = false;
        std::cout << "Damage blocked! Dmg taken has been reduced by 70%" << std::endl;
        Character::takeDamage(d * 0.3f);
        gainResource(5);
        return;
    }
    Character::takeDamage(d);
    gainResource(static_cast<int>(d / 5.0f));
}

void Berserker::setGuaranteeBlock(bool v) { guaranteeBlock = v; }

void Berserker::checkPassiveUnlock() {
    if (getLevel() == 10 && passives.size() < 2) {
        addPassive(std::make_unique<FuryUnleashed>());
    }
}

void Berserker::onCombatAction() {
    // Rage is built in takeDamage
}

bool Berserker::canEvolve() const {
    return evolution_ < 2 && level_ >= 20;
}

void Berserker::evolve() {
    std::cout << colorize("=== EVOLUTION ===", Color::MAGENTA) << std::endl;
    std::cout << colorize("Berserker has evolved into Warlord!", Color::MAGENTA) << std::endl;
    Character::evolve();
}
