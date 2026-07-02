#pragma once
#include "Skill.h"

class RainOfArrows : public Skill {
public:
    RainOfArrows();
    void skillImplementation(Character& user, Character& target) override;
};
