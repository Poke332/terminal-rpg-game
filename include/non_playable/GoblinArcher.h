#pragma once
#include "Enemy.h"

class GoblinArcher : public Enemy {
public:
    GoblinArcher(const std::string& n);
    std::string className() const override;
};