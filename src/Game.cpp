#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <ctime>
#include <functional>

#include "../include/Game.h"
#include "../include/utils.h"
#include "../include/stats/AddModifier.h"
#include "../include/stats/PercentModifier.h"
#include "../include/stats/StatusEffect.h"
#include "../include/passive/ElitePassive.h"

#include "../include/non_playable/Goblin.h"
#include "../include/non_playable/GoblinArcher.h"
#include "../include/non_playable/GoblinSpearman.h"
#include "../include/non_playable/GoblinChief.h"
#include "../include/non_playable/Orc.h"
#include "../include/non_playable/OrcShaman.h"
#include "../include/non_playable/Skeleton.h"
#include "../include/non_playable/DarkKnight.h"
#include "../include/non_playable/Slime.h"
#include "../include/non_playable/GoblinKing.h"
#include "../include/non_playable/OrcWarlord.h"
#include "../include/non_playable/AncientDragon.h"

#include "../include/non_playable/GoblinOverlord.h"
#include "../include/non_playable/OrcShamanLord.h"
#include "../include/non_playable/MushroomGuardian.h"
#include "../include/non_playable/SporeTitan.h"
#include "../include/non_playable/CrystalGolem.h"
#include "../include/non_playable/GemDragon.h"
#include "../include/non_playable/FireElementalLord.h"
#include "../include/non_playable/MagmaWyrm.h"
#include "../include/non_playable/ShadowWraith.h"
#include "../include/non_playable/VoidKing.h"

#include "../include/playable/archer/Archer.h"
#include "../include/playable/mage/Mage.h"
#include "../include/playable/priest/Priest.h"
#include "../include/playable/warrior/Warrior.h"

#include "../include/playable/warrior/Berserker.h"
#include "../include/playable/warrior/Warlord.h"
#include "../include/playable/mage/Sorcerer.h"
#include "../include/playable/mage/Archmage.h"
#include "../include/playable/priest/Cleric.h"
#include "../include/playable/priest/HighPriest.h"
#include "../include/playable/archer/Ranger.h"
#include "../include/playable/archer/Sniper.h"

#include "../include/items/HealthPotion.h"
#include "../include/items/AttackScroll.h"

#include "../include/Ids.h"

#include "../include/skills/PowerShot.h"
#include "../include/skills/PiercingThrust.h"
#include "../include/skills/Frenzy.h"
#include "../include/skills/ShadowBolt.h"
#include "../include/skills/Execute.h"
#include "../include/skills/SoulDrain.h"
#include "../include/skills/CorrosiveSpit.h"

using namespace Ids;

Game::Game() : rng(std::random_device{}()) {
    party.reserve(4);
    enemies.reserve(5);

    inventory.push_back(std::make_unique<HealthPotion>(3));
    inventory.push_back(std::make_unique<AttackScroll>(2));
}

void Game::partyBuildMenu() {
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(colorize("PARTY BUILDER", Color::WHITE_BOLD)) << "|" << std::endl;
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter("Choose 4 party members. Duplicates are allowed.") << "|" << std::endl;
    printDivider('-');

    struct ClassOption {
        std::string name;
        std::string description;
    };
    ClassOption options[] = {
        {"Warrior", "High HP, armor, block chance. Tank."},
        {"Mage",   "High attack, AoE and burst damage."},
        {"Priest",  "Healing and support. Buffs allies."},
        {"Archer",  "High crit, fast attacks, execute."}
    };

    for (int i = 0; i < 4; i++) {
        printBoxedLine(colorize("  " + std::to_string(i + 1) + ". " + options[i].name, Color::CYAN)
                       + " - " + options[i].description);
    }
    printDivider('-');

    for (int slot = 0; slot < 4; slot++) {
        std::string choice;
        while (true) {
            std::cout << "Party slot " << (slot + 1) << " - Choose class (1-4): ";
            if (!getline(std::cin, choice)) return;
            if (choice == "1" || choice == "2" || choice == "3" || choice == "4") break;
            std::cout << colorize("Invalid choice. Enter 1, 2, 3, or 4.", Color::RED) << std::endl;
        }

        std::cout << "Party slot " << (slot + 1) << " - Enter name: ";
        std::string name;
        if (!getline(std::cin, name)) return;
        if (name.empty()) name = options[std::stoi(choice) - 1].name + std::to_string(slot + 1);

        switch (std::stoi(choice)) {
            case 1: party.push_back(std::make_unique<Warrior>(name)); break;
            case 2: party.push_back(std::make_unique<Mage>(name)); break;
            case 3: party.push_back(std::make_unique<Priest>(name)); break;
            case 4: party.push_back(std::make_unique<Archer>(name)); break;
        }

        std::cout << colorize("  Added " + party.back()->className() + " \"" + name + "\"!", Color::GREEN) << std::endl;
    }

    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(colorize("Your Party:", Color::WHITE_BOLD)) << "|" << std::endl;
    for (const auto& ally : party) {
        std::cout << "|" << std::setfill(' ') << printCenter(ally->className()) << "|" << std::endl;
    }
    printDivider('=');
    waitForEnter();
}

