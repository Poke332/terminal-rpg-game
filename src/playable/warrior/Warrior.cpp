#include "../../include/playable/warrior/Warrior.h"
#include "../../include/skills/ShieldBlock.h"
#include "../../include/skills/WarCry.h"
#include "../../include/skills/ShieldBash.h"
#include "../../include/passive/WarriorPassive.h"

#include <iostream>
#include <random>
#include "../../include/Ids.h"

using namespace Ids;

Warrior::Warrior(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 120.0f);
        registerStat(Stat::max_hp, 120.0f);
        registerStat(Stat::armor, 5.0f);
        registerStat(Stat::attack, 15.0f);
        registerStat(Stat::block_chance, 0.5f);
        registerStat(Stat::damage_reduction, 0.05f);
        registerStat(Stat::crit_chance, 0.05f);
        registerStat(Stat::crit_damage, 0.5f);

        skillSlots[0] = std::make_unique<ShieldBlock>();
        skillSlots[1] = std::make_unique<WarCry>();
        skillSlots[2] = std::make_unique<ShieldBash>();

        addPassive(std::make_unique<IronWill>());
}

std::string Warrior::className() const {
    return "Warrior";
}

void Warrior::takeDamage(float d) {
    for (auto& p : passives) p->onTakeDamage(*this, d);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    if (dist(rng) < static_cast<int>(getStat(Stat::block_chance) * 100) || guaranteeBlock) {
        guaranteeBlock = false;
        std::cout << "Damage blocked! Dmg taken has been reduced by 50%" << std::endl;
        Character::takeDamage(d * 0.5f);
        return;
    }
    Character::takeDamage(d);
}

void Warrior::setGuaranteeBlock(bool v) { guaranteeBlock = v; }

void Warrior::checkPassiveUnlock() {}
