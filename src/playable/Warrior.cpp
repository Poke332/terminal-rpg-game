#include "../../include/playable/Warrior.h"
#include "../../include/skills/ShieldBlock.h"

#include <iostream>

Warrior::Warrior(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 120.0f);
        registerStat("max_hp", 120.0f);
        registerStat("armor", 5.0f);
        registerStat("attack", 15.0f);
        registerStat("block_chance", 0.5f);
        registerStat("damage_reduction", 0.05f);
        registerStat("crit_chance", 0.05f);
        registerStat("crit_damage", 0.5f);

        skillSlots[0] = std::make_unique<ShieldBlock>();
}

std::string Warrior::className() const {
    return "Warrior";
}

void Warrior::takeDamage(float d) {
    if (rand() % 100 < (static_cast<int>(getStat("block_chance")*100)) || guaranteeBlock) {
        std::cout << "Damage blocked! Dmg taken has been reduced by 50%" << std::endl;
        Character::takeDamage(d*0.5f);
        return;
    } else {
        Character::takeDamage(d);
    }
}

void Warrior::setGuaranteeBlock(bool v) { guaranteeBlock = v; }