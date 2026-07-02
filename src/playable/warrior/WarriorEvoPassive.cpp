#include "../../include/playable/warrior/WarriorEvoPassive.h"
#include "../../include/Character.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/utils.h"
#include <iostream>

FuryUnleashed::FuryUnleashed()
    : Passive("Fury Unleashed", "ATK increases by 1 for every 10% HP missing", 1) {}

void FuryUnleashed::onUnlock(Character& owner) {
    std::cout << colorize("Fury Unleashed unlocked! ATK scales with missing HP!", Color::GREEN) << std::endl;
}

void FuryUnleashed::onTakeDamage(Character& owner, float& damage) {
    float hp = owner.getStat("hp");
    float maxHp = owner.getStat("max_hp");
    float missingPct = 1.0f - (hp / maxHp);
    int bonusAtk = static_cast<int>(missingPct * 10.0f);
    if (bonusAtk > 0) {
        owner.modifyStat("attack", std::make_unique<AddModifier>(static_cast<float>(bonusAtk), 1));
    }
}

WarlordsPresence::WarlordsPresence()
    : Passive("Warlord's Presence", "When an ally kills an enemy, gain +5 ATK stacking for combat", 1) {}

void WarlordsPresence::onUnlock(Character& owner) {
    std::cout << colorize("Warlord's Presence unlocked! Gains ATK when allies defeat enemies!", Color::GREEN) << std::endl;
}

void WarlordsPresence::onAttack(Character& owner, Character& target, float& damage) {
    float hp = owner.getStat("hp");
    float maxHp = owner.getStat("max_hp");
    if (hp < maxHp * 0.5f) {
        damage *= 1.15f;
    }
}
