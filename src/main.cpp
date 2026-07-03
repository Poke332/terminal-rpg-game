#include "../include/Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));

    Game g;
    std::string c;
    while (true) {
        g.mainMenu();
        do {
            std::cout << "Your choice: ";
            if (!getline(std::cin, c)) return 0;
        } while (c != "1" && c != "2" && c != "3" && c != "4");

        if (c == "1") {
            g.partyBuildMenu();
            g.runGame();

            std::string retry;
            do {
                std::cout << "Your choice: ";
                if (!getline(std::cin, retry)) return 0;
            } while (retry != "1" && retry != "2");

            if (retry == "1") {
                Game newGame;
                g = std::move(newGame);
                continue;
            }
            break;
        } else if (c == "2") {
            g.characterDetailMenu();
        } else if (c == "3") {
            g.debugMenu();

            std::string retry;
            do {
                std::cout << "Your choice: ";
                if (!getline(std::cin, retry)) return 0;
            } while (retry != "1" && retry != "2");

            if (retry == "1") {
                Game newGame;
                g = std::move(newGame);
                continue;
            }
            break;
        } else {
            std::cout << "Quitting game..." << std::endl;
            break;
        }
    }
}
