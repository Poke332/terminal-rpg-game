#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "../include/Game.h"
#include "../include/utils.h"

#include "../include/non_playable/Goblin.h"
#include "../include/non_playable/GoblinArcher.h"
#include "../include/non_playable/GoblinSpearman.h"
#include "../include/non_playable/GoblinChief.h"

#include "../include/playable/Archer.h"
#include "../include/playable/Mage.h"
#include "../include/playable/Priest.h"
#include "../include/playable/Warrior.h"

#include "../include/items/HealthPotion.h"
#include "../include/items/AttackScroll.h"

Game::Game() {
    party.reserve(4);
    enemies.reserve(4);

    party.push_back(std::make_unique<Warrior>("Alex"));
    party.push_back(std::make_unique<Mage>("Ellision"));
    party.push_back(std::make_unique<Priest>("Elira"));
    party.push_back(std::make_unique<Archer>("Avery"));

    inventory.push_back(std::make_unique<HealthPotion>(3));
    inventory.push_back(std::make_unique<AttackScroll>(2));
}

void Game::runGame() {
    for (int w = 1; w <= totalWaves; w++) {
        enemies.clear();
        spawnWaves(w);
        int allyCount = 0, enemyCount = 0;

        bool waveOver = false;
        while(!waveOver) {
            allyCount = 0;
            enemyCount = 0;
            for (const auto& ally : party) {
                if (ally->isAlive()) allyCount++;
            }

            for (const auto& enemy : enemies) {
                if (enemy->isAlive()) enemyCount++;
            }

            if (allyCount == 0 || enemyCount == 0) {
                waveOver = true;
            } else {
                playerTurn();
                enemyTurn();
            }
        }

        if (allyCount == 0) {
            gameOverMenu(w);
            return;
        }
    }

    gameOverMenu(totalWaves, true);
}

void Game::spawnWaves(int wave_num) {
    std::cout << "Spawning wave " << wave_num << "..." << std::endl;
    switch (wave_num)
    {
    case 1:
        for (int i = 1; i <= totalWaves; i++) {
            enemies.push_back(std::make_unique<Goblin>(std::to_string(i)));
        }
        break;
    
    case 2:
        enemies.push_back(std::make_unique<Goblin>("1"));
        enemies.push_back(std::make_unique<GoblinSpearman>("2"));
        enemies.push_back(std::make_unique<GoblinArcher>("3"));
        enemies.push_back(std::make_unique<Goblin>("4"));
        break;
    
    case 3:
        enemies.push_back(std::make_unique<GoblinSpearman>("1"));
        enemies.push_back(std::make_unique<GoblinSpearman>("2"));
        enemies.push_back(std::make_unique<GoblinArcher>("3"));
        enemies.push_back(std::make_unique<GoblinArcher>("4"));
        break;
    
    case 4:
        enemies.push_back(std::make_unique<GoblinSpearman>("1"));
        enemies.push_back(std::make_unique<GoblinSpearman>("2"));
        enemies.push_back(std::make_unique<GoblinArcher>("3"));
        enemies.push_back(std::make_unique<GoblinChief>("4"));
        break;
    
    default:
        std::cout << "Error! Invalid wave number" << std::endl;
        break;
    }
}

