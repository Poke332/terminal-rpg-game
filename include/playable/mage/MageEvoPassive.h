#pragma once
#include "Passive.h"

class SpellAmplifier : public Passive {
    int spellCount_ = 0;
public:
    SpellAmplifier();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};

class ElementalMastery : public Passive {
public:
    ElementalMastery();
    void onUnlock(Character& owner) override;
    void onAttack(Character& owner, Character& target, float& damage) override;
};
