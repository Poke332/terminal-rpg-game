#pragma once

#include <vector>
#include <string>
#include <memory>
#include <random>
#include "Character.h"
#include "items/Item.h"

class Game {
    std::vector<std::unique_ptr<Character>> party;
    std::vector<std::unique_ptr<Character>> enemies;
    std::vector<std::unique_ptr<Item>> inventory;

    int currentFloor = 1;
    bool surrendered_ = false;
    std::mt19937 rng;

public:
    Game();
    void runGame();
    void partyBuildMenu();

    void playerTurn();
    void enemyTurn();
    void generateFloor(int floorNumber);
    void generateBossStage(int floorNumber);
    void promoteToElite(Character& enemy);
    void assignEliteSkills(Character& enemy);
    void awardFloorReward();
    void clearPartyStatusEffects();
    void checkEvolutions();

    void mainMenu() const;
    void fightMenu() const;
    void characterDetailMenu() const;
    void gameOverMenu(int floor_num);
    void inspectCharacter(const Character& c) const;

    void showParty() const;
    void showEnemy() const;
    void showFightChoices(const Character& ally) const;
    void showSkillChoices(const Character& ally) const;
    void showInventory();
};