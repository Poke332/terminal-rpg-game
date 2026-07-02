#pragma once
#include "Passive.h"

class HuntersInstinct : public Passive {
public:
    HuntersInstinct();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};

class EagleVision : public Passive {
public:
    EagleVision();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};
