#pragma once

#include "Enemy.h"

class AncientDragon : public Enemy {
public:
    AncientDragon(const std::string& n);
    std::string className() const override;
};
