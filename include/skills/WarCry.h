#pragma once
#include "Skill.h"

class WarCry : public Skill {
public:
    WarCry();
    void skillImplementation(Character& user, Character& target) override;
};
