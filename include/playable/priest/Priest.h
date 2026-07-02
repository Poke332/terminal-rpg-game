#pragma once
#include "../Player.h"

class Priest : public Player {
public:
    Priest(const std::string& n);
    std::string className() const override;
    int heal(float h) override;
    void checkPassiveUnlock() override;
};