#pragma once

#include "Enemy.h"

class Skill;

class GoblinKing : public Enemy {
public:
    GoblinKing(const std::string& n);
    std::string className() const override;
};
