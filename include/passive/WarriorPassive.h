#pragma once

#include "Passive.h"

class IronWill : public Passive {
public:
    IronWill();
    void onUnlock(Character& owner) override;
};

class Veteran : public Passive {
public:
    Veteran();
    void onUnlock(Character& owner) override;
};

class Unbreakable : public Passive {
public:
    Unbreakable();
    void onUnlock(Character& owner) override;
    void onTakeDamage(Character& owner, float& damage) override;
};
