#pragma once
#include "Skill.h"

class QuickShot : public Skill {
public:
    QuickShot();
    void skillImplementation(Character& user, Character& target) override;
};
