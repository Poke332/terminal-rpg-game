#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Character.h"

class Game {
    std::vector<std::unique_ptr<Character>> party;
    std::vector<std::unique_ptr<Character>> enemies;
    std::map<std::string, int> inventory;

    int totalWaves = 4;
public:
    Game();
    void runGame();

    void playerTurn();
    void enemyTurn();
    void spawnWaves(int wave_num);

    void mainMenu() const;
    void fightMenu() const;
    void characterDetailMenu() const;
    void gameOverMenu(int wave_num, bool finish = false);

    void showParty() const;
    void showEnemy() const;
    void showFightChoices() const;
    void showSkillChoices(const Character& ally) const;
};