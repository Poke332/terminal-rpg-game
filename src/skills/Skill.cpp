#include "../../include/skills/Skill.h"
#include "../../include/Character.h"
#include "../../include/utils.h"
#include "../../include/stats/AddModifier.h"
#include "../../include/Ids.h"
#include <iostream>

using namespace Ids;

Skill::Skill(const std::string& n, const std::string& d, const std::string& t, float b, float p, int cd)
    : name(n), description(d), type(t), maxCooldown(cd), baseScale(b), percentScale(p) {};

std::string Skill::showShort() const {
    std::string typeTag;
    if (type == SkillType::aoe_enemy) typeTag = colorize("[AOE]", Color::RED);
    else if (type == SkillType::aoe_adjacent_enemy) typeTag = colorize("[Splash]", Color::RED);
    else if (type == SkillType::aoe_ally) typeTag = colorize("[Party]", Color::GREEN);
    else if (type == SkillType::aoe_adjacent_ally) typeTag = colorize("[Adj Heal]", Color::GREEN);
    else if (type == SkillType::single_cast_ally) typeTag = colorize("[Heal]", Color::GREEN);
    else if (type == SkillType::self_cast) typeTag = colorize("[Self]", Color::CYAN);
    else typeTag = colorize("[Atk]", Color::YELLOW);

    std::string status = isReady() ? colorize("Ready", Color::GREEN) : colorize("CD:" + std::to_string(cooldown), Color::YELLOW);
    return name + " " + typeTag + " CD:" + std::to_string(maxCooldown) + " " + status;
}

std::string Skill::getName() const { return name; }
std::string Skill::getDescription() const { return description; }

void Skill::printDetails() const {
    std::string typeLabel;
    if (type == SkillType::single_cast_enemy) typeLabel = "Single Enemy";
    else if (type == SkillType::single_cast_ally) typeLabel = "Single Ally";
    else if (type == SkillType::self_cast) typeLabel = "Self";
    else if (type == SkillType::aoe_enemy) typeLabel = "All Enemies (AOE)";
    else if (type == SkillType::aoe_adjacent_enemy) typeLabel = "Adjacent Enemies (Splash)";
    else if (type == SkillType::aoe_ally) typeLabel = "All Allies";
    else if (type == SkillType::aoe_adjacent_ally) typeLabel = "Adjacent Allies";
    else typeLabel = type;

    printBoxedLine(colorize("  " + name, Color::CYAN) + "  " + colorize("[" + typeLabel + "]", Color::YELLOW));

    int maxDesc = colWidth - 6;
    std::string desc = description;
    while (!desc.empty()) {
        if (static_cast<int>(desc.size()) <= maxDesc) {
            printBoxedLine("  " + desc);
            break;
        }
        int split = maxDesc;
        while (split > 0 && desc[split] != ' ') split--;
        if (split == 0) split = maxDesc;
        printBoxedLine("  " + desc.substr(0, split));
        while (split < static_cast<int>(desc.size()) && desc[split] == ' ') split++;
        desc = desc.substr(split);
    }

    printBoxedLine("  " + colorize("CD: " + std::to_string(maxCooldown) + "T", Color::WHITE_BOLD)
                   + "  Scaling: (" + std::to_string(static_cast<int>(baseScale)) + " + ATK) * (1+" + std::to_string(percentScale) + ")");
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
            targets[i]->modifyStat("attack", std::make_unique<AddModifier>(15.0f, 2));
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
