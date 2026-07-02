#pragma once

#include "Passive.h"

class EliteResilience : public Passive {
public:
    EliteResilience();
    void onUnlock(Character& owner) override;
};
