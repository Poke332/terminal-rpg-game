#include "../../include/skills/Skill.h"
#include "../../include/Character.h"
#include <iostream>

Skill::Skill(const std::string& n, const std::string& d, const std::string& t, float b, float p, int cd)
    : name(n), description(d), type(t), baseScale(b), percentScale(p), maxCooldown(cd) {};

std::string Skill::showShort() const {
    return name + " CD: " + std::to_string(maxCooldown) + " " + (isReady() ? "Usable" : ("On Cooldown " + std::to_string(cooldown) + " Turns"));
}

void Skill::printDetails() const {
    std::cout << "Skill Name: " << name << " Cooldown: " << maxCooldown << " Turns" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Scaling: (" << baseScale << " + Character Attack) * (1+" << percentScale << ")" << std::endl;  
}

bool Skill::isReady() const {
    return cooldown == 0;
}

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
    std::cout << "Casting " << name << std::endl;
    skillImplementation(user, target);   
}