#pragma once

#include "../Character.h"

class Player : public Character {
public:
    Player(const std::string& n, const std::string& t = "undefined");
    void useAbility(int slot, Character& target) override;
};