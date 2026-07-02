#pragma once

#include "Enemy.h"

class Skill;

class CrystalGolem : public Enemy {
public:
    CrystalGolem(const std::string& n);
    std::string className() const override;
};
