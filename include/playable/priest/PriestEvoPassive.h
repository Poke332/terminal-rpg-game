#pragma once
#include "Passive.h"

class DivineAegis : public Passive {
public:
    DivineAegis();
    void onUnlock(Character& owner) override;
};

class Sanctuary : public Passive {
public:
    Sanctuary();
    void onUnlock(Character& owner) override;
};
