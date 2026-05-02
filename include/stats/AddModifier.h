#pragma once

#include "StatModifier.h"
#include <string>

class AddModifier : public StatModifier {
    float amount;
public:
    AddModifier(float a);

    float apply(float currentValue) const override;
    std::string getDescription() const override;
};