#pragma once
#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin(const std::string& n);
    std::string className() const override;
};