#include "../include/Game.h"
#include <iostream>
#include <string>

int main() {
    Game g;
    std::string c;
    while(true) {
        g.mainMenu();
        do {
            std::cout << "Your choice: ";
            getline(std::cin, c);
        } while (c != "1" && c != "2" && c != "3");

        if (c == "1") {
            g.runGame();
            break;
        } else if (c == "2") {
            g.characterDetailMenu();
        } else {
            std::cout << "Quitting game..." << std::endl;
            break;
        }
    }
}