#pragma once

#include "Enemy.h"

class Skill;

class GemDragon : public Enemy {
public:
    GemDragon(const std::string& n);
    std::string className() const override;
};
