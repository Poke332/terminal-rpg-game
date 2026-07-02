#pragma once
#include "../Player.h"

class Warrior : public Player {
    bool guaranteeBlock = false;
public:
    Warrior(const std::string& n);
    std::string className() const override;
    void takeDamage(float d) override;
    void setGuaranteeBlock(bool v);
    void checkPassiveUnlock() override;
};