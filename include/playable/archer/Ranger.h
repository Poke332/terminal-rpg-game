#pragma once
#include "../Player.h"

class Ranger : public Player {
public:
    Ranger(const std::string& n);
    std::string className() const override;
    void attack(Character& target) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    bool canEvolve() const override;
    void evolve() override;
};
