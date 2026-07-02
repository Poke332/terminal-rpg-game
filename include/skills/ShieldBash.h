#pragma once
#include "Skill.h"

class ShieldBash : public Skill {
public:
    ShieldBash();
    void skillImplementation(Character& user, Character& target) override;
};
