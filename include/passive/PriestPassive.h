#pragma once

#include "Passive.h"

class HolyBlessing : public Passive {
public:
    HolyBlessing();
    void onUnlock(Character& owner) override;
};

class DivineProtection : public Passive {
public:
    DivineProtection();
    void onUnlock(Character& owner) override;
};

class MiracleWorker : public Passive {
public:
    MiracleWorker();
    void onUnlock(Character& owner) override;
};
