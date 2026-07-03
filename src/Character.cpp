#include "../include/Character.h"
#include "../include/passive/Passive.h"
#include "../include/utils.h"
#include "../include/Ids.h"
#include "../include/stats/AddModifier.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace Ids;

Character::Character(const std::string& n, const std::string& t)
    : name_(n), type(t) {}

bool Character::isAlive() const {
    return getStat(Stat::hp) > 0.0f;
}

void Character::turnPassed() {
    for (const auto& skill : skillSlots) {
        if (skill) skill->reduceCooldown();
    }
    if (ultimateSkill_) ultimateSkill_->reduceCooldown();
    for (auto& [name, comp] : stats) {
        comp->tickModifiers();
    }
    for (auto& effect : statusEffects) {
        if (!effect->isExpired()) {
            effect->onTurnStart(*this);
            effect->reduceDuration();
        }
    }
    statusEffects.erase(
        std::remove_if(statusEffects.begin(), statusEffects.end(),
            [](const auto& e) { return e->isExpired(); }),
        statusEffects.end());
    onCombatAction();
}

void Character::resetCooldowns() {
    for (auto& skill : skillSlots) {
        if (skill) {
            while (!skill->isReady()) {
                skill->reduceCooldown();
            }
        }
    }
    if (ultimateSkill_) {
        while (!ultimateSkill_->isReady()) {
            ultimateSkill_->reduceCooldown();
        }
    }
    resource_ = maxResource_;
}

bool Character::hasStat(const std::string& statName) const {
    return stats.find(statName) != stats.end();
}

float Character::getStat(const std::string& statName) const {
    auto it = stats.find(statName);
    return (it != stats.end() ? it->second->getValue() : 0.0f);
}

float Character::getAtkValue() const {
    float atk = getStat(Stat::attack);
    float dmgBonus = 1.0f + getStat(Stat::damage_bonus);
    float critChance = getStat(Stat::crit_chance);
    float critDamage = 1.0f + getStat(Stat::crit_damage);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);

    float finDamage = atk * dmgBonus;
    if (dist(rng) < static_cast<int>(critChance * 100)) {
        finDamage *= (1.0f + critDamage);
    }

    return finDamage;
}

void Character::attack(Character& target) {
    float finDamage = getAtkValue();
    for (auto& p : passives) p->onAttack(*this, target, finDamage);
    float hpBefore = target.getStat(Stat::hp);
    target.takeDamage(finDamage);
    float hpAfter = target.getStat(Stat::hp);
    std::cout << colorize(className() + " " + name_, Color::CYAN)
              << " attacks "
              << colorize(target.className() + " " + target.name_, Color::RED)
              << " for " << colorize(std::to_string(static_cast<int>(finDamage)) + " damage", Color::RED)
              << "! " << colorize("[HP:" + std::to_string(static_cast<int>(hpBefore)) + "->" +
                  std::to_string(static_cast<int>(hpAfter)) + "]", Color::YELLOW) << std::endl;
    if (!target.isAlive()) addExp(target.getExpValue() + target.bonusExp_);
}

void Character::takeDamage(float d) {
    float currentHp = getStat(Stat::hp);
    float armorVal = getStat(Stat::armor);
    float dmgReduc = getStat(Stat::damage_reduction);

    float rawDamage = std::max(0.0f, d - armorVal);
    float dmgTaken = rawDamage * (1.0f - dmgReduc);

    auto hpIt = stats.find(Stat::hp);
    if (hpIt != stats.end()) {
        float currentBase = hpIt->second->getBaseValue();
        float flatExtras = currentHp - currentBase;
        float newBase = currentBase - dmgTaken;
        if (newBase + flatExtras < 0) newBase = -flatExtras;
        hpIt->second->setBaseValue(newBase);
    }
}

bool Character::registerStat(const std::string& statName, float baseValue) {
    if (hasStat(statName)) return false;
    stats[statName] = std::make_unique<StatComponent>(statName, baseValue);
    return true;
}

