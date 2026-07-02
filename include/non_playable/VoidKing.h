#pragma once

#include "Enemy.h"

class Skill;

class VoidKing : public Enemy {
public:
    VoidKing(const std::string& n);
    std::string className() const override;
};
