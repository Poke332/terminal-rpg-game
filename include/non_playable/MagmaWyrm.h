#pragma once

#include "Enemy.h"

class Skill;

class MagmaWyrm : public Enemy {
public:
    MagmaWyrm(const std::string& n);
    std::string className() const override;
};