void Game::runGame() {
    currentFloor = debugMode_ ? debugStartFloor_ : 1;
    surrendered_ = false;

    while (true) {
        enemies.clear();
        effectiveTurnCount_ = 0;
        dragonMinionCount_ = 0;

        if (currentFloor % 5 == 0) {
            generateBossStage(currentFloor);
        } else {
            generateFloor(currentFloor);
        }

        int allyCount = 0, enemyCount = 0;
        bool floorOver = false;
        while (!floorOver) {
            allyCount = 0;
            enemyCount = 0;
            for (const auto& ally : party) {
                if (ally->isAlive()) allyCount++;
            }
            for (const auto& enemy : enemies) {
                if (enemy->isAlive()) enemyCount++;
            }

            if (allyCount == 0 || enemyCount == 0) {
                floorOver = true;
            } else {
                playerTurn();
                if (surrendered_) { floorOver = true; break; }
                enemyTurn();
            }
        }

        if (surrendered_ || allyCount == 0) {
            gameOverMenu(currentFloor);
            return;
        }

        printDivider('=');
        printBoxedLine(colorize(getFullFloorLabel(currentFloor) + " - CLEARED!", Color::GREEN));
        printDivider('=');

        int floorExp = static_cast<int>(50 + currentFloor * 15);
        if (currentFloor % 5 == 0) floorExp = static_cast<int>(floorExp * 1.3f);
        for (auto& ally : party) {
            if (ally->isAlive()) {
                ally->addExp(floorExp);
            }
        }
        printBoxedLine(colorize("All allies gained " + std::to_string(floorExp) + " EXP!", Color::YELLOW));
        printDivider('=');

        clearPartyStatusEffects();
        checkEvolutions();
        awardFloorReward();
        currentFloor++;
    }
}

void Game::clearPartyStatusEffects() {
    for (auto& ally : party) {
        ally->clearStatusEffects();
        ally->clearAllTempModifiers();
        ally->heal(9999);
    }
}

void Game::checkEvolutions() {
    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        auto& ally = party[i];
        if (!ally->canEvolve()) continue;

        std::string oldClass = ally->className();
        int evo = ally->getEvolution();
        std::string name = ally->getName();

        std::unique_ptr<Character> evolved;

        if (oldClass == "Warrior" && evo == 0) {
            evolved = std::make_unique<Berserker>(name);
        } else if (oldClass == "Berserker" && evo == 1) {
            evolved = std::make_unique<Warlord>(name);
        } else if (oldClass == "Mage" && evo == 0) {
            evolved = std::make_unique<Sorcerer>(name);
        } else if (oldClass == "Sorcerer" && evo == 1) {
            evolved = std::make_unique<Archmage>(name);
        } else if (oldClass == "Priest" && evo == 0) {
            evolved = std::make_unique<Cleric>(name);
        } else if (oldClass == "Cleric" && evo == 1) {
            evolved = std::make_unique<HighPriest>(name);
        } else if (oldClass == "Archer" && evo == 0) {
            evolved = std::make_unique<Ranger>(name);
        } else if (oldClass == "Ranger" && evo == 1) {
            evolved = std::make_unique<Sniper>(name);
        }

        if (evolved) {
            evolved->copyStateFrom(*ally);
            std::string newClass = evolved->className();

            printDivider('=');
            printBoxedLine(colorize("  === EVOLUTION! ===", Color::MAGENTA));
            printBoxedLine(colorize("  " + oldClass + " " + name + " has evolved into " + newClass + "!", Color::MAGENTA));
            printBoxedLine(colorize("  New skills and passives unlocked!", Color::GREEN));
            printDivider('=');
            waitForEnter();

            party[i] = std::move(evolved);
        }
    }
}

void Game::awardFloorReward() {
    std::uniform_int_distribution<int> dist(0, 1);
    int roll = dist(rng);

    std::string itemName;
    if (roll == 0) {
        inventory.push_back(std::make_unique<HealthPotion>(1));
        itemName = ItemName::health_potion;
    } else {
        inventory.push_back(std::make_unique<AttackScroll>(1));
        itemName = ItemName::attack_scroll;
    }

    std::cout << "|" << std::setfill(' ') << printCenter(
        colorize("Reward: " + itemName + " added to inventory!", Color::YELLOW)) << "|" << std::endl;
    printDivider('=');
    waitForEnter();
}

void Game::generateFloor(int floorNumber) {
    enum EnemyType { GOBLIN, SLIME, GOBLIN_ARCHER, GOBLIN_SPEARMAN, GOBLIN_CHIEF, ORC, ORC_SHAMAN, SKELETON, DARK_KNIGHT, ENEMY_TYPE_COUNT };

    struct EnemyInfo { int minFloor; float baseWeight; };
    EnemyInfo info[ENEMY_TYPE_COUNT] = {
        {1, 4.0f}, {1, 3.0f}, {1, 2.5f}, {1, 2.5f},
        {3, 1.5f}, {3, 2.0f}, {3, 1.5f}, {5, 2.0f}, {7, 1.5f}
    };

    int enemyCount;
    if (floorNumber <= 3) enemyCount = 3;
    else if (floorNumber <= 6) enemyCount = 4;
    else enemyCount = 5;

    std::vector<EnemyType> available;
    std::vector<float> weights;
    for (int t = 0; t < ENEMY_TYPE_COUNT; t++) {
        if (floorNumber >= info[t].minFloor) {
            float weight = info[t].baseWeight;
            if (floorNumber > info[t].minFloor + 3) weight *= 0.5f;
            available.push_back(static_cast<EnemyType>(t));
            weights.push_back(weight);
        }
    }

    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    float statScale = 1.0f + (floorNumber - 1) * 0.04f;

    float eliteChance = 0.20f;
    if (floorNumber >= 30) {
        eliteChance = 0.20f + std::min(0.20f, (floorNumber - 30) * 0.005f);
    }
    std::uniform_real_distribution<float> eliteRoll(0.0f, 1.0f);

    auto createEnemy = [&](EnemyType type, const std::string& name) -> std::unique_ptr<Character> {
        switch (type) {
            case GOBLIN:         return std::make_unique<Goblin>(name);
            case SLIME:          return std::make_unique<Slime>(name);
            case GOBLIN_ARCHER:  return std::make_unique<GoblinArcher>(name);
            case GOBLIN_SPEARMAN:return std::make_unique<GoblinSpearman>(name);
            case GOBLIN_CHIEF:   return std::make_unique<GoblinChief>(name);
            case ORC:            return std::make_unique<Orc>(name);
            case ORC_SHAMAN:     return std::make_unique<OrcShaman>(name);
            case SKELETON:       return std::make_unique<Skeleton>(name);
            case DARK_KNIGHT:    return std::make_unique<DarkKnight>(name);
            default:             return std::make_unique<Goblin>(name);
        }
    };

    for (int i = 0; i < enemyCount; i++) {
        EnemyType type = available[dist(rng)];
        auto enemy = createEnemy(type, std::to_string(i + 1));

        if (statScale > 1.0f && enemy->hasStat(Stat::hp)) {
            float hpBonus = enemy->getStat(Stat::hp) * (statScale - 1.0f);
            float maxHpBonus = enemy->getStat(Stat::max_hp) * (statScale - 1.0f);
            float atkBonus = enemy->getStat(Stat::attack) * (statScale - 1.0f);
            enemy->modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
            enemy->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(maxHpBonus));
            enemy->modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
            if (enemy->hasStat(Stat::armor)) {
                float armorBonus = enemy->getStat(Stat::armor) * (statScale - 1.0f);
                enemy->modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
            }
        }

        if (eliteRoll(rng) < eliteChance) {
            promoteToElite(*enemy);
        }

        enemies.push_back(std::move(enemy));
    }

    printDivider('=');
    printBoxedLine(colorize(getFullFloorLabel(floorNumber), Color::WHITE_BOLD));
    printBoxedLine(colorize(std::to_string(enemyCount) + " enemies approach! (Scale: x" +
        std::to_string(statScale).substr(0, 4) + ")", Color::RED));
    printDivider('=');
    waitForEnter();
}