void Game::playerTurn() {
    for(const auto& ally : party) {
        if (!ally->isAlive()) {
            continue;
        }

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
            showFightChoices();
            do {
                std::cout << ally->className() << " turn: ";
                getline(std::cin, choice);
            } while (choice != "1" && choice != "2" && choice != "3");

            if (choice == "1") {
                while (true) {
                    std::cout << "Choose enemy number to attack (or type back): ";
                    getline(std::cin, choice_atk);

                    if (choice_atk == "back") {
                        break;
                    }

                    if (choice_atk != "1" && choice_atk != "2" && choice_atk != "3" && choice_atk != "4") {
                        std::cout << "Invalid input. Choose 1, 2, 3, or 4." << std::endl;
                        continue;
                    }

                    int targetIdx = std::stoi(choice_atk) - 1;
                    if (!enemies[targetIdx]->isAlive()) {
                        std::cout << "That enemy is already defeated. Choose another target." << std::endl;
                        continue;
                    }

                    auto& target = enemies[targetIdx];
                    ally->attack(*target);
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
                    getline(std::cin, choice_skill);

                    if (choice_skill == "back") {
                        skill = nullptr;
                        break;
                    }

                    if (choice_skill != "1" && choice_skill != "2" && choice_skill != "3") {
                        std::cout << "Invalid input. Choose 1, 2, or 3." << std::endl;
                        continue;
                    }

                    slot = std::stoi(choice_skill) - 1;
                    skill = ally->getSkill(slot);
                    if (skill == nullptr) {
                        std::cout << "That skill slot is empty for this character." << std::endl;
                        continue;
                    }

                    if (!skill->isReady()) {
                        std::cout << "That skill is on cooldown." << std::endl;
                        continue;
                    }
                    break;
                }

                if (skill == nullptr) {
                    continue;
                }

                if (skill->getType() == "self_cast") {
                    ally->useAbility(slot, *ally);
                    waitForEnter();
                    actionTaken = true;
                } else if (skill->getType() == "single_cast_ally") {
                    showParty();
                    while (true) {
                        std::cout << "Choose ally number to target (or type back): ";
                        getline(std::cin, choice_atk);

                        if (choice_atk == "back") {
                            break;
                        }

                        if (choice_atk != "1" && choice_atk != "2" && choice_atk != "3" && choice_atk != "4") {
                            std::cout << "Invalid input. Choose 1, 2, 3, or 4." << std::endl;
                            continue;
                        }

                        int targetIdx = std::stoi(choice_atk) - 1;
                        if (!party[targetIdx]->isAlive()) {
                            std::cout << "That ally is down. Choose a living ally." << std::endl;
                            continue;
                        }

                        auto& target = party[targetIdx];
                        ally->useAbility(slot, *target);
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                } else if (skill->getType() == "single_cast_enemy") {
                    showEnemy();
                    while (true) {
                        std::cout << "Choose enemy number to target (or type back): ";
                        getline(std::cin, choice_atk);

                        if (choice_atk == "back") {
                            break;
                        }

                        if (choice_atk != "1" && choice_atk != "2" && choice_atk != "3" && choice_atk != "4") {
                            std::cout << "Invalid input. Choose 1, 2, 3, or 4." << std::endl;
                            continue;
                        }

                        int targetIdx = std::stoi(choice_atk) - 1;
                        if (!enemies[targetIdx]->isAlive()) {
                            std::cout << "That enemy is already defeated. Choose another target." << std::endl;
                            continue;
                        }

                        auto& target = enemies[targetIdx];
                        ally->useAbility(slot, *target);
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                }
            } else if (choice == "3") {
                if (inventory.empty()) {
                    std::cout << "No items in inventory." << std::endl;
                    continue;
                }
                while (true) {
                    showInventory();
                    std::cout << "Choose item number (or type back): ";
                    getline(std::cin, choice_item);
                    if (choice_item == "back") {
                        break;
                    }
                    int itemIdx = -1;
                    try {
                        itemIdx = std::stoi(choice_item) - 1;
                    } catch (...) {
                        std::cout << "Invalid input. Enter a number from the list." << std::endl;
                        continue;
                    }
                    if (itemIdx < 0 || static_cast<int>(itemIdx) >= inventory.size()) {
                        std::cout << "Invalid item choice." << std::endl;
                        continue;
                    }
                    Item* picked = inventory[static_cast<int>(itemIdx)].get();
                    if (picked->getUsable() <= 0) {
                        std::cout << "That item is out of uses." << std::endl;
                        continue;
                    }
                    showParty();
                    while (true) {
                        std::cout << "Choose ally number to use item on (or type back): ";
                        getline(std::cin, choice_atk);
                        if (choice_atk == "back") {
                            break;
                        }
                        if (choice_atk != "1" && choice_atk != "2" && choice_atk != "3" && choice_atk != "4") {
                            std::cout << "Invalid input. Choose 1, 2, 3, or 4." << std::endl;
                            continue;
                        }
                        int targetIdx = std::stoi(choice_atk) - 1;
                        if (!party[targetIdx]->isAlive()) {
                            std::cout << "That ally is down. Choose a living ally." << std::endl;
                            continue;
                        }
                        auto& target = party[targetIdx];
                        picked->useItem(*target);
                        picked->decrementUsable();
                        if (picked->getUsable() <= 0) {
                            inventory.erase(inventory.begin() + itemIdx);
                        }
                        waitForEnter();
                        actionTaken = true;
                        break;
                    }
                    if (actionTaken) {
                        break;
                    }
                }
            } else {
                std::cout << "Invalid input. Choose 1, 2, or 3." << std::endl;
                continue;
            }
        }
        ally->turnPassed();
    }
}

void Game::enemyTurn() {
    for (const auto& enemy : enemies) {
        if (!enemy->isAlive()) {
            continue;
        }

        bool allyAlive = false;
        for (const auto& ally : party) {
            if (ally->isAlive()) {
                allyAlive = true;
                break;
            }
        }
        if (!allyAlive) {
            break;
        }

        int target = -1;
        while (target < 0 || target > 3) {
            target = rand() % 4;
            if (!(party[target]->isAlive())) target = -1;
        }
        auto& ally = party[target];

        if (enemy->anyReadySkill()) {
            enemy->useAbility(rand() % 3, *ally);
        } else {
            enemy->attack(*ally);
        }
        waitForEnter();
    }
}

void Game::mainMenu() const {
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter(title) << "|" << std::endl;
    printDivider('=');
    std::cout << "|" << std::setfill(' ') << printCenter("A party of 4 adventurers was form, consisting of a Warrior,") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("Archer, Mage, and Priest. Your party has accepted a quest") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("to exterminate a nearby Goblin Camp. Command your party") << "|" << std::endl;
    std::cout << "|" << std::setfill(' ') << printCenter("through waves of enemies and seek victory!") << "|" << std::endl;
    printDivider('=');
    printThreeCols("1. Start Game", "2. Party Detail", "3. Quit Game");
    printDivider('='); 
}

void Game::fightMenu() const {
    printDivider('=');
    for (const auto& ally : party) {
        std::cout << "|" << std::setfill(' ') << printCenter(ally->showStatus()) << "|" << std::endl;
    }
    printDivider('-');
    for (const auto& enemy : enemies) {
        std::cout << "|" << std::setfill(' ') << printCenter(enemy->showStatus()) << "|" << std::endl;
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

void Game::gameOverMenu(int wave_num, bool finish) {
    if (finish) {
        printDivider('=');
        printThreeCols("VICTORY", ("REACHED WAVE: " + std::to_string(wave_num)), title);
        printDivider('=');
        printDivider(' ');
        std::cout << "|" << std::setfill(' ') << printCenter("Your party's might successfully conquered the Goblin's Den.") << "|" << std::endl;
        std::cout << "|" << std::setfill(' ') << printCenter("Having completed your quest, your party clains the reward.") << "|" << std::endl;
        printDivider(' ');
        printDivider('=');
        std::cout << "|" << std::setfill(' ') << std::left << std::setw((colWidth/2)) << "1. Play Again" << std::left << std::setw((colWidth/2)) << "2. Quit Game" << "|" << std::endl;
        printDivider('=');  
    } else {
        printDivider('=');
        printThreeCols("GAME OVER", ("REACHED WAVE: " + std::to_string(wave_num)), title);
        printDivider('=');
        printDivider(' ');
        std::cout << "|" << std::setfill(' ') << printCenter("Your party has fought with all their might but, the enemy") << "|" << std::endl;
        std::cout << "|" << std::setfill(' ') << printCenter("forces were just too strong. Faced with defeat you ran.") << "|" << std::endl;
        printDivider(' ');
        printDivider('=');
        std::cout << "|" << std::setfill(' ') << std::left << std::setw((colWidth/2)) << "1. Retry Game" << std::left << std::setw((colWidth/2)) << "2. Quit Game" << "|" << std::endl;
        printDivider('='); 
    }
}

void Game::showParty() const {
    printDivider('=');
    for (const auto& ally : party) {
        std::cout << "|" << std::setfill(' ') << printCenter(ally->showStatus()) << "|" << std::endl;
    }
    printDivider('=');
}

void Game::showEnemy() const {
    printDivider('=');
    for (const auto& enemy : enemies) {
        std::cout << "|" << std::setfill(' ') << printCenter(enemy->showStatus()) << "|" << std::endl;
    }
    printDivider('=');
}

void Game::showFightChoices() const {
    printDivider('-');
    printThreeCols("1. Attack", "2. Cast Skill", "3. Use Item");
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
        std::cout << "|" << std::setfill(' ') << std::left << std::setw(colWidth)
                  << (std::to_string(i) + ". " + item->getName() + " x" + std::to_string(item->getUsable()))
                  << "|" << std::endl;
        i++;
    }
    printDivider('-');
}
