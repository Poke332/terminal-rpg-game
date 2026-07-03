#include "../../include/non_playable/Enemy.h"

Enemy::Enemy(const std::string& n, const std::string& t) :
    Character(n, t) {}

void Enemy::useAbility(int slot, Character& target) {
    Skill* skill = getSkill(slot);
    if (skill) skill->execute(*this, target);
}