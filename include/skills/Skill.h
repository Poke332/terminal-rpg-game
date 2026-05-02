#pragma once

#include <string>

class Character;

class Skill {
protected:
    std::string name;
    std::string description;
    std::string type;
    int cooldown = 0;
    int maxCooldown;
    float baseScale;
    float percentScale;
public:
    Skill(const std::string& n, const std::string& d, const std::string& t, float b, float p, int cd);
    std::string showShort() const;
    void printDetails() const;

    std::string getType() const;
    float getFinalDamage(float userDamage) const;
    bool isReady() const;

    void reduceCooldown();
    void execute(Character& user, Character& target);
    
    virtual void skillImplementation(Character& user, Character& target) = 0;
    virtual ~Skill() = default;
};