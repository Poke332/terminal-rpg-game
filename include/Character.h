#pragma once

#include <string>
#include <map>
#include <array>
#include <vector>
#include <memory>
#include "skills/Skill.h"
#include "stats/StatComponent.h"
#include "stats/StatusEffect.h"
#include "passive/Passive.h"

class Character {
protected:
    std::string name_;
    std::map<std::string, std::unique_ptr<StatComponent>> stats;
    std::array<std::unique_ptr<Skill>, 4> skillSlots;
    std::string type;

    int level_ = 1;
    int exp_ = 0;
    int expToNext_ = 100;
    int expValue_ = 0;
    int bonusExp_ = 0;

    bool isElite_ = false;
    bool isBoss_ = false;

    int evolution_ = 0;
    int perfectLevel_ = 1;

    std::unique_ptr<Skill> ultimateSkill_ = nullptr;
    int resource_ = 0;
    int maxResource_ = 100;
    std::string resourceName_;

    std::vector<std::unique_ptr<Passive>> passives;
    std::vector<std::unique_ptr<StatusEffect>> statusEffects;

public:
    Character(const std::string& n, const std::string& t = "undefined");
    virtual ~Character() = default;

    bool isAlive() const;
    const std::string& getName() const { return name_; }
    void turnPassed();
    void resetCooldowns();
    bool registerStat(const std::string& statName, float baseValue);
    void modifyStat(const std::string& statName, std::unique_ptr<StatModifier> modifier);
    bool hasStat(const std::string& statName) const;
    bool anyReadySkill() const;
    float getStat(const std::string& statName) const;
    float getAtkValue() const;
    Skill* getSkill(int slot) const;
    void setSkill(int slot, std::unique_ptr<Skill> skill);

    void addExp(int amount);
    int getExp() const;
    int getExpToNext() const;
    int getLevel() const;
    int getExpValue() const;
    void setExpValue(int v);
    void setBonusExp(int v);
    int getBonusExp() const;
    virtual void levelUp();

    void setElite(bool v);
    void setBoss(bool v);
    bool isElite() const;
    bool isBoss() const;

    int getEvolution() const;
    int getPerfectLevel() const;
    virtual bool canEvolve() const;
    virtual void evolve();
    void copyStateFrom(const Character& other);

    int getResource() const;
    int getMaxResource() const;
    std::string getResourceName() const;
    virtual void gainResource(int amount);
    virtual void onCombatAction();
    bool hasUltimate() const;
    bool hasUltimateReady() const;
    Skill* getUltimateSkill() const;
    void setUltimateSkill(std::unique_ptr<Skill> sk);
    void useUltimate(Character& target);

    void addPassive(std::unique_ptr<Passive> passive);
    void showPassives() const;
    virtual void checkPassiveUnlock();

    void addStatusEffect(std::unique_ptr<StatusEffect> effect);
    void removeStatusEffect(const std::string& name);
    bool hasStatusEffect(const std::string& name) const;
    void clearStatusEffects();
    void clearAllTempModifiers();
    void showStatusEffects() const;

    virtual void attack(Character& target);
    virtual void useAbility(int slot, Character& target) = 0;
    virtual std::string className() const = 0;
    virtual void takeDamage(float d);
    virtual int heal(float h);

    std::string showStatus(int padWidth = -1) const;
    void showSkillsShort() const;
    void showSkillLong(int index) const;
    void showFullStats() const;
};
