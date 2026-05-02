#pragma once
#include "Player.h"

class Archer : public Player {
public:
    Archer(const std::string& n);
    std::string className() const override;
};