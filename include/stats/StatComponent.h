#pragma once

#include <vector>
#include <string>
#include <memory>
#include "StatModifier.h"

class StatComponent {
    float baseValue;
    std::vector<std::unique_ptr<StatModifier>> modifiers;
    std::string name;
    mutable bool dirty;
    mutable float cachedValue;
public:
    StatComponent(const std::string& n, float base = 0.0);

    void addModifier(std::unique_ptr<StatModifier> modifier);

    float getValue() const;
    void setBaseValue(float val);
    float getBaseValue() const;
    void clearModifiers();
    void tickModifiers();
    void clearTemporaryModifiers();
};
