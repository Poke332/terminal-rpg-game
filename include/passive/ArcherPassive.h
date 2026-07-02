#pragma once

#include "Passive.h"

class KeenEye : public Passive {
public:
    KeenEye();
    void onUnlock(Character& owner) override;
};

class EaglesPrecision : public Passive {
public:
    EaglesPrecision();
    void onUnlock(Character& owner) override;
};

class ShadowStalker : public Passive {
public:
    ShadowStalker();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};
