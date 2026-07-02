#pragma once
#include "Skill.h"

class SoulDrain : public Skill {
public:
    SoulDrain();
    void skillImplementation(Character& user, Character& target) override;
};
