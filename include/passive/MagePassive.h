#pragma once

#include "Passive.h"

class ArcanePower : public Passive {
public:
    ArcanePower();
    void onUnlock(Character& owner) override;
};

class BurningInsight : public Passive {
public:
    BurningInsight();
    void onUnlock(Character& owner) override;
};

class GrandMagus : public Passive {
public:
    GrandMagus();
    void onUnlock(Character& owner) override;
};
