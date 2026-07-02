#pragma once
#include "Skill.h"

class Execute : public Skill {
public:
    Execute();
    void skillImplementation(Character& user, Character& target) override;
};
