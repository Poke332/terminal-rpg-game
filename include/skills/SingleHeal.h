#pragma once

#include "Skill.h"

class SingleHeal : public Skill {
public:
    SingleHeal();
    void skillImplementation(Character& user, Character& target) override;
};