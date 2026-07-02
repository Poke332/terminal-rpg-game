#pragma once

#include "Enemy.h"

class Skill;

class MushroomGuardian : public Enemy {
public:
    MushroomGuardian(const std::string& n);
    std::string className() const override;
};