void Game::generateBossStage(int floorNumber) {
    std::unique_ptr<Character> boss;
    std::string minionType;
    bool isDragon = false;

    if (floorNumber >= 65) {
        int elementIndex = ((floorNumber - 65) / 5) % 5;
        auto elem = static_cast<AncientDragon::Element>(elementIndex);
        std::string latinName = AncientDragon::randomLatinName();
        boss = std::make_unique<AncientDragon>(elem, latinName);
        isDragon = true;

        float statScale = std::min(3.0f, 1.0f + (floorNumber - 1) * 0.04f);
        if (statScale > 1.0f) {
            float hpBonus = boss->getStat(Stat::hp) * (statScale - 1.0f);
            float maxHpBonus = boss->getStat(Stat::max_hp) * (statScale - 1.0f);
            float atkBonus = boss->getStat(Stat::attack) * (statScale - 1.0f);
            boss->modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
            boss->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(maxHpBonus));
            boss->modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
            if (boss->hasStat(Stat::armor)) {
                float armorBonus = boss->getStat(Stat::armor) * (statScale - 1.0f);
                boss->modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
            }
        }

        enemies.push_back(std::move(boss));

        printDivider('=');
        printBoxedLine(colorize(getFullFloorLabel(floorNumber, true), Color::RED));
        printBoxedLine(colorize(enemies[0]->className() + " has appeared!", Color::RED));
        printBoxedLine(colorize("  No minions initially... but reinforcements may arrive!", Color::YELLOW));
        printDivider('=');
        waitForEnter();
        return;
    }

    int bossGroup = (floorNumber / 5) - 1;
    switch (bossGroup) {
        case 0: boss = std::make_unique<GoblinKing>("1"); minionType = "goblin"; break;
        case 1: boss = std::make_unique<GoblinOverlord>("1"); minionType = "goblin"; break;
        case 2: boss = std::make_unique<OrcWarlord>("1"); minionType = "orc"; break;
        case 3: boss = std::make_unique<OrcShamanLord>("1"); minionType = "orc"; break;
        case 4: boss = std::make_unique<MushroomGuardian>("1"); minionType = "fungal"; break;
        case 5: boss = std::make_unique<SporeTitan>("1"); minionType = "fungal"; break;
        case 6: boss = std::make_unique<CrystalGolem>("1"); minionType = "crystal"; break;
        case 7: boss = std::make_unique<GemDragon>("1"); minionType = "crystal"; break;
        case 8: boss = std::make_unique<FireElementalLord>("1"); minionType = "fire"; break;
        case 9: boss = std::make_unique<MagmaWyrm>("1"); minionType = "fire"; break;
        case 10: boss = std::make_unique<ShadowWraith>("1"); minionType = "void"; break;
        case 11: boss = std::make_unique<VoidKing>("1"); minionType = "void"; break;
        default: boss = std::make_unique<GoblinKing>("1"); minionType = "goblin"; break;
    }

    enemies.push_back(std::move(boss));

    std::vector<std::function<std::unique_ptr<Character>(const std::string&)>> minionFactories;
    if (minionType == "goblin") {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<Goblin>(n); },
            [](const std::string& n) { return std::make_unique<GoblinArcher>(n); },
            [](const std::string& n) { return std::make_unique<GoblinSpearman>(n); },
            [](const std::string& n) { return std::make_unique<GoblinChief>(n); }
        };
    } else if (minionType == "orc") {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<Orc>(n); },
            [](const std::string& n) { return std::make_unique<OrcShaman>(n); },
            [](const std::string& n) { return std::make_unique<Orc>(n); },
            [](const std::string& n) { return std::make_unique<OrcShaman>(n); }
        };
    } else if (minionType == "fungal") {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<Slime>(n); },
            [](const std::string& n) { return std::make_unique<Slime>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); }
        };
    } else if (minionType == "crystal") {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<Skeleton>(n); },
            [](const std::string& n) { return std::make_unique<DarkKnight>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); },
            [](const std::string& n) { return std::make_unique<DarkKnight>(n); }
        };
    } else if (minionType == "fire") {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<Slime>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); },
            [](const std::string& n) { return std::make_unique<Slime>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); }
        };
    } else {
        minionFactories = {
            [](const std::string& n) { return std::make_unique<DarkKnight>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); },
            [](const std::string& n) { return std::make_unique<DarkKnight>(n); },
            [](const std::string& n) { return std::make_unique<Skeleton>(n); }
        };
    }

    for (int i = 0; i < 4; i++) {
        auto minion = minionFactories[i](std::to_string(i + 2));
        enemies.push_back(std::move(minion));
    }

    printDivider('=');
    printBoxedLine(colorize(getFullFloorLabel(floorNumber, true), Color::RED));
    printBoxedLine(colorize(enemies[0]->className() + " has appeared!", Color::RED));
    printDivider('=');
    waitForEnter();
}

