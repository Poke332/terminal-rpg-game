#pragma once

#include <string>

class Character;

class Passive {
protected:
    std::string name_;
    std::string description_;
    int requiredLevel_;
public:
    Passive(const std::string& name, const std::string& desc, int reqLevel);
    virtual ~Passive() = default;

    std::string getName() const;
    std::string getDescription() const;
    int getRequiredLevel() const;

    virtual void onUnlock(Character& owner);
    virtual void onTakeDamage(Character& owner, float& damage);
    virtual void onAttack(Character& owner, Character& target, float& damage);
};
