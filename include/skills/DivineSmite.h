#pragma once
#include "Skill.h"

class DivineSmite : public Skill {
public:
    DivineSmite();
    void skillImplementation(Character& user, Character& target) override;
};
