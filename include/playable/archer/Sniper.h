#pragma once
#include "../Player.h"

class Sniper : public Player {
public:
    Sniper(const std::string& n);
    std::string className() const override;
    void attack(Character& target) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    void takeDamage(float d) override;
};
