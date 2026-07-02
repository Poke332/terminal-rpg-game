#pragma once

#include <string>

class StatModifier {
public:
    enum class Type { FLAT, PERCENTAGE };

    int turnsRemaining = -1; // -1 = permanent, 0+ = expires after N turns

    virtual ~StatModifier() = default;
    virtual float apply(float currentValue) const = 0;
    virtual std::string getDescription() const = 0;
    virtual Type getType() const = 0;

    bool isExpired() const { return turnsRemaining == 0; }
    void tick() { if (turnsRemaining > 0) turnsRemaining--; }
};
