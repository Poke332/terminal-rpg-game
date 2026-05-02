#include "../../include/non_playable/Enemy.h"

Enemy::Enemy(const std::string& n, const std::string& t) :
    Character(n, t) {}

void Enemy::useAbility(int slot, Character& target) {
    // Enemy ignores slot parameter and just cast whichevery skill not on cooldown first
    for (const auto& skill : skillSlots) {
        if (skill && skill->isReady()) {
            skill->execute(*this, target);
        } 
    }
}