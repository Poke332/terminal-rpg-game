#include "../../include/playable/Player.h"

Player::Player(const std::string& n, const std::string& t) :
    Character(n, t) {}

void Player::useAbility(int slot, Character& target) {
    //The choice for slot and target is left inside the Game class
    getSkill(slot)->execute(*this, target);
}