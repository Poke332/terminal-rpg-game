#pragma once

#include "StatModifier.h"

class PercentModifier : public StatModifier {
    float percent; // e.g., 20 = +20%, -15 = -15%
public:
    PercentModifier(float p, int duration = -1);
    float apply(float currentValue) const override;
    std::string getDescription() const override;
    Type getType() const override;
};
