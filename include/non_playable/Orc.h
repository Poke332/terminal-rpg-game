#pragma once
#include "Enemy.h"

class Orc : public Enemy {
public:
    Orc(const std::string& n);
    std::string className() const override;
};
