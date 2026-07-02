#pragma once
#include "Passive.h"

class FuryUnleashed : public Passive {
public:
    FuryUnleashed();
    void onUnlock(Character& owner) override;
    void onTakeDamage(Character& owner, float& damage) override;
};

class WarlordsPresence : public Passive {
public:
    WarlordsPresence();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};
