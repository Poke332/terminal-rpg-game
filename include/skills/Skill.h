#pragma once

#include <string>
#include <vector>
#include <memory>

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
    std::string getName() const;
    void printDetails() const;

    std::string getType() const;
    float getFinalDamage(float userDamage) const;
    bool isReady() const;
    int getCooldown() const;
    int getMaxCooldown() const;

    void reduceCooldown();
    void setCooldown();
    void execute(Character& user, Character& target);
    void executeAoE(Character& user, std::vector<std::unique_ptr<Character>>& targets, int primaryIndex, float splashMultiplier);
    void executeAoEAlly(Character& user, std::vector<std::unique_ptr<Character>>& allies, int primaryIndex, float splashMultiplier);
    void executeAoEAllAlly(Character& user, std::vector<std::unique_ptr<Character>>& allies, float multiplier);
    
    virtual void skillImplementation(Character& user, Character& target) = 0;
    virtual ~Skill() = default;
};
