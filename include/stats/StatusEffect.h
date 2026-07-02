#pragma once

#include <string>
#include <memory>

class Character;

class StatusEffect {
protected:
    std::string name_;
    std::string description_;
    std::string icon_;
    int duration_;
    int maxDuration_;
    int stacks_ = 1;
    bool stackable_ = false;
    int maxStacks_ = 99;
public:
    StatusEffect(const std::string& name, const std::string& desc,
                 const std::string& icon, int duration,
                 bool stackable = false, int maxStacks = 99);
    virtual ~StatusEffect() = default;

    std::string getName() const;
    std::string getDescription() const;
    std::string getIcon() const;
    int getDuration() const;
    int getStacks() const;
    void addStacks(int n);
    void reduceDuration();
    bool isExpired() const;

    virtual void onApply(Character& owner);
    virtual void onTurnStart(Character& owner);
    virtual void onExpire(Character& owner);
};

class DamageOverTime : public StatusEffect {
    float damagePerTurn_;
public:
    DamageOverTime(const std::string& name, const std::string& icon,
                   float damagePerTurn, int duration, bool stackable = true, int maxStacks = 5);
    void onTurnStart(Character& owner) override;
};
