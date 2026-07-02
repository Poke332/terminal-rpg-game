#include "../../include/skills/Skill.h"
#include "../../include/Character.h"
#include "../../include/utils.h"
#include <iostream>

Skill::Skill(const std::string& n, const std::string& d, const std::string& t, float b, float p, int cd)
    : name(n), description(d), type(t), maxCooldown(cd), baseScale(b), percentScale(p) {};

std::string Skill::showShort() const {
    return name + " CD: " + std::to_string(maxCooldown) + " " + (isReady() ? "Usable" : ("On Cooldown " + std::to_string(cooldown) + " Turns"));
}

std::string Skill::getName() const { return name; }

void Skill::printDetails() const {
    std::cout << "Skill Name: " << name << " Cooldown: " << maxCooldown << " Turns" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Scaling: (" << baseScale << " + Character Attack) * (1+" << percentScale << ")" << std::endl;  
}

bool Skill::isReady() const {
    return cooldown == 0;
}

int Skill::getCooldown() const { return cooldown; }
int Skill::getMaxCooldown() const { return maxCooldown; }

void Skill::reduceCooldown() {
    if (cooldown > 0) {
        cooldown--;
    }
}

std::string Skill::getType() const {
    return type;
}

float Skill::getFinalDamage(float userDamage) const {
    return (baseScale + userDamage) * (1.0f + percentScale);
}

void Skill::execute(Character& user, Character& target) {
    cooldown = maxCooldown;
    std::cout << colorize(user.className() + " " + user.getName(), Color::CYAN) << " uses "
              << colorize(name, Color::YELLOW) << " on "
              << colorize(target.className() + " " + target.getName(), Color::RED) << "!" << std::endl;
    skillImplementation(user, target);
    if (!target.isAlive()) user.addExp(target.getExpValue() + target.getBonusExp());
}