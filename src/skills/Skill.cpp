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

void Skill::setCooldown() {
    cooldown = maxCooldown;
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

void Skill::executeAoE(Character& user, std::vector<std::unique_ptr<Character>>& targets, int primaryIndex, float splashMultiplier) {
    cooldown = maxCooldown;
    std::cout << colorize(user.className() + " " + user.getName(), Color::CYAN) << " uses "
              << colorize(name, Color::YELLOW) << " on "
              << colorize("all enemies", Color::RED) << "!" << std::endl;

    for (int i = 0; i < static_cast<int>(targets.size()); i++) {
        if (!targets[i]->isAlive()) continue;
        if (i == primaryIndex) {
            skillImplementation(user, *targets[i]);
            if (!targets[i]->isAlive()) user.addExp(targets[i]->getExpValue() + targets[i]->getBonusExp());
        } else {
            std::cout << colorize("  [Splash] " + targets[i]->className() + " " + targets[i]->getName(), Color::YELLOW) << std::endl;
            skillImplementation(user, *targets[i]);
            if (!targets[i]->isAlive()) user.addExp(targets[i]->getExpValue() + targets[i]->getBonusExp());
        }
    }
}

void Skill::executeAoEAlly(Character& user, std::vector<std::unique_ptr<Character>>& allies, int primaryIndex, float splashMultiplier) {
    cooldown = maxCooldown;
    std::cout << colorize(user.className() + " " + user.getName(), Color::CYAN) << " uses "
              << colorize(name, Color::YELLOW) << " on "
              << colorize("all allies", Color::GREEN) << "!" << std::endl;

    for (int i = 0; i < static_cast<int>(allies.size()); i++) {
        if (!allies[i]->isAlive()) continue;
        skillImplementation(user, *allies[i]);
    }
}

void Skill::executeAoEAllAlly(Character& user, std::vector<std::unique_ptr<Character>>& allies, float multiplier) {
    cooldown = maxCooldown;
    std::cout << colorize(user.className() + " " + user.getName(), Color::CYAN) << " uses "
              << colorize(name, Color::YELLOW) << " on "
              << colorize("all allies", Color::GREEN) << "!" << std::endl;

    for (int i = 0; i < static_cast<int>(allies.size()); i++) {
        if (!allies[i]->isAlive()) continue;
        skillImplementation(user, *allies[i]);
    }
}
