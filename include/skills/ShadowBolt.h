#pragma once
#include "Skill.h"

class ShadowBolt : public Skill {
public:
    ShadowBolt();
    void skillImplementation(Character& user, Character& target) override;
};
