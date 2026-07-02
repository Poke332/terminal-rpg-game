#include "../../include/skills/ShieldBlock.h"
#include "../../include/playable/warrior/Warrior.h"
#include "../../include/Character.h"
#include "../../include/Ids.h"
#include "../../include/utils.h"

#include <iostream>

using namespace Ids;

ShieldBlock::ShieldBlock()
    : Skill("Shield Block", 
            "Raises your shield in preparation to block. Only usable by Warriors",
            SkillType::self_cast,
            0.0f,
            0.0f,
            3) {}

void ShieldBlock::skillImplementation(Character& user, Character& target) {
    Warrior* warrior = dynamic_cast<Warrior*>(&user);
    if (!warrior) return;
    warrior->setGuaranteeBlock(true);
    std::cout << colorize("You raised your shield in preparation!", Color::CYAN) << std::endl;
}
