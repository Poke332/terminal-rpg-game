#pragma once

#include "StatModifier.h"

class AddModifier : public StatModifier {
    float amount;
public:
    AddModifier(float a, int duration = -1);
    float apply(float currentValue) const override;
    std::string getDescription() const override;
    Type getType() const override;
};
