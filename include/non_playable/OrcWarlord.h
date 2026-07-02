#pragma once

#include "Enemy.h"

class OrcWarlord : public Enemy {
public:
    OrcWarlord(const std::string& n);
    std::string className() const override;
};
