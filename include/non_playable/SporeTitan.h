#pragma once

#include "Enemy.h"

class Skill;

class SporeTitan : public Enemy {
public:
    SporeTitan(const std::string& n);
    std::string className() const override;
};
