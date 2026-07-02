#include "../../include/playable/priest/Cleric.h"
#include "../../include/playable/priest/PriestEvoSkills.h"
#include "../../include/playable/priest/PriestEvoPassive.h"
#include "../../include/passive/PriestPassive.h"
#include "../../include/playable/priest/HighPriest.h"
#include "../../include/utils.h"
#include <iostream>

Cleric::Cleric(const std::string& n)
    : Player(n, "human") {
        registerStat("hp", 120.0f);
        registerStat("max_hp", 120.0f);
        registerStat("armor", 5.0f);
        registerStat("attack", 14.0f);
        registerStat("crit_chance", 0.08f);
        registerStat("crit_damage", 0.5f);
        registerStat("healing_bonus_percentage", 0.15f);
        registerStat("healing_bonus_base", 8.0f);

        skillSlots[0] = std::make_unique<MassHeal>();
        skillSlots[1] = std::make_unique<HolyWrath>();
        skillSlots[2] = std::make_unique<DivineFavor>();

        evolution_ = 1;
        resourceName_ = "Meditation";
        maxResource_ = 5;

        addPassive(std::make_unique<HolyBlessing>());
}

std::string Cleric::className() const {
    return "Cleric";
}

int Cleric::heal(float h) {
    float newHeal = (h * (1.0f + getStat("healing_bonus_percentage")) + getStat("healing_bonus_base"));
    return Character::heal(newHeal);
}

void Cleric::checkPassiveUnlock() {
    if (getLevel() == 10 && passives.size() < 2) {
        addPassive(std::make_unique<DivineAegis>());
    }
}

void Cleric::onCombatAction() {
    if (meditating_) {
        gainResource(1);
        std::cout << colorize("Meditation... [" + std::to_string(resource_) + "/" + std::to_string(maxResource_) + "]", Color::CYAN) << std::endl;
        meditating_ = false;
    }
}

bool Cleric::canEvolve() const {
    return evolution_ < 2 && level_ >= 20;
}

void Cleric::evolve() {
    std::cout << colorize("=== EVOLUTION ===", Color::MAGENTA) << std::endl;
    std::cout << colorize("Cleric has evolved into High Priest!", Color::MAGENTA) << std::endl;
    Character::evolve();
}

void Cleric::setMeditating(bool v) { meditating_ = v; }
bool Cleric::isMeditating() const { return meditating_; }
