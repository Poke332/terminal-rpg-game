mkdir build/

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT="$PROJECT_DIR/build/DungeonCrawler.exe"

x86_64-w64-mingw32-g++-posix -static -static-libgcc -static-libstdc++ -std=c++17 -Wall -Wextra -pedantic\
  -I"$PROJECT_DIR/include" \
  -I"$PROJECT_DIR/include/non_playable" \
  -I"$PROJECT_DIR/include/playable" \
  -I"$PROJECT_DIR/include/skills" \
  -I"$PROJECT_DIR/include/stats" \
  "$PROJECT_DIR/src/Character.cpp" \
  "$PROJECT_DIR/src/Game.cpp" \
  "$PROJECT_DIR/src/utils.cpp" \
  "$PROJECT_DIR/src/main.cpp" \
  "$PROJECT_DIR/src/playable/Warrior.cpp" \
  "$PROJECT_DIR/src/playable/Mage.cpp" \
  "$PROJECT_DIR/src/playable/Priest.cpp" \
  "$PROJECT_DIR/src/playable/Archer.cpp" \
  "$PROJECT_DIR/src/playable/Player.cpp" \
  "$PROJECT_DIR/src/non_playable/Enemy.cpp" \
  "$PROJECT_DIR/src/non_playable/Goblin.cpp" \
  "$PROJECT_DIR/src/non_playable/GoblinArcher.cpp" \
  "$PROJECT_DIR/src/non_playable/GoblinChief.cpp" \
  "$PROJECT_DIR/src/non_playable/GoblinSpearman.cpp" \
  "$PROJECT_DIR/src/skills/Fireball.cpp" \
  "$PROJECT_DIR/src/skills/PrecisionShot.cpp" \
  "$PROJECT_DIR/src/skills/ShieldBlock.cpp" \
  "$PROJECT_DIR/src/skills/SingleHeal.cpp" \
  "$PROJECT_DIR/src/skills/Skill.cpp" \
  "$PROJECT_DIR/src/stats/StatComponent.cpp" \
  "$PROJECT_DIR/src/stats/AddModifier.cpp" \
  -o "$OUTPUT"

echo "Build complete: $OUTPUT"
