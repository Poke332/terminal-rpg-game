#include "../../include/stats/PercentModifier.h"

PercentModifier::PercentModifier(float p, int duration) : percent(p) {
    turnsRemaining = duration;
}

float PercentModifier::apply(float currentValue) const {
    return currentValue * (1.0f + percent / 100.0f);
}

std::string PercentModifier::getDescription() const {
    std::string desc = (percent >= 0 ? "+" : "") + std::to_string(static_cast<int>(percent)) + "%";
    if (turnsRemaining > 0) desc += " [" + std::to_string(turnsRemaining) + "T]";
    return desc;
}

StatModifier::Type PercentModifier::getType() const {
    return Type::PERCENTAGE;
}
