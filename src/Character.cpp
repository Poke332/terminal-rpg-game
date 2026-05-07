#include "../include/Character.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

Character::Character(const std::string& n, const std::string& t)
    : name_(n), type(t) {}

bool Character::isAlive() const {
    return getStat("hp") > 0.0f;
}

void Character::turnPassed() {
    for (const auto& skill : skillSlots) {
        if (skill) skill->reduceCooldown();
    }
}


bool Character::hasStat(const std::string& statName) const {
    return stats.find(statName) != stats.end();
}

float Character::getStat(const std::string& statName) const {
    auto it = stats.find(statName);
    return (this->hasStat(statName) ? it->second->getValue() : 0.0f);
} 

float Character::getAtkValue() const {
    float attack = getStat("attack");
    float dmgBonus = 1.0f + getStat("damage_bonus");
    float critChance = getStat("crit_chance");
    float critDamage = 1.0f + getStat("crit_damage");

    float finDamage = attack * dmgBonus;
    if ((rand() % 100) < (static_cast<int>(critChance*100))) {
        finDamage *= (1.0f+critDamage);
    }

    return finDamage;
}

void Character::attack(Character& target) {
    float finDamage = getAtkValue();
    target.takeDamage(finDamage);
    std::cout << this->name_ << " dealt " << finDamage << "damage!" << std::endl;
}  

void Character::takeDamage(float d) {
    float currentHp = getStat("hp");
    float armor = getStat("armor");
    float dmgReduc = getStat("damage_reduction");

    float rawDamage = std::max(0.0f, d - armor);
    float dmgTaken = rawDamage * (1.0f - dmgReduc);

    if (hasStat("hp")) {
        stats.find("hp")->second->setBaseValue(std::max(0.0f, (currentHp - dmgTaken)));
    }
}

bool Character::registerStat(const std::string& statName, float baseValue) {
    if (hasStat(statName)) {
        return false;
    }
    stats[statName] = std::make_unique<StatComponent>(statName, baseValue);
    return true;
}

void Character::modifyStat(const std::string& statName, std::unique_ptr<StatModifier> modifier) {
    if (hasStat(statName)) {
        stats.find(statName)->second->addModifier(std::move(modifier));
    }
}


bool Character::anyReadySkill() const {
    bool ready = true;
    for (const auto& skill : skillSlots) {
        if (!skill || !(skill->isReady())) ready = false;
        else ready = true;
    } return ready;
}

Skill* Character::getSkill(int slot) const { 
    if (slot < 0 || slot >= 3) return nullptr;
    return skillSlots[slot].get();
}

int Character::heal(float h) {
    if (!isAlive()) {
        return static_cast<int>(getStat("hp"));
    }

    float maxHp = getStat("max_hp");
    float currentHp = getStat("hp");
    
    float newHp = std::min(maxHp, currentHp + h);
    if (hasStat("hp")) {
        stats.find("hp")->second->setBaseValue(newHp);
    }

    return newHp;
}

std::string Character::showStatus() const { 
    float currentHp = getStat("hp");
    float currentMaxHp = getStat("max_hp");
    return className() + " " + name_ + "[HP: " + std::to_string(static_cast<int>(currentHp)) + "/" + std::to_string(static_cast<int>(currentMaxHp)) + "]"; 
}

void Character::showSkillsShort() const {
    for (const auto& skill : skillSlots) {
        if (skill) {
            std::cout << "|" << std::setfill(' ') << std::left << std::setw(72)
            << skill->showShort() << "|" << std::endl;
        }
    }
}

void Character::showSkillLong(int index) const {
    if (index < 0 || index > 3 || !skillSlots[index]) return;
    skillSlots[index]->printDetails();
}

void Character::showFullStats() const {
    std::cout << className() << " " << name_ << std::endl;
    for (const auto& stat : stats) {
        std::cout << "\t" << stat.first << ": " << stat.second->getValue() << std::endl; 
    }
    std::cout << "Owned Skills:" << std::endl;
    for(const auto& skill : skillSlots) {
        if (skill) {
            skill->printDetails();
        }
    }
}