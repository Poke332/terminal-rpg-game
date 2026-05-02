#pragma once

#include "Skill.h"

class ShieldBlock : public Skill {
public:
    ShieldBlock();
    void skillImplementation(Character& user, Character& target) override;
};