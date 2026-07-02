#include "../../include/playable/priest/HighPriest.h"
#include "../../include/playable/priest/PriestEvoSkills.h"
#include "../../include/playable/priest/PriestEvoPassive.h"
#include "../../include/passive/PriestPassive.h"
#include "../../include/utils.h"
#include <iostream>
#include "../../include/Ids.h"

using namespace Ids;

HighPriest::HighPriest(const std::string& n)
    : Player(n, "human") {
        registerStat(Stat::hp, 150.0f);
        registerStat(Stat::max_hp, 150.0f);
        registerStat(Stat::armor, 7.0f);
        registerStat(Stat::attack, 18.0f);
        registerStat(Stat::crit_chance, 0.10f);
        registerStat(Stat::crit_damage, 0.5f);
        registerStat(Stat::healing_bonus_pct, 0.25f);
        registerStat(Stat::healing_bonus_base, 12.0f);

        skillSlots[0] = std::make_unique<SanctuaryHeal>();
        skillSlots[1] = std::make_unique<Judgment>();
        skillSlots[2] = std::make_unique<HolyCovenant>();

        evolution_ = 2;
        resourceName_ = Resource::meditation;
        maxResource_ = 5;

        addPassive(std::make_unique<HolyBlessing>());
}

std::string HighPriest::className() const {
    return "High Priest";
}

int HighPriest::heal(float h) {
    float newHeal = (h * (1.0f + getStat(Stat::healing_bonus_pct)) + getStat(Stat::healing_bonus_base));
    return Character::heal(newHeal);
}

void HighPriest::checkPassiveUnlock() {
    if (getLevel() == 5 && passives.size() < 2) {
        addPassive(std::make_unique<DivineAegis>());
    }
    if (getLevel() == 15 && passives.size() < 3) {
        addPassive(std::make_unique<Sanctuary>());
    }
    if (getLevel() == 20) {
        setUltimateSkill(std::make_unique<DivineIntervention>());
        std::cout << colorize("ULTIMATE UNLOCKED: Divine Intervention!", Color::MAGENTA) << std::endl;
    }
}

void HighPriest::onCombatAction() {
    if (meditating_) {
        gainResource(1);
        std::cout << colorize("Meditation... [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
        meditating_ = false;
    }
}

void HighPriest::setMeditating(bool v) { meditating_ = v; }
bool HighPriest::isMeditating() const { return meditating_; }
