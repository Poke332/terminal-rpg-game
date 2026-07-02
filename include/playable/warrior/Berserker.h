#pragma once
#include "../Player.h"

class Berserker : public Player {
    bool guaranteeBlock = false;
public:
    Berserker(const std::string& n);
    std::string className() const override;
    void takeDamage(float d) override;
    void setGuaranteeBlock(bool v);
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    bool canEvolve() const override;
    void evolve() override;
};
