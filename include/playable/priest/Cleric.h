#pragma once
#include "../Player.h"

class Cleric : public Player {
    bool meditating_ = false;
public:
    Cleric(const std::string& n);
    std::string className() const override;
    int heal(float h) override;
    void checkPassiveUnlock() override;
    void onCombatAction() override;
    bool canEvolve() const override;
    void evolve() override;
    void setMeditating(bool v);
    bool isMeditating() const;
};
