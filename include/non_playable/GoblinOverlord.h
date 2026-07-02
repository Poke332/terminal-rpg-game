#pragma once

#include "Enemy.h"

class Skill;

class GoblinOverlord : public Enemy {
public:
    GoblinOverlord(const std::string& n);
    std::string className() const override;
};