void Character::modifyStat(const std::string& statName, std::unique_ptr<StatModifier> modifier) {
    auto it = stats.find(statName);
    if (it != stats.end()) {
        it->second->addModifier(std::move(modifier));
    }
}

bool Character::anyReadySkill() const {
    for (const auto& skill : skillSlots) {
        if (skill && skill->isReady()) return true;
    }
    return false;
}

Skill* Character::getSkill(int slot) const {
    if (slot < 0 || slot >= 4) return nullptr;
    return skillSlots[slot].get();
}

void Character::setSkill(int slot, std::unique_ptr<Skill> skill) {
    if (slot >= 0 && slot < 4) {
        skillSlots[slot] = std::move(skill);
    }
}

void Character::addExp(int amount) {
    if (amount <= 0) return;
    exp_ += amount;
    while (exp_ >= expToNext_) {
        exp_ -= expToNext_;
        levelUp();
    }
}

int Character::getExp() const { return exp_; }
int Character::getExpToNext() const { return expToNext_; }
int Character::getLevel() const { return level_; }
int Character::getExpValue() const { return expValue_; }
void Character::setExpValue(int v) { expValue_ = v; }
void Character::setBonusExp(int v) { bonusExp_ = v; }
int Character::getBonusExp() const { return bonusExp_; }

void Character::levelUp() {
    level_++;
    perfectLevel_++;
    expToNext_ = 100 + (level_ - 1) * 50;

    std::string cn = className();
    if (cn == "Warrior" || cn == "Berserker" || cn == "Warlord") {
        modifyStat(Stat::max_hp, std::make_unique<AddModifier>(8.0f));
        modifyStat(Stat::hp, std::make_unique<AddModifier>(8.0f));
        modifyStat(Stat::attack, std::make_unique<AddModifier>(2.0f));
        modifyStat(Stat::armor, std::make_unique<AddModifier>(1.0f));
        modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.005f));
    } else if (cn == "Mage" || cn == "Sorcerer" || cn == "Archmage") {
        modifyStat(Stat::max_hp, std::make_unique<AddModifier>(4.0f));
        modifyStat(Stat::hp, std::make_unique<AddModifier>(4.0f));
        modifyStat(Stat::attack, std::make_unique<AddModifier>(3.0f));
        modifyStat(Stat::armor, std::make_unique<AddModifier>(0.5f));
        modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.01f));
    } else if (cn == "Priest" || cn == "Cleric" || cn == "High Priest") {
        modifyStat(Stat::max_hp, std::make_unique<AddModifier>(5.0f));
        modifyStat(Stat::hp, std::make_unique<AddModifier>(5.0f));
        modifyStat(Stat::attack, std::make_unique<AddModifier>(1.0f));
        modifyStat(Stat::armor, std::make_unique<AddModifier>(0.5f));
        modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.005f));
        modifyStat(Stat::healing_bonus_pct, std::make_unique<AddModifier>(0.005f));
        modifyStat(Stat::healing_bonus_base, std::make_unique<AddModifier>(0.5f));
    } else if (cn == "Archer" || cn == "Ranger" || cn == "Sniper") {
        modifyStat(Stat::max_hp, std::make_unique<AddModifier>(4.0f));
        modifyStat(Stat::hp, std::make_unique<AddModifier>(4.0f));
        modifyStat(Stat::attack, std::make_unique<AddModifier>(2.0f));
        modifyStat(Stat::armor, std::make_unique<AddModifier>(0.5f));
        modifyStat(Stat::crit_chance, std::make_unique<AddModifier>(0.015f));
        modifyStat(Stat::crit_damage, std::make_unique<AddModifier>(0.02f));
    }

    auto hpIt = stats.find(Stat::hp);
    if (hpIt != stats.end()) {
        float maxHp = getStat(Stat::max_hp);
        float currentHp = getStat(Stat::hp);
        float flatExtras = currentHp - hpIt->second->getBaseValue();
        hpIt->second->setBaseValue(maxHp - flatExtras);
    }
    checkPassiveUnlock();
    if (canEvolve()) {
        evolve();
    }
}

