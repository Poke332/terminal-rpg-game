cmake_minimum_required(VERSION 3.16)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

set(SOURCES
    src/Character.cpp
    src/Game.cpp
    src/utils.cpp
    src/main.cpp

    # playable
    src/playable/Warrior.cpp
    src/playable/Mage.cpp
    src/playable/Priest.cpp
    src/playable/Archer.cpp
    src/playable/Player.cpp

    # non_playable
    src/non_playable/Enemy.cpp
    src/non_playable/Goblin.cpp
    src/non_playable/GoblinArcher.cpp
    src/non_playable/GoblinChief.cpp
    src/non_playable/GoblinSpearman.cpp

    # skills
    src/skills/Fireball.cpp
    src/skills/PrecisionShot.cpp
    src/skills/ShieldBlock.cpp
    src/skills/SingleHeal.cpp
    src/skills/Skill.cpp

    # stats
    src/stats/StatComponent.cpp
    src/stats/AddModifier.cpp

    # items
    src/items/Item.cpp
    src/items/HealthPotion.cpp
    src/items/AttackScroll.cpp
)

add_executable(DungeonCrawler ${SOURCES})

target_include_directories(DungeonCrawler PRIVATE
    include/non_playable
    include/playable
    include/skills
    include/stats
)