#pragma once

#include <string>

extern int colWidth;
extern std::string title;

namespace Color {
    extern const std::string RESET;
    extern const std::string RED;
    extern const std::string GREEN;
    extern const std::string YELLOW;
    extern const std::string CYAN;
    extern const std::string MAGENTA;
    extern const std::string WHITE_BOLD;
}

std::string colorize(const std::string& text, const std::string& color);
void printColored(const std::string& text, const std::string& color);
std::string hpBar(float current, float max, int width = 15);

int visibleLength(const std::string& s);
std::string padToWidth(const std::string& text, int width);
void printBoxedLine(const std::string& line);

namespace EnemyLevel {
    constexpr float GROWTH_PER_LEVEL = 0.10f;
    constexpr int BOSS_LEVEL_BONUS = 5;
}

int getEnemyLevelForFloor(int floorNumber);
int getBossLevelForFloor(int floorNumber);

std::string getFloorLayer(int floorNum);
std::string getDynamicFloorName(int floorNum);
std::string getFullFloorLabel(int floorNum, bool isBoss = false);

std::string printCenter(const std::string& text);
void printDivider(char divider);
void printThreeCols(const std::string& s1, const std::string& s2, const std::string& s3);
void waitForEnter();