void Character::setElite(bool v) { isElite_ = v; }
void Character::setBoss(bool v) { isBoss_ = v; }
bool Character::isElite() const { return isElite_; }
bool Character::isBoss() const { return isBoss_; }

int Character::getEvolution() const { return evolution_; }
int Character::getPerfectLevel() const { return perfectLevel_; }

bool Character::canEvolve() const {
    return evolution_ < 2 && level_ >= 20;
}

void Character::evolve() {
    evolution_++;
    level_ = 1;
    exp_ = 0;
    expToNext_ = 100;
}

void Character::copyStateFrom(const Character& other) {
    name_ = other.name_;
    type = other.type;
    level_ = other.level_;
    exp_ = other.exp_;
    expToNext_ = other.expToNext_;
    expValue_ = other.expValue_;
    bonusExp_ = other.bonusExp_;
    evolution_ = other.evolution_;
    perfectLevel_ = other.perfectLevel_;
    resource_ = other.resource_;
    maxResource_ = other.maxResource_;
    resourceName_ = other.resourceName_;
    isElite_ = other.isElite_;
    isBoss_ = other.isBoss_;

    for (auto& [statName, comp] : stats) {
        auto otherIt = other.stats.find(statName);
        if (otherIt != other.stats.end()) {
            comp->setBaseValue(otherIt->second->getBaseValue());
        }
    }

    if (other.ultimateSkill_) {
        ultimateSkill_ = nullptr;
    }
}

int Character::getResource() const { return resource_; }
int Character::getMaxResource() const { return maxResource_; }
std::string Character::getResourceName() const { return resourceName_; }

void Character::gainResource(int amount) {
    resource_ = std::min(maxResource_, resource_ + amount);
}

void Character::onCombatAction() {}

bool Character::hasUltimate() const {
    return ultimateSkill_ != nullptr;
}

bool Character::hasUltimateReady() const {
    return ultimateSkill_ && ultimateSkill_->isReady() && resource_ >= maxResource_;
}

Skill* Character::getUltimateSkill() const {
    return ultimateSkill_.get();
}

void Character::setUltimateSkill(std::unique_ptr<Skill> sk) {
    ultimateSkill_ = std::move(sk);
}

void Character::useUltimate(Character& target) {
    if (!hasUltimateReady()) return;
    resource_ = 0;
    ultimateSkill_->execute(*this, target);
}

void Character::addPassive(std::unique_ptr<Passive> passive) {
    passive->onUnlock(*this);
    passives.push_back(std::move(passive));
}

void Character::showPassives() const {
    if (passives.empty()) return;
    printBoxedLine(colorize("Passive Skills:", Color::WHITE_BOLD));
    for (const auto& p : passives) {
        printBoxedLine("  " + colorize(p->getName(), Color::CYAN)
                       + " - " + p->getDescription());
    }
}

void Character::checkPassiveUnlock() {}

void Character::addStatusEffect(std::unique_ptr<StatusEffect> effect) {
    for (auto& existing : statusEffects) {
        if (existing->getName() == effect->getName()) {
            existing->addStacks(1);
            std::cout << colorize(effect->getName() + " stacked! [" +
                        std::to_string(existing->getStacks()) + "x]", Color::YELLOW) << std::endl;
            return;
        }
    }
    effect->onApply(*this);
    statusEffects.push_back(std::move(effect));
}

void Character::removeStatusEffect(const std::string& name) {
    statusEffects.erase(
        std::remove_if(statusEffects.begin(), statusEffects.end(),
            [&name](const auto& e) { return e->getName() == name; }),
        statusEffects.end());
}

bool Character::hasStatusEffect(const std::string& name) const {
    for (const auto& e : statusEffects) {
        if (e->getName() == name) return true;
    }
    return false;
}

void Character::clearStatusEffects() {
    statusEffects.clear();
}

void Character::clearAllTempModifiers() {
    for (auto& [name, comp] : stats) {
        comp->clearTemporaryModifiers();
    }
}

