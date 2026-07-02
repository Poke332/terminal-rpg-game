#pragma once
#include "Skill.h"

class Blessing : public Skill {
public:
    Blessing();
    void skillImplementation(Character& user, Character& target) override;
};
