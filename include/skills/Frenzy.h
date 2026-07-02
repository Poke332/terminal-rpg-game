#pragma once
#include "Skill.h"

class Frenzy : public Skill {
public:
    Frenzy();
    void skillImplementation(Character& user, Character& target) override;
};
