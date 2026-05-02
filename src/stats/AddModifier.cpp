#include "../../include/stats/AddModifier.h"
#include <string>

AddModifier::AddModifier(float a) : amount(a) {}

float AddModifier::apply(float currentValue) const { return currentValue + amount; }

std::string AddModifier::getDescription() const { return "+" + std::to_string(amount); }