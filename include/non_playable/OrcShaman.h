#pragma once
#include "Enemy.h"

class OrcShaman : public Enemy {
public:
    OrcShaman(const std::string& n);
    std::string className() const override;
};
