#include "WarCry.h"
#include "../Character.h"
#include "../stats/AddModifier.h"
#include "../utils.h"
#include "../../include/Ids.h"

#include <iostream>

using namespace Ids;

WarCry::WarCry()
    : Skill("War Cry",
            "Lets out a battle cry, boosting attack power by 5 for the rest of combat",
            SkillType::self_cast, 0.0f, 0.0f, 4) {}

void WarCry::skillImplementation(Character& user, Character& target) {
    user.modifyStat(Stat::attack, std::make_unique<AddModifier>(5.0f));
    std::cout << colorize("War Cry! Attack increased by 5!", Color::YELLOW) << std::endl;
}
