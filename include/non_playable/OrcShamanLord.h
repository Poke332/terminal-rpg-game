#pragma once

#include "Enemy.h"

class Skill;

class OrcShamanLord : public Enemy {
public:
    OrcShamanLord(const std::string& n);
    std::string className() const override;
};
