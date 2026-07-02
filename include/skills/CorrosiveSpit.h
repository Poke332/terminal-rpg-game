#pragma once
#include "Skill.h"

class CorrosiveSpit : public Skill {
public:
    CorrosiveSpit();
    void skillImplementation(Character& user, Character& target) override;
};
