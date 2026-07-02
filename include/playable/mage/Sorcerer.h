#pragma once
#include "../Player.h"

class Sorcerer : public Player {
public:
    Sorcerer(const std::string& n);
    std::string className() const override;
    void useAbility(int slot, Character& target) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    bool canEvolve() const override;
    void evolve() override;
};