void Game::promoteToElite(Character& enemy) {
    enemy.setElite(true);
    enemy.setBonusExp(enemy.getExpValue() * 2);

    float hpBonus = enemy.getStat(Stat::hp) * 0.5f;
    float maxHpBonus = enemy.getStat(Stat::max_hp) * 0.5f;
    float atkBonus = enemy.getStat(Stat::attack) * 0.3f;
    enemy.modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
    enemy.modifyStat(Stat::max_hp, std::make_unique<AddModifier>(maxHpBonus));
    enemy.modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
    if (enemy.hasStat(Stat::armor)) {
        float armorBonus = enemy.getStat(Stat::armor) * 0.3f;
        enemy.modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
    }

    assignEliteSkills(enemy);
    enemy.addPassive(std::make_unique<EliteResilience>());
}

void Game::assignEliteSkills(Character& enemy) {
    std::string t = enemy.className();
    if (t.find("Goblin") != std::string::npos || t == "Goblin") {
        if (!enemy.getSkill(0)) enemy.setSkill(0, std::make_unique<PowerShot>());
        if (!enemy.getSkill(1)) enemy.setSkill(1, std::make_unique<PiercingThrust>());
        if (!enemy.getSkill(2)) enemy.setSkill(2, std::make_unique<Frenzy>());
    } else if (t.find("Orc") != std::string::npos || t == "Orc") {
        if (!enemy.getSkill(0)) enemy.setSkill(0, std::make_unique<ShadowBolt>());
        if (!enemy.getSkill(1)) enemy.setSkill(1, std::make_unique<PowerShot>());
        if (!enemy.getSkill(2)) enemy.setSkill(2, std::make_unique<Frenzy>());
    } else if (t.find("Skeleton") != std::string::npos) {
        if (!enemy.getSkill(0)) enemy.setSkill(0, std::make_unique<Execute>());
        if (!enemy.getSkill(1)) enemy.setSkill(1, std::make_unique<SoulDrain>());
        if (!enemy.getSkill(2)) enemy.setSkill(2, std::make_unique<ShadowBolt>());
    } else if (t.find("Knight") != std::string::npos) {
        if (!enemy.getSkill(0)) enemy.setSkill(0, std::make_unique<SoulDrain>());
        if (!enemy.getSkill(1)) enemy.setSkill(1, std::make_unique<ShadowBolt>());
        if (!enemy.getSkill(2)) enemy.setSkill(2, std::make_unique<PowerShot>());
    } else if (t.find("Slime") != std::string::npos) {
        if (!enemy.getSkill(0)) enemy.setSkill(0, std::make_unique<CorrosiveSpit>());
        if (!enemy.getSkill(1)) enemy.setSkill(1, std::make_unique<PiercingThrust>());
        if (!enemy.getSkill(2)) enemy.setSkill(2, std::make_unique<Execute>());
    }
}

