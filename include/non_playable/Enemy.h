#pragma once

#include "../Character.h"

class Enemy : public Character {
public:
    Enemy(const std::string& n, const std::string& t = "undefined");
    void useAbility(int slot, Character& target) override;
};