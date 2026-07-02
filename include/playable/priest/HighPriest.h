#pragma once
#include "../Player.h"

class HighPriest : public Player {
    bool meditating_ = false;
public:
    HighPriest(const std::string& n);
    std::string className() const override;
    int heal(float h) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    void setMeditating(bool v);
    bool isMeditating() const;
};
