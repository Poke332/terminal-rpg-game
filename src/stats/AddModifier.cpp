#include "../../include/stats/AddModifier.h"

AddModifier::AddModifier(float a, int duration) : amount(a) {
    turnsRemaining = duration;
}

float AddModifier::apply(float currentValue) const {
    return currentValue + amount;
}

std::string AddModifier::getDescription() const {
    std::string desc = (amount >= 0 ? "+" : "") + std::to_string(static_cast<int>(amount));
    if (turnsRemaining > 0) desc += " [" + std::to_string(turnsRemaining) + "T]";
    return desc;
}

StatModifier::Type AddModifier::getType() const {
    return Type::FLAT;
}
