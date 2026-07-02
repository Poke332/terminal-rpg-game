#include "Blessing.h"
#include "../Character.h"
#include "../stats/AddModifier.h"
#include "../utils.h"
#include <iostream>

Blessing::Blessing()
    : Skill("Blessing",
            "Bestows a divine blessing, permanently increasing an ally's attack by 5",
            "single_cast_ally", 0.0f, 0.0f, 4) {}

void Blessing::skillImplementation(Character& user, Character& target) {
    target.modifyStat("attack", std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("Blessing! " + target.className() + "'s attack increased by 5!", Color::GREEN) << std::endl;
}