void Game::playerTurn() {
    for (const auto& ally : party) {

        if (!ally->isAlive()) continue;

        int aliveEnemies = 0;
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) aliveEnemies++;
        }
        if (aliveEnemies == 0) {
            ally->turnPassed();
            continue;
        }

        std::string choice, choice_atk, choice_skill, choice_item;
        bool actionTaken = false;
        while (!actionTaken) {
            fightMenu();
            showFightChoices(*ally);

            bool isPriest = (ally->className() == "Priest" || ally->className() == "Cleric" || ally->className() == "High Priest");
            bool hasUlt = ally->hasUltimateReady();

            std::string validChoices = "12345";
            if (isPriest) validChoices += "6";
            if (hasUlt) validChoices += "7";

            do {
                std::cout << colorize(ally->className() + "'s turn: ", Color::CYAN);
                if (!getline(std::cin, choice)) { surrendered_ = true; return; }
            } while (choice.empty() || validChoices.find(choice) == std::string::npos);

            if (choice == "1") {
                while (true) {
                    std::cout << "Choose enemy number to attack (or type back): ";
                    if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                    if (choice_atk == "back") break;

                    int targetIdx = -1;
                    try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                        std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                        continue;
                    }
                    if (targetIdx < 0 || targetIdx >= static_cast<int>(enemies.size())) {
                        std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                        continue;
                    }
                    if (!enemies[targetIdx]->isAlive()) {
                        std::cout << colorize("That enemy is already defeated.", Color::RED) << std::endl;
                        continue;
                    }

                    ally->attack(*enemies[targetIdx]);
                    waitForEnter();
                    actionTaken = true;
                    break;
                }
            } else if (choice == "2") {
                showSkillChoices(*ally);
                Skill* skill = nullptr;
                int slot = -1;
                while (true) {
                    std::cout << "Choose skill to cast (or type back): ";
                    if (!getline(std::cin, choice_skill)) { surrendered_ = true; return; }
                    if (choice_skill == "back") { skill = nullptr; break; }

                    if (choice_skill != "1" && choice_skill != "2" && choice_skill != "3" && choice_skill != "4") {
                        std::cout << colorize("Invalid input. Choose 1, 2, 3, or 4.", Color::RED) << std::endl;
                        continue;
                    }
                    slot = std::stoi(choice_skill) - 1;
                    skill = ally->getSkill(slot);
                    if (!skill) {
                        std::cout << colorize("That skill slot is empty.", Color::RED) << std::endl;
                        continue;
                    }
                    if (!skill->isReady()) {
                        std::cout << colorize("That skill is on cooldown.", Color::YELLOW) << std::endl;
                        continue;
                    }
                    break;
                }

                if (!skill) continue;

                if (skill->getType() == SkillType::self_cast) {
                    ally->useAbility(slot, *ally);
                    waitForEnter();
                    actionTaken = true;
                } else if (skill->getType() == SkillType::single_cast_ally) {
                    showParty();
                    while (true) {
                        std::cout << "Choose ally number to target (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(party.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!party[targetIdx]->isAlive()) {
                            std::cout << colorize("That ally is down.", Color::RED) << std::endl;
                            continue;
                        }
                        ally->useAbility(slot, *party[targetIdx]);
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                } else if (skill->getType() == SkillType::single_cast_enemy) {
                    showEnemy();
                    while (true) {
                        std::cout << "Choose enemy number to target (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(enemies.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!enemies[targetIdx]->isAlive()) {
                            std::cout << colorize("That enemy is already defeated.", Color::RED) << std::endl;
                            continue;
                        }
                        ally->useAbility(slot, *enemies[targetIdx]);
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                } else if (skill->getType() == SkillType::aoe_enemy) {
                    showEnemy();
                    while (true) {
                        std::cout << "Choose primary target (splash hits all enemies) (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(enemies.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!enemies[targetIdx]->isAlive()) {
                            std::cout << colorize("That enemy is already defeated.", Color::RED) << std::endl;
                            continue;
                        }
                        ally->getSkill(slot)->executeAoE(*ally, enemies, targetIdx, 0.6f);
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                } else if (skill->getType() == SkillType::aoe_adjacent_enemy) {
                    showEnemy();
                    while (true) {
                        std::cout << "Choose primary target (splash hits adjacent enemies) (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(enemies.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!enemies[targetIdx]->isAlive()) {
                            std::cout << colorize("That enemy is already defeated.", Color::RED) << std::endl;
                            continue;
                        }
                        Skill* sk = ally->getSkill(slot);
                        sk->setCooldown();
                        std::cout << colorize(ally->className() + " " + ally->getName(), Color::CYAN) << " uses "
                                  << colorize(sk->getName(), Color::YELLOW) << "!" << std::endl;
                        for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
                            if (!enemies[i]->isAlive()) continue;
                            int dist = std::abs(i - targetIdx);
                            if (dist == 0) {
                                sk->skillImplementation(*ally, *enemies[i]);
                                if (!enemies[i]->isAlive()) ally->addExp(enemies[i]->getExpValue() + enemies[i]->getBonusExp());
                            } else if (dist == 1) {
                                std::cout << colorize("  [Adjacent] " + enemies[i]->className() + " " + enemies[i]->getName(), Color::YELLOW) << std::endl;
                                sk->skillImplementation(*ally, *enemies[i]);
                                if (!enemies[i]->isAlive()) ally->addExp(enemies[i]->getExpValue() + enemies[i]->getBonusExp());
                            }
                        }
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                } else if (skill->getType() == SkillType::aoe_ally) {
                    ally->getSkill(slot)->executeAoEAllAlly(*ally, party, 1.0f);
                    waitForEnter();
                    actionTaken = true;
                } else if (skill->getType() == SkillType::aoe_adjacent_ally) {
                    showParty();
                    while (true) {
                        std::cout << "Choose primary ally (splash heals adjacent allies) (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(party.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!party[targetIdx]->isAlive()) {
                            std::cout << colorize("That ally is down.", Color::RED) << std::endl;
                            continue;
                        }
                        Skill* sk = ally->getSkill(slot);
                        sk->setCooldown();
                        std::cout << colorize(ally->className() + " " + ally->getName(), Color::CYAN) << " uses "
                                  << colorize(sk->getName(), Color::YELLOW) << "!" << std::endl;
                        for (int i = 0; i < static_cast<int>(party.size()); i++) {
                            if (!party[i]->isAlive()) continue;
                            int dist = std::abs(i - targetIdx);
                            if (dist <= 1) {
                                sk->skillImplementation(*ally, *party[i]);
                            }
                        }
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                }
            } else if (choice == "3") {
                if (inventory.empty()) {
                    std::cout << colorize("No items in inventory.", Color::YELLOW) << std::endl;
                    continue;
                }
                while (true) {
                    showInventory();
                    std::cout << "Choose item number (or type back): ";
                    if (!getline(std::cin, choice_item)) { surrendered_ = true; return; }
                    if (choice_item == "back") break;

                    int itemIdx = -1;
                    try { itemIdx = std::stoi(choice_item) - 1; } catch (...) {
                        std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                        continue;
                    }
                    if (itemIdx < 0 || itemIdx >= static_cast<int>(inventory.size())) {
                        std::cout << colorize("Invalid item choice.", Color::RED) << std::endl;
                        continue;
                    }
                    Item* picked = inventory[itemIdx].get();
                    if (picked->getUsable() <= 0) {
                        std::cout << colorize("That item is out of uses.", Color::YELLOW) << std::endl;
                        continue;
                    }
                    showParty();
                    while (true) {
                        std::cout << "Choose ally to use item on (or type back): ";
                        if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                        if (choice_atk == "back") break;

                        int targetIdx = -1;
                        try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                            std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                            continue;
                        }
                        if (targetIdx < 0 || targetIdx >= static_cast<int>(party.size())) {
                            std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                            continue;
                        }
                        if (!party[targetIdx]->isAlive()) {
                            std::cout << colorize("That ally is down.", Color::RED) << std::endl;
                            continue;
                        }
                        picked->useItem(*party[targetIdx]);
                        picked->decrementUsable();
                        if (picked->getUsable() <= 0) {
                            inventory.erase(inventory.begin() + itemIdx);
                        }
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                    if (actionTaken) break;
                }
            } else if (choice == "4") {
                printDivider('=');
                printBoxedLine(colorize("  PARTY:", Color::CYAN));
                for (int i = 0; i < static_cast<int>(party.size()); i++) {
                    printBoxedLine("  " + std::to_string(i + 1) + ". " + party[i]->showStatus());
                }
                printBoxedLine(colorize("  ENEMIES:", Color::RED));
                for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
                    std::string prefix = "  " + std::to_string(party.size() + i + 1) + ". ";
                    std::string status = enemies[i]->showStatus(colWidth - 2 - static_cast<int>(prefix.size()));
                    printBoxedLine(prefix + status);
                }
                printDivider('=');

                while (true) {
                    std::cout << "Choose character to inspect (or type back): ";
                    if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                    if (choice_atk == "back") break;

                    int idx = -1;
                    try { idx = std::stoi(choice_atk) - 1; } catch (...) {
                        std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                        continue;
                    }
                    int totalChars = party.size() + enemies.size();
                    if (idx < 0 || idx >= totalChars) {
                        std::cout << colorize("Invalid choice.", Color::RED) << std::endl;
                        continue;
                    }

                    if (idx < static_cast<int>(party.size())) {
                        inspectCharacter(*party[idx]);
                    } else {
                        inspectCharacter(*enemies[idx - party.size()]);
                    }
                    break;
                }
            } else if (choice == "5") {
                std::string confirm;
                std::cout << colorize("Surrender? This will end the run. (y/n): ", Color::RED);
                if (!getline(std::cin, confirm)) { surrendered_ = true; return; }
                if (confirm == "y" || confirm == "Y") {
                    surrendered_ = true;
                    return;
                }
            } else if (choice == "6" && isPriest) {
                Cleric* cleric = dynamic_cast<Cleric*>(ally.get());
                HighPriest* hp = dynamic_cast<HighPriest*>(ally.get());
                if (cleric) {
                    cleric->setMeditating(true);
                } else if (hp) {
                    hp->setMeditating(true);
                }
                std::cout << colorize(ally->className() + " meditates, focusing inner power...", Color::CYAN) << std::endl;
                ally->turnPassed();
                waitForEnter();
                actionTaken = true;
            } else if (choice == "7" && hasUlt) {
                showEnemy();
                while (true) {
                    std::cout << "Choose enemy number to target with ULTIMATE (or type back): ";
                    if (!getline(std::cin, choice_atk)) { surrendered_ = true; return; }
                    if (choice_atk == "back") break;

                    int targetIdx = -1;
                    try { targetIdx = std::stoi(choice_atk) - 1; } catch (...) {
                        std::cout << colorize("Invalid input.", Color::RED) << std::endl;
                        continue;
                    }
                    if (targetIdx < 0 || targetIdx >= static_cast<int>(enemies.size())) {
                        std::cout << colorize("Invalid target.", Color::RED) << std::endl;
                        continue;
                    }
                    if (!enemies[targetIdx]->isAlive()) {
                        std::cout << colorize("That enemy is already defeated.", Color::RED) << std::endl;
                        continue;
                    }
                    ally->useUltimate(*enemies[targetIdx]);
                    waitForEnter();
                    actionTaken = true;
                    break;
                }
            }
        }
        ally->turnPassed();
        if (debugSkillTest_) ally->resetCooldowns();
    }
}

