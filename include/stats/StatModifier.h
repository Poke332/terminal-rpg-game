#pragma once

#include <string>

class StatModifier {
public:
    virtual ~StatModifier() = default;
    virtual float apply(float currentValue) const = 0;
    virtual std::string getDescription() const = 0;
};