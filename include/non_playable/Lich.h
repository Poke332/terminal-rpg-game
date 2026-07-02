#pragma once

#include "Enemy.h"

class Lich : public Enemy {
public:
    Lich(const std::string& n);
    std::string className() const override;
};
