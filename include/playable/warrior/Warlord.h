#pragma once
#include "../Player.h"

class Warlord : public Player {
    bool guaranteeBlock = false;
public:
    Warlord(const std::string& n);
    std::string className() const override;
    void takeDamage(float d) override;
    void setGuaranteeBlock(bool v);
    void checkPassiveUnlock() override;
    void onCombatAction() override;
};
