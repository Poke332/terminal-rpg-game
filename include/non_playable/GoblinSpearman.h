#pragma once
#include "Enemy.h"

class GoblinSpearman : public Enemy {
public:
    GoblinSpearman(const std::string& n);
    std::string className() const override;
};