void Game::enemyTurn() {
    std::uniform_int_distribution<int> slotDist(0, 3);

    printDivider('-');
    printBoxedLine(colorize("  --- ENEMY PHASE ---", Color::RED));
    printDivider('-');

    bool hasDragon = false;
    for (const auto& enemy : enemies) {
        if (enemy->isAlive() && enemy->isBoss() && enemy->className().find("Dragon") != std::string::npos) {
            hasDragon = true;
            break;
        }
    }

    for (const auto& enemy : enemies) {
        if (!enemy->isAlive()) continue;

        bool allyAlive = false;
        for (const auto& ally : party) {
            if (ally->isAlive()) { allyAlive = true; break; }
        }
        if (!allyAlive) break;

        std::vector<int> aliveIndices;
        for (int i = 0; i < static_cast<int>(party.size()); i++) {
            if (party[i]->isAlive()) aliveIndices.push_back(i);
        }
        std::uniform_int_distribution<int> targetDist(0, aliveIndices.size() - 1);
        int targetIdx = aliveIndices[targetDist(rng)];
        auto& ally = party[targetIdx];

        if (enemy->anyReadySkill()) {
            int startSlot = slotDist(rng);
            Skill* sk = nullptr;
            int usedSlot = -1;
            for (int i = 0; i < 4; i++) {
                int slot = (startSlot + i) % 4;
                Skill* candidate = enemy->getSkill(slot);
                if (candidate && candidate->isReady()) {
                    sk = candidate;
                    usedSlot = slot;
                    break;
                }
            }
            if (sk) {
                std::string skillType = sk->getType();
                if (skillType == SkillType::aoe_enemy) {
                    sk->executeAoE(*enemy, party, targetIdx, 0.5f);
                } else if (skillType == SkillType::aoe_adjacent_enemy) {
                    sk->setCooldown();
                    std::cout << colorize(enemy->className() + " " + enemy->getName(), Color::RED) << " uses "
                              << colorize(sk->getName(), Color::YELLOW) << "!" << std::endl;
                    for (int i = 0; i < static_cast<int>(party.size()); i++) {
                        if (!party[i]->isAlive()) continue;
                        int dist = std::abs(i - targetIdx);
                        if (dist == 0) {
                            sk->skillImplementation(*enemy, *party[i]);
                        } else if (dist == 1) {
                            std::cout << colorize("  [Adjacent] " + party[i]->className() + " " + party[i]->getName(), Color::YELLOW) << std::endl;
                            sk->skillImplementation(*enemy, *party[i]);
                        }
                    }
                } else if (skillType == SkillType::aoe_ally) {
                    sk->executeAoEAllAlly(*enemy, enemies, 0.7f);
                } else {
                    enemy->useAbility(usedSlot, *ally);
                }
            } else {
                enemy->attack(*ally);
            }
        } else {
            enemy->attack(*ally);
        }
    }

    if (hasDragon) {
        effectiveTurnCount_++;
        if (effectiveTurnCount_ >= 5 && dragonMinionCount_ < 4) {
            int toSpawn = std::min(2, 4 - dragonMinionCount_);
            float statScale = std::min(3.0f, 1.0f + (currentFloor - 1) * 0.04f);

            std::vector<std::function<std::unique_ptr<Character>(const std::string&)>> minionFactories = {
                [](const std::string& n) { return std::make_unique<Skeleton>(n); },
                [](const std::string& n) { return std::make_unique<DarkKnight>(n); }
            };

            printDivider('-');
            for (int i = 0; i < toSpawn; i++) {
                auto minion = minionFactories[i % 2](std::to_string(enemies.size() + 1));
                if (statScale > 1.0f) {
                    float hpBonus = minion->getStat(Stat::hp) * (statScale - 1.0f);
                    float maxHpBonus = minion->getStat(Stat::max_hp) * (statScale - 1.0f);
                    float atkBonus = minion->getStat(Stat::attack) * (statScale - 1.0f);
                    minion->modifyStat(Stat::hp, std::make_unique<AddModifier>(hpBonus));
                    minion->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(maxHpBonus));
                    minion->modifyStat(Stat::attack, std::make_unique<AddModifier>(atkBonus));
                    if (minion->hasStat(Stat::armor)) {
                        float armorBonus = minion->getStat(Stat::armor) * (statScale - 1.0f);
                        minion->modifyStat(Stat::armor, std::make_unique<AddModifier>(armorBonus));
                    }
                }
                enemies.push_back(std::move(minion));
                dragonMinionCount_++;
            }
            printBoxedLine(colorize("  " + std::to_string(toSpawn) + " minions have joined the battle!", Color::YELLOW));
            printDivider('-');
            effectiveTurnCount_ = 0;
        }
    }

    printDivider('=');
    waitForEnter();
}

