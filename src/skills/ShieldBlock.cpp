#include "../../include/skills/ShieldBlock.h"
#include "../../include/playable/Warrior.h"
#include "../../include/Character.h"

#include <iostream>

ShieldBlock::ShieldBlock()
    : Skill("Shield Block", 
            "Raises your shield in preperation to block, Only usable by Warriors",
            "self_cast",
            0.0f,
            0.0f,
            3) {}

void ShieldBlock::skillImplementation(Character& user, Character& target) {
    Warrior* warrior = dynamic_cast<Warrior*>(&user);
    if (!warrior) return;
    warrior->setGuaranteeBlock(true);
    std::cout << "You raised your shield in preperation!" << std::endl;
}