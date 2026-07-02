#include "../../include/stats/StatusEffect.h"
#include "../../include/Character.h"
#include "../../include/utils.h"

#include <iostream>

StatusEffect::StatusEffect(const std::string& name, const std::string& desc,
                           const std::string& icon, int duration,
                           bool stackable, int maxStacks)
    : name_(name), description_(desc), icon_(icon),
      duration_(duration), maxDuration_(duration),
      stackable_(stackable), maxStacks_(maxStacks) {}

std::string StatusEffect::getName() const { return name_; }
std::string StatusEffect::getDescription() const { return description_; }
std::string StatusEffect::getIcon() const { return icon_; }
int StatusEffect::getDuration() const { return duration_; }
int StatusEffect::getStacks() const { return stacks_; }

void StatusEffect::addStacks(int n) {
    if (stackable_) {
        stacks_ = std::min(maxStacks_, stacks_ + n);
        duration_ = maxDuration_;
    }
}

void StatusEffect::reduceDuration() {
    if (duration_ > 0) duration_--;
}

bool StatusEffect::isExpired() const {
    return duration_ <= 0;
}

void StatusEffect::onApply(Character& owner) {}
void StatusEffect::onTurnStart(Character& owner) {}
void StatusEffect::onExpire(Character& owner) {}

DamageOverTime::DamageOverTime(const std::string& name, const std::string& icon,
                               float damagePerTurn, int duration, bool stackable, int maxStacks)
    : StatusEffect(name, "Deals " + std::to_string(static_cast<int>(damagePerTurn)) +
                   " damage per turn", icon, duration, stackable, maxStacks),
      damagePerTurn_(damagePerTurn) {}

void DamageOverTime::onTurnStart(Character& owner) {
    float totalDmg = damagePerTurn_ * stacks_;
    owner.takeDamage(totalDmg);
    std::cout << colorize(icon_ + " " + name_ + " deals " +
                std::to_string(static_cast<int>(totalDmg)) +
                " damage! [" + std::to_string(stacks_) + "x]",
                Color::RED) << std::endl;
}
