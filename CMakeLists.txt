cmake_minimum_required(VERSION 3.16)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/Character.cpp
    src/Game.cpp
    src/utils.cpp
    src/main.cpp

    # playable - base
    src/playable/Player.cpp
    src/playable/warrior/Warrior.cpp
    src/playable/mage/Mage.cpp
    src/playable/priest/Priest.cpp
    src/playable/archer/Archer.cpp

    # playable - evolutions
    src/playable/warrior/Berserker.cpp
    src/playable/warrior/Warlord.cpp
    src/playable/mage/Sorcerer.cpp
    src/playable/mage/Archmage.cpp
    src/playable/priest/Cleric.cpp
    src/playable/priest/HighPriest.cpp
    src/playable/archer/Ranger.cpp
    src/playable/archer/Sniper.cpp

    # playable - evolution skills
    src/playable/warrior/WarriorEvoSkills.cpp
    src/playable/mage/MageEvoSkills.cpp
    src/playable/priest/PriestEvoSkills.cpp
    src/playable/archer/ArcherEvoSkills.cpp

    # playable - evolution passives
    src/playable/warrior/WarriorEvoPassive.cpp
    src/playable/mage/MageEvoPassive.cpp
    src/playable/priest/PriestEvoPassive.cpp
    src/playable/archer/ArcherEvoPassive.cpp

    # non_playable
    src/non_playable/Enemy.cpp
    src/non_playable/Goblin.cpp
    src/non_playable/GoblinArcher.cpp
    src/non_playable/GoblinChief.cpp
    src/non_playable/GoblinSpearman.cpp
    src/non_playable/Orc.cpp
    src/non_playable/OrcShaman.cpp
    src/non_playable/Skeleton.cpp
    src/non_playable/DarkKnight.cpp
    src/non_playable/Slime.cpp
    src/non_playable/GoblinKing.cpp
    src/non_playable/OrcWarlord.cpp
    src/non_playable/Lich.cpp
    src/non_playable/AncientDragon.cpp

    # skills - existing
    src/skills/Fireball.cpp
    src/skills/PrecisionShot.cpp
    src/skills/ShieldBlock.cpp
    src/skills/SingleHeal.cpp
    src/skills/Skill.cpp

    # skills - player new
    src/skills/WarCry.cpp
    src/skills/ShieldBash.cpp
    src/skills/ArcaneBlast.cpp
    src/skills/FrostNova.cpp
    src/skills/DivineSmite.cpp
    src/skills/Blessing.cpp
    src/skills/RainOfArrows.cpp
    src/skills/QuickShot.cpp

    # skills - enemy new
    src/skills/ShadowBolt.cpp
    src/skills/Execute.cpp
    src/skills/SoulDrain.cpp
    src/skills/CorrosiveSpit.cpp
    src/skills/PowerShot.cpp
    src/skills/PiercingThrust.cpp
    src/skills/Frenzy.cpp

    # stats
    src/stats/StatComponent.cpp
    src/stats/AddModifier.cpp
    src/stats/PercentModifier.cpp
    src/stats/StatusEffect.cpp

    # passive
    src/passive/Passive.cpp
    src/passive/WarriorPassive.cpp
    src/passive/MagePassive.cpp
    src/passive/PriestPassive.cpp
    src/passive/ArcherPassive.cpp
    src/passive/ElitePassive.cpp

    # items
    src/items/Item.cpp
    src/items/HealthPotion.cpp
    src/items/AttackScroll.cpp
)

add_executable(DungeonCrawler ${SOURCES})

target_include_directories(DungeonCrawler PRIVATE
    include/non_playable
    include/playable
    include/playable/warrior
    include/playable/mage
    include/playable/priest
    include/playable/archer
    include/skills
    include/stats
    include/passive
)
