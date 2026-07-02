#pragma once

#include "Enemy.h"

class Skill;

class ShadowWraith : public Enemy {
public:
    ShadowWraith(const std::string& n);
    std::string className() const override;
};
