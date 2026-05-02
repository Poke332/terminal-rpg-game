#pragma once

#include "Skill.h"

class Fireball : public Skill {
public:
    Fireball();
    void skillImplementation(Character& user, Character& target) override;
};