void Character::showStatusEffects() const {
    if (statusEffects.empty()) return;
    std::string line = " ";
    for (const auto& e : statusEffects) {
        line += e->getIcon() + e->getName() + "[" + std::to_string(e->getDuration()) + "] ";
    }
    printBoxedLine(colorize(line, Color::YELLOW));
}

int Character::heal(float h) {
    if (!isAlive()) return static_cast<int>(getStat(Stat::hp));

    float maxHp = getStat(Stat::max_hp);
    float currentHp = getStat(Stat::hp);

    float newHp = std::min(maxHp, currentHp + h);
    auto hpIt = stats.find(Stat::hp);
    if (hpIt != stats.end()) {
        float currentBase = hpIt->second->getBaseValue();
        float flatExtras = currentHp - currentBase;
        hpIt->second->setBaseValue(newHp - flatExtras);
    }
    return static_cast<int>(newHp);
}

std::string Character::showStatus(int padWidth) const {
    if (padWidth < 0) padWidth = colWidth - 2;
    float currentHp = getStat(Stat::hp);
    float currentMaxHp = getStat(Stat::max_hp);
    std::string bar = hpBar(currentHp, currentMaxHp, 12);

    std::string tag;
    if (isBoss_) tag = colorize("[BOSS] ", Color::RED);
    else if (isElite_) tag = colorize("[ELITE] ", Color::CYAN);

    std::string evoTag;
    if (evolution_ == 1) evoTag = colorize("[EVO1] ", Color::GREEN);
    else if (evolution_ == 2) evoTag = colorize("[EVO2] ", Color::MAGENTA);

    std::string core = tag + evoTag + className() + " " + name_;
    std::string hpInfo = " Lv" + std::to_string(level_) +
           " HP:" + std::to_string(static_cast<int>(currentHp)) +
           "/" + std::to_string(static_cast<int>(currentMaxHp));
    std::string rightBlock = hpInfo + " " + bar;

    if (!statusEffects.empty()) {
        for (const auto& e : statusEffects) {
            rightBlock += " " + colorize(e->getIcon(), Color::YELLOW);
        }
    }

    int coreVis = visibleLength(core);
    int rightVis = visibleLength(rightBlock);
    int padding = std::max(1, padWidth - coreVis - rightVis - 1);

    return core + std::string(padding, ' ') + rightBlock;
}

void Character::showSkillsShort() const {
    for (int i = 0; i < 4; i++) {
        if (skillSlots[i]) {
            std::string entry = std::to_string(i + 1) + ". " + skillSlots[i]->showShort();
            printBoxedLine(entry);
        }
    }
    if (ultimateSkill_) {
        std::string entry = "5. " + colorize(ultimateSkill_->showShort(), Color::MAGENTA);
        if (resource_ >= maxResource_ && ultimateSkill_->isReady()) {
            entry += " " + colorize("READY!", Color::RED);
        } else {
            entry += " " + colorize(resourceName_ + ": " + std::to_string(resource_) + "/" + std::to_string(maxResource_), Color::YELLOW);
        }
        printBoxedLine(entry);
    }
}

void Character::showSkillLong(int index) const {
    if (index < 0 || index >= 3 || !skillSlots[index]) return;
    skillSlots[index]->printDetails();
}

