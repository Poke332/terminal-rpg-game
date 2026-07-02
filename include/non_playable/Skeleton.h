#pragma once
#include "Enemy.h"

class Skeleton : public Enemy {
public:
    Skeleton(const std::string& n);
    std::string className() const override;
};
