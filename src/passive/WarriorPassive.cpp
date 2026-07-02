#include "../include/passive/WarriorPassive.h"
#include "../include/Character.h"
#include "../include/stats/AddModifier.h"
#include "../include/utils.h"
#include <iostream>

IronWill::IronWill() : Passive("Iron Will", "+20 max_hp, +3 armor", 15) {}

void IronWill::onUnlock(Character& owner) {
    owner.modifyStat("max_hp", std::make_unique<AddModifier>(20.0f));
    owner.modifyStat("hp", std::make_unique<AddModifier>(20.0f));
    owner.modifyStat("armor", std::make_unique<AddModifier>(3.0f));
    std::cout << colorize("Iron Will unlocked! +20 HP, +3 Armor", Color::GREEN) << std::endl;
}

Veteran::Veteran() : Passive("Veteran", "+3 armor, +5% damage reduction", 30) {}

void Veteran::onUnlock(Character& owner) {
    owner.modifyStat("armor", std::make_unique<AddModifier>(3.0f));
    owner.modifyStat("damage_reduction", std::make_unique<AddModifier>(0.05f));
    std::cout << colorize("Veteran unlocked! +3 Armor, +5% DMG Reduction", Color::GREEN) << std::endl;
}

Unbreakable::Unbreakable() : Passive("Unbreakable", "+10% block chance. Halve damage when HP<20%", 45) {}

void Unbreakable::onUnlock(Character& owner) {
    owner.modifyStat("block_chance", std::make_unique<AddModifier>(0.10f));
    std::cout << colorize("Unbreakable unlocked! +10% Block. Damage halved at critical HP!", Color::GREEN) << std::endl;
}

void Unbreakable::onTakeDamage(Character& owner, float& damage) {
    float hp = owner.getStat("hp");
    float maxHp = owner.getStat("max_hp");
    if (hp < maxHp * 0.2f && hp > 0) {
        damage *= 0.5f;
        std::cout << colorize("Unbreakable! Damage halved at critical HP!", Color::YELLOW) << std::endl;
    }
}
