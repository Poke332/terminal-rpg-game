#pragma once
#include "Skill.h"

class FrostNova : public Skill {
public:
    FrostNova();
    void skillImplementation(Character& user, Character& target) override;
};
