#include "../../include/stats/StatComponent.h"

#include <iostream>
#include <algorithm>

StatComponent::StatComponent(const std::string& n, float base)
    : name(n), baseValue(base), dirty(true), cachedValue(0.0) {}

void StatComponent::addModifier(std::unique_ptr<StatModifier> modifier) {
    modifiers.push_back(std::move(modifier));
    dirty = true;
}

float StatComponent::getValue() const {
    if (!dirty) return cachedValue;

    float flatSum = baseValue;
    float percentBonus = 0.0f;

    for (const auto& mod : modifiers) {
        if (mod->getType() == StatModifier::Type::FLAT) {
            flatSum = mod->apply(flatSum);
        } else {
            percentBonus += 0.0f;
        }
    }

    for (const auto& mod : modifiers) {
        if (mod->getType() == StatModifier::Type::PERCENTAGE) {
            flatSum = mod->apply(flatSum);
        }
    }

    cachedValue = flatSum;
    dirty = false;
    return cachedValue;
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

void StatComponent::tickModifiers() {
    for (auto& mod : modifiers) {
        mod->tick();
    }
    modifiers.erase(
        std::remove_if(modifiers.begin(), modifiers.end(),
            [](const std::unique_ptr<StatModifier>& m) { return m->isExpired(); }),
        modifiers.end());
    dirty = true;
}

void StatComponent::clearTemporaryModifiers() {
    modifiers.erase(
        std::remove_if(modifiers.begin(), modifiers.end(),
            [](const std::unique_ptr<StatModifier>& m) { return m->turnsRemaining != -1; }),
        modifiers.end());
    dirty = true;
}