void Game::debugMenu() {
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(colorize("DEBUG MODE", Color::MAGENTA)) << "|" << std::endl;
    printDivider('=');
    printBoxedLine(colorize("  1. Custom Floor Start", Color::CYAN));
    printBoxedLine(colorize("  2. Deploy Admin Party", Color::CYAN));
    printBoxedLine(colorize("  3. Both (Admin Party + Custom Floor)", Color::CYAN));
    printBoxedLine(colorize("  4. Skill Testing Mode (No Cooldowns)", Color::CYAN));
    printBoxedLine(colorize("  5. Back to Main Menu", Color::YELLOW));
    printDivider('=');

    std::string choice;
    do {
        std::cout << "Your choice: ";
        if (!getline(std::cin, choice)) return;
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5");

    if (choice == "5") return;

    debugMode_ = true;
    debugSkillTest_ = false;
    debugStartFloor_ = 1;

    if (choice == "1" || choice == "3") {
        std::string floorStr;
        while (true) {
            std::cout << "Enter starting floor (1-999): ";
            if (!getline(std::cin, floorStr)) return;
            try {
                int f = std::stoi(floorStr);
                if (f >= 1 && f <= 999) {
                    debugStartFloor_ = f;
                    break;
                }
            } catch (...) {}
            std::cout << colorize("Invalid floor number.", Color::RED) << std::endl;
        }
    }

    if (choice == "4") {
        debugSkillTest_ = true;
        std::string floorStr;
        while (true) {
            std::cout << "Enter starting floor (1-999): ";
            if (!getline(std::cin, floorStr)) return;
            try {
                int f = std::stoi(floorStr);
                if (f >= 1 && f <= 999) {
                    debugStartFloor_ = f;
                    break;
                }
            } catch (...) {}
            std::cout << colorize("Invalid floor number.", Color::RED) << std::endl;
        }
        deployDebugParty();
        printDivider('=');
        printBoxedLine(colorize("  DEBUG: Skill Testing Mode Active", Color::MAGENTA));
        printBoxedLine(colorize("  All cooldowns reset every turn", Color::MAGENTA));
        printBoxedLine(colorize("  Starting at Floor " + std::to_string(debugStartFloor_), Color::MAGENTA));
        printDivider('=');
        waitForEnter();
        runGame();
        debugMode_ = false;
        debugSkillTest_ = false;
        debugStartFloor_ = 1;
        return;
    }

    if (choice == "2" || choice == "3") {
        deployDebugParty();
    } else {
        partyBuildMenu();
    }

    printDivider('=');
    printBoxedLine(colorize("  DEBUG: Starting at Floor " + std::to_string(debugStartFloor_), Color::MAGENTA));
    printDivider('=');
    waitForEnter();

    runGame();
    debugMode_ = false;
    debugSkillTest_ = false;
    debugStartFloor_ = 1;
}

void Game::deployDebugParty() {
    party.clear();

    printDivider('=');
    printBoxedLine(colorize("  Deploying Admin Party...", Color::MAGENTA));
    printDivider('=');

    auto warrior = std::make_unique<Warrior>("DebugWarrior");
    for (int i = 0; i < 19; i++) warrior->addExp(9999);
    warrior->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(60.0f));
    warrior->modifyStat(Stat::hp, std::make_unique<AddModifier>(60.0f));
    warrior->modifyStat(Stat::attack, std::make_unique<AddModifier>(7.0f));
    warrior->modifyStat(Stat::armor, std::make_unique<AddModifier>(5.0f));
    party.push_back(std::move(warrior));

    auto mage = std::make_unique<Mage>("DebugMage");
    for (int i = 0; i < 19; i++) mage->addExp(9999);
    mage->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(30.0f));
    mage->modifyStat(Stat::hp, std::make_unique<AddModifier>(30.0f));
    mage->modifyStat(Stat::attack, std::make_unique<AddModifier>(12.0f));
    mage->modifyStat(Stat::armor, std::make_unique<AddModifier>(2.0f));
    party.push_back(std::move(mage));

    auto priest = std::make_unique<Priest>("DebugPriest");
    for (int i = 0; i < 19; i++) priest->addExp(9999);
    priest->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(40.0f));
    priest->modifyStat(Stat::hp, std::make_unique<AddModifier>(40.0f));
    priest->modifyStat(Stat::attack, std::make_unique<AddModifier>(8.0f));
    priest->modifyStat(Stat::armor, std::make_unique<AddModifier>(3.0f));
    party.push_back(std::move(priest));

    auto archer = std::make_unique<Archer>("DebugArcher");
    for (int i = 0; i < 19; i++) archer->addExp(9999);
    archer->modifyStat(Stat::max_hp, std::make_unique<AddModifier>(30.0f));
    archer->modifyStat(Stat::hp, std::make_unique<AddModifier>(30.0f));
    archer->modifyStat(Stat::attack, std::make_unique<AddModifier>(10.0f));
    archer->modifyStat(Stat::armor, std::make_unique<AddModifier>(3.0f));
    party.push_back(std::move(archer));

    for (auto& ally : party) {
        ally->heal(9999);
        ally->resetCooldowns();
    }

    printBoxedLine(colorize("  Admin Party Deployed!", Color::GREEN));
    for (const auto& ally : party) {
        printBoxedLine("  " + ally->className() + " " + ally->getName() + " Lv" + std::to_string(ally->getLevel())
                       + " HP:" + std::to_string(static_cast<int>(ally->getStat(Stat::hp)))
                       + "/" + std::to_string(static_cast<int>(ally->getStat(Stat::max_hp))));
    }
    printDivider('=');
}

