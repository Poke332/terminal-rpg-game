#pragma once

#include "Enemy.h"

class Skill;

class FireElementalLord : public Enemy {
public:
    FireElementalLord(const std::string& n);
    std::string className() const override;
};
