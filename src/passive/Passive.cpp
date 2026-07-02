#include "../include/passive/Passive.h"

Passive::Passive(const std::string& name, const std::string& desc, int reqLevel)
    : name_(name), description_(desc), requiredLevel_(reqLevel) {}

std::string Passive::getName() const { return name_; }
std::string Passive::getDescription() const { return description_; }
int Passive::getRequiredLevel() const { return requiredLevel_; }

void Passive::onUnlock(Character& owner) {}
void Passive::onTakeDamage(Character& owner, float& damage) {}
void Passive::onAttack(Character& owner, Character& target, float& damage) {}
