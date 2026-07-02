#pragma once
#include "../Player.h"

class Archmage : public Player {
public:
    Archmage(const std::string& n);
    std::string className() const override;
    void useAbility(int slot, Character& target) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
};
