# Dungeon Crawler

A terminal-based RPG dungeon crawler built in C++17. Assemble a party of 4 adventurers, descend into the endless Goblin's Den, and see how deep you can go.

## Features

### Party System
- Choose from **4 base classes**: Warrior, Mage, Priest, Archer
- Build a party of 4 — duplicates allowed
- Name each party member

### Class Evolution System
Each class evolves twice, gaining new skills, passives, and a unique resource mechanic:

| Base | 1st Evolution | 2nd Evolution | Resource | Ultimate |
|------|---------------|---------------|----------|----------|
| Warrior | Berserker | Warlord | Rage | Titan's Strike |
| Mage | Sorcerer | Archmage | Focus | Arcane Annihilation |
| Priest | Cleric | High Priest | Meditation | Divine Intervention |
| Archer | Ranger | Sniper | Focus | Perfect Shot |

- **Level 20**: First evolution — class resets to Level 1, stats preserved, 3 evolved skills + 2 passives
- **Level 40**: Second evolution — class resets to Level 1, stats preserved, 3 further evolved skills + 3 passives
- **Level 60**: Ultimate skill unlocked — requires full resource meter to activate

### Resource Mechanics
- **Warrior (Rage)**: Builds when taking damage. Ultimate requires 100 rage.
- **Mage (Focus)**: Builds when casting skills (+20 per cast). Ultimate requires 100 focus.
- **Priest (Meditation)**: Builds via the Meditate combat action. Ultimate requires 5 stacks.
- **Archer (Focus)**: Builds on successful attacks (+1), lost when taking damage. Ultimate requires 5 focus.

### Combat
- Turn-based combat with 4 party members vs up to 5 enemies
- Actions: Attack, Cast Skill, Use Item, View Character, Surrender, Meditate (Priest), Ultimate (when ready)
- Skills have cooldowns, status effects, and scaling damage
- Status effects: Burning (DoT), Chilled (% debuffs), Weakened (-ATK), Corroded (-armor)

### Progression
- Endless dungeon with increasing difficulty (8% stat scaling per floor)
- Elite enemies (20% chance, scaling up) with bonus skills and passives
- Boss stages every 15 floors with unique bosses and minions
- EXP from kills and floor clears
- Floor names and layer colors based on depth

### Items
- **Health Potion**: Restores HP to an ally
- **Attack Scroll**: Permanently boosts an ally's attack

## Building

### Prerequisites
- CMake 3.16+
- GCC/G++ with C++17 support (or any C++17 compliant compiler)

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd DungeonCrawler

# Create build directory and compile
mkdir build
cd build
cmake ..
make

# Run the game
./DungeonCrawler
```

### Quick Build (Linux/WSL)

```bash
rm -rf build && mkdir build && cd build && cmake .. && make -j$(nproc) && ./DungeonCrawler
```

## Project Structure

```
DungeonCrawler/
├── CMakeLists.txt
├── include/
│   ├── Character.h
│   ├── Game.h
│   ├── utils.h
│   ├── items/
│   │   ├── Item.h
│   │   ├── HealthPotion.h
│   │   └── AttackScroll.h
│   ├── non_playable/
│   │   ├── Enemy.h
│   │   ├── Goblin.h, GoblinArcher.h, GoblinChief.h, GoblinSpearman.h
│   │   ├── Orc.h, OrcShaman.h
│   │   ├── Skeleton.h, DarkKnight.h, Slime.h
│   │   └── GoblinKing.h, OrcWarlord.h, Lich.h, AncientDragon.h
│   ├── passive/
│   │   ├── Passive.h
│   │   ├── WarriorPassive.h, MagePassive.h, PriestPassive.h, ArcherPassive.h
│   │   └── ElitePassive.h
│   ├── playable/
│   │   ├── Player.h
│   │   ├── warrior/
│   │   │   ├── Warrior.h, Berserker.h, Warlord.h
│   │   │   ├── WarriorEvoSkills.h
│   │   │   └── WarriorEvoPassive.h
│   │   ├── mage/
│   │   │   ├── Mage.h, Sorcerer.h, Archmage.h
│   │   │   ├── MageEvoSkills.h
│   │   │   └── MageEvoPassive.h
│   │   ├── priest/
│   │   │   ├── Priest.h, Cleric.h, HighPriest.h
│   │   │   ├── PriestEvoSkills.h
│   │   │   └── PriestEvoPassive.h
│   │   └── archer/
│   │       ├── Archer.h, Ranger.h, Sniper.h
│   │       ├── ArcherEvoSkills.h
│   │       └── ArcherEvoPassive.h
│   ├── skills/
│   │   ├── Skill.h
│   │   ├── Fireball.h, ArcaneBlast.h, FrostNova.h
│   │   ├── ShieldBlock.h, WarCry.h, ShieldBash.h
│   │   ├── SingleHeal.h, DivineSmite.h, Blessing.h
│   │   ├── PrecisionShot.h, RainOfArrows.h, QuickShot.h
│   │   └── (enemy skills...)
│   └── stats/
│       ├── StatComponent.h, StatModifier.h
│       ├── AddModifier.h, PercentModifier.h
│       └── StatusEffect.h
└── src/
    ├── Character.cpp, Game.cpp, utils.cpp, main.cpp
    ├── playable/       (mirrors include/playable/ structure)
    ├── non_playable/
    ├── skills/
    ├── stats/
    ├── passive/
    └── items/
```

## Controls

| Action | Input |
|--------|-------|
| Select menu option | Type the number and press Enter |
| Attack | `1` → choose enemy |
| Cast Skill | `2` → choose skill → choose target |
| Use Item | `3` → choose item → choose ally |
| View Character | `4` → choose character |
| Surrender | `5` → confirm with `y` |
| Meditate (Priest) | `6` |
| Ultimate (when ready) | `7` → choose enemy |
| Go back | Type `back` |
| Continue | Press Enter |

## License

This project is for educational and personal use.
