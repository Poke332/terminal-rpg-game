#pragma once

#include "Skill.h"

class PrecisionShot : public Skill {
public:
    PrecisionShot();
    void skillImplementation(Character& user, Character& target) override;
};