void Character::showFullStats() const {
    std::string header = className() + " " + name_ + " (Lv" + std::to_string(level_) + ")";
    if (evolution_ > 0) header += " [Evo" + std::to_string(evolution_) + "]";
    if (isBoss_) header = "[BOSS] " + header;
    else if (isElite_) header = "[ELITE] " + header;

    printBoxedLine(colorize(header, Color::WHITE_BOLD));

    float hp = getStat(Stat::hp);
    float maxHp = getStat(Stat::max_hp);
    printBoxedLine("  HP: " + std::to_string(static_cast<int>(hp)) + "/" + std::to_string(static_cast<int>(maxHp))
                   + " " + hpBar(hp, maxHp, 12));

    printBoxedLine("");

    auto statStr = [this](const std::string& label, const std::string& statName) -> std::string {
        if (!hasStat(statName)) return "";
        float val = getStat(statName);
        std::string valStr = (statName.find("crit") != std::string::npos || statName.find("bonus") != std::string::npos ||
                              statName.find("reduction") != std::string::npos || statName.find("block") != std::string::npos)
            ? std::to_string(static_cast<int>(val * 100)) + "%"
            : std::to_string(static_cast<int>(val));
        return "  " + colorize(label, Color::CYAN) + ": " + valStr;
    };

    std::string line;
    line = colorize("  -- COMBAT --", Color::WHITE_BOLD);
    line += statStr("ATK", Stat::attack);
    line += statStr("DMG Bonus", Stat::damage_bonus);
    printBoxedLine(line);

    line = colorize("  -- DEFENSE --", Color::WHITE_BOLD);
    line += statStr("Armor", Stat::armor);
    line += statStr("DMG Reduc", Stat::damage_reduction);
    line += statStr("Block", Stat::block_chance);
    printBoxedLine(line);

    line = colorize("  -- CRITICAL --", Color::WHITE_BOLD);
    line += statStr("Crit Chance", Stat::crit_chance);
    line += statStr("Crit Damage", Stat::crit_damage);
    printBoxedLine(line);

    if (hasStat(Stat::healing_bonus_pct) || hasStat(Stat::healing_bonus_base)) {
        line = colorize("  -- SUPPORT --", Color::WHITE_BOLD);
        line += statStr("Heal Bonus %", Stat::healing_bonus_pct);
        line += statStr("Heal Bonus Base", Stat::healing_bonus_base);
        printBoxedLine(line);
    }

    printBoxedLine("  " + colorize("EXP", Color::YELLOW)
                   + ": " + std::to_string(exp_) + "/" + std::to_string(expToNext_)
                   + "  " + colorize("Total Level", Color::WHITE_BOLD) + ": " + std::to_string(perfectLevel_));

    if (!resourceName_.empty()) {
        int resBarWidth = 10;
        int filled = static_cast<int>((static_cast<float>(resource_) / maxResource_) * resBarWidth);
        std::string resBar = "[";
        for (int i = 0; i < resBarWidth; i++) {
            resBar += (i < filled) ? "=" : "-";
        }
        resBar += "]";
        printBoxedLine("  " + colorize(resourceName_, Color::MAGENTA) + ": " + std::to_string(resource_) + "/" + std::to_string(maxResource_) + " " + colorize(resBar, Color::MAGENTA));
    }

    printBoxedLine("");
    printBoxedLine(colorize("Skills:", Color::WHITE_BOLD));
    for (const auto& skill : skillSlots) {
        if (skill) {
            std::string cd = skill->isReady() ? colorize("READY", Color::GREEN) : colorize("CD:" + std::to_string(skill->getCooldown()), Color::YELLOW);
            printBoxedLine("  " + skill->showShort() + " " + cd);
        }
    }
    if (ultimateSkill_) {
        std::string ultStatus;
        if (resource_ >= maxResource_ && ultimateSkill_->isReady()) {
            ultStatus = colorize("ULTIMATE READY!", Color::RED);
        } else {
            ultStatus = colorize(resourceName_ + ": " + std::to_string(resource_) + "/" + std::to_string(maxResource_), Color::YELLOW);
        }
        printBoxedLine("  " + colorize("ULTIMATE: ", Color::MAGENTA) + ultimateSkill_->showShort() + " " + ultStatus);
    }

    if (!passives.empty()) {
        printBoxedLine("");
        showPassives();
    }

    if (!statusEffects.empty()) {
        printBoxedLine("");
        printBoxedLine(colorize("Status Effects:", Color::WHITE_BOLD));
        for (const auto& e : statusEffects) {
            std::string effectLine = "  " + colorize(e->getIcon(), Color::YELLOW)
                                    + " " + e->getName() + " [" + std::to_string(e->getDuration()) + "T]";
            if (e->getStacks() > 1) effectLine += " x" + std::to_string(e->getStacks());
            effectLine += " - " + e->getDescription();
            printBoxedLine(effectLine);
        }
    }
}
