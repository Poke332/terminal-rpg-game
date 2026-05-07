#pragma once

#include <string>
#include <map>
#include <array>
#include <memory>
#include "skills/Skill.h"
#include "stats/StatComponent.h"

class Character {
protected:
    std::string name_;
    std::map<std::string, std::unique_ptr<StatComponent>> stats;
    std::array<std::unique_ptr<Skill>, 3> skillSlots; // unique_ptr automatically handles memory
    std::string type;
    
public:
    Character(const std::string& n, const std::string& t = "undefined");
    virtual ~Character() = default;
    
    bool isAlive() const;
    void turnPassed();
    bool registerStat(const std::string& statName, float baseValue);
    void modifyStat(const std::string& statName, std::unique_ptr<StatModifier> modifier);
    bool hasStat(const std::string& statName) const;
    bool anyReadySkill() const;
    float getStat(const std::string& statName) const;
    float getAtkValue() const;
    Skill* getSkill(int slot) const;

    virtual void attack(Character& target);
    virtual void useAbility(int slot, Character& target) = 0; // This method is only used for enemy
    virtual std::string className() const = 0;
    virtual void takeDamage(float d);
    virtual int heal(float h);

    std::string showStatus() const;
    void showSkillsShort() const;
    void showSkillLong(int index) const;
    void showFullStats() const;
};