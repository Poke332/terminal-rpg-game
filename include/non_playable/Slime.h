#pragma once
#include "Enemy.h"

class Slime : public Enemy {
public:
    Slime(const std::string& n);
    std::string className() const override;
};
