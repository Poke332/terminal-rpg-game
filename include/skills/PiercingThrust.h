#pragma once
#include "Skill.h"

class PiercingThrust : public Skill {
public:
    PiercingThrust();
    void skillImplementation(Character& user, Character& target) override;
};
