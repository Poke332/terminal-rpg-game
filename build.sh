#!/bin/bash
cd "$(dirname "${BASH_SOURCE[0]}")"

mkdir -p build/

TARGET="${1:-auto}"

# Resolve 'auto' by detecting OS
if [[ "$TARGET" == "auto" ]]; then
    if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
        TARGET="windows"
    else
        TARGET="linux"
    fi
fi

# Set compiler and output based on target
case "$TARGET" in
    windows)
        CXX="x86_64-w64-mingw32-g++"
        FLAGS="-static -static-libgcc -static-libstdc++"
        OUTPUT="build/DungeonCrawler.exe"
        ;;
    linux)
        CXX="g++"
        FLAGS=""
        OUTPUT="build/DungeonCrawler"
        ;;
    *)
        echo "Unknown target: '$TARGET'. Use: ./build.sh [windows|linux]"
        exit 1
        ;;
esac

echo "Building for $TARGET..."

$CXX $FLAGS -std=c++17 -Wall -Wextra -pedantic \
  -Iinclude \
  -Iinclude/non_playable \
  -Iinclude/playable \
  -Iinclude/skills \
  -Iinclude/stats \
  -Iinclude/items \
  src/Character.cpp \
  src/Game.cpp \
  src/utils.cpp \
  src/main.cpp \
  src/playable/Warrior.cpp \
  src/playable/Mage.cpp \
  src/playable/Priest.cpp \
  src/playable/Archer.cpp \
  src/playable/Player.cpp \
  src/non_playable/Enemy.cpp \
  src/non_playable/Goblin.cpp \
  src/non_playable/GoblinArcher.cpp \
  src/non_playable/GoblinChief.cpp \
  src/non_playable/GoblinSpearman.cpp \
  src/skills/Fireball.cpp \
  src/skills/PrecisionShot.cpp \
  src/skills/ShieldBlock.cpp \
  src/skills/SingleHeal.cpp \
  src/skills/Skill.cpp \
  src/stats/StatComponent.cpp \
  src/stats/AddModifier.cpp \
  src/items/Item.cpp \
  src/items/HealthPotion.cpp \
  src/items/AttackScroll.cpp \
  -o "$OUTPUT"

echo "Build complete: $OUTPUT"