void Game::mainMenu() const {
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(colorize(title, Color::WHITE_BOLD)) << "|" << std::endl;
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter("A party of 4 adventurers descends into the") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("endless Goblin's Den. Build your party,") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("survive the floors, and see how deep you can go!") << "|" << std::endl;
    printDivider('=');
    printThreeCols("1. Start Game", "2. Party Detail", "3. Debug Mode");
    printBoxedLine(colorize("4. Quit Game", Color::RED));
    printDivider('=');
}

void Game::fightMenu() const {
    printDivider('=');
    printBoxedLine(colorize(getFullFloorLabel(currentFloor), Color::WHITE_BOLD));
    printDivider('-');
    for (const auto& ally : party) {
        std::string line = colorize(ally->showStatus(), ally->isAlive() ? Color::CYAN : Color::RED);
        printBoxedLine(line);
    }
    printDivider('-');
    for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
        const auto& enemy = enemies[i];
        std::string prefix = colorize(std::to_string(i + 1) + ".", Color::YELLOW);
        int prefixVis = visibleLength(prefix + " ");
        std::string status = enemy->showStatus(colWidth - 2 - prefixVis);
        std::string line = prefix + " " + colorize(status, enemy->isAlive() ? Color::RED : Color::YELLOW);
        printBoxedLine(line);
    }
    printDivider('=');
}

void Game::characterDetailMenu() const {
    printDivider('-');
    for (const auto& ally : party) {
        std::cout << std::endl;
        ally->showFullStats();
        std::cout << std::endl;
        waitForEnter();
    }
    printDivider('-');
}

void Game::inspectCharacter(const Character& c) const {
    printDivider('=');
    c.showFullStats();
    printDivider('=');
    waitForEnter();
}

void Game::gameOverMenu(int floor_num) {
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(colorize("GAME OVER", Color::RED)) << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter(
        colorize("REACHED: " + getFullFloorLabel(floor_num), Color::YELLOW)) << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter(title) << "|" << std::endl;
    printDivider('=');
    printDivider(' ');
    std::cout << "|" << std::setfill(' ') << printCenter("Your party fought bravely but fell in the depths.") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("The dungeon claims another group of heroes...") << "|" << std::endl;
    printDivider(' ');
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << std::left << std::setw((colWidth / 2))
              << "1. Retry" << std::left << std::setw((colWidth / 2)) << "2. Quit Game" << "|" << std::endl;
    printDivider('=');
}

void Game::showParty() const {
    printDivider('=');
    for (const auto& ally : party) {
        std::string line = colorize(ally->showStatus(), ally->isAlive() ? Color::CYAN : Color::RED);
        printBoxedLine(line);
    }
    printDivider('=');
}

void Game::showEnemy() const {
    printDivider('=');
    for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
        const auto& enemy = enemies[i];
        std::string prefix = colorize(std::to_string(i + 1) + ".", Color::YELLOW);
        int prefixVis = visibleLength(prefix + " ");
        std::string status = enemy->showStatus(colWidth - 2 - prefixVis);
        std::string line = prefix + " " + colorize(status, enemy->isAlive() ? Color::RED : Color::YELLOW);
        printBoxedLine(line);
    }
    printDivider('=');
}

void Game::showFightChoices(const Character& ally) const {
    printDivider('-');
    printThreeCols(
        colorize("1. Attack", Color::WHITE_BOLD),
        colorize("2. Cast Skill", Color::WHITE_BOLD),
        colorize("3. Use Item", Color::WHITE_BOLD)
    );

    std::string col1 = colorize("4. View Char", Color::WHITE_BOLD);
    std::string col2 = colorize("5. Surrender", Color::RED);
    std::string col3;

    bool isPriest = (ally.className() == "Priest" || ally.className() == "Cleric" || ally.className() == "High Priest");
    if (isPriest) {
        col3 = colorize("6. Meditate", Color::CYAN);
    }

    printThreeCols(col1, col2, col3);

    if (ally.hasUltimateReady()) {
        printBoxedLine(colorize("  7. ULTIMATE: " + ally.getUltimateSkill()->showShort(), Color::MAGENTA));
    }

    printDivider('-');
}

void Game::showSkillChoices(const Character& ally) const {
    printDivider('-');
    ally.showSkillsShort();
    printDivider('-');
}

void Game::showInventory() {
    printDivider('-');
    int i = 1;
    for (const auto& item : inventory) {
        std::string entry = std::to_string(i) + ". " + item->getName() + " x" + std::to_string(item->getUsable());
        printBoxedLine(colorize(entry, Color::GREEN));
        i++;
    }
    printDivider('-');
}
