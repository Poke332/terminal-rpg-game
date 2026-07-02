#pragma once
#include "../Player.h"

class Mage : public Player {
public:
    Mage(const std::string& n);
    std::string className() const override;
    void checkPassiveUnlock() override;
};