#include "../../include/stats/StatComponent.h"

#include <iostream>

StatComponent::StatComponent(const std::string& n, float base)
    : name(n), baseValue(base), dirty(true), cachedValue(0.0) {}

void StatComponent::addModifier(std::unique_ptr<StatModifier> modifier) {
    modifiers.push_back(std::move(modifier));
    dirty = true;
}

float StatComponent::getValue() const {
    if (!dirty) {
        return cachedValue;
    }

    float res = baseValue;
    for (const auto& modifier : modifiers) {
        res = modifier->apply(res);
    }
    cachedValue = res;
    dirty = false;
    return res;
}

void StatComponent::setBaseValue(float val) {
    baseValue = val;
    dirty = true;
}

float StatComponent::getBaseValue() const { return baseValue; }

void StatComponent::clearModifiers() {
    modifiers.clear();
    dirty = true;
}

