#pragma once
#include "Skill.h"

class ArcaneBlast : public Skill {
public:
    ArcaneBlast();
    void skillImplementation(Character& user, Character& target) override;
};
