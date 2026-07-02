#pragma once
#include "Skill.h"

class PowerShot : public Skill {
public:
    PowerShot();
    void skillImplementation(Character& user, Character& target) override;
};
