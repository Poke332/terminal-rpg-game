#pragma once
#include "Enemy.h"

class GoblinChief : public Enemy {
public:
    GoblinChief(const std::string& n);
    std::string className() const override;
};