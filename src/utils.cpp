#include "../include/utils.h"

#include <iostream>
#include <iomanip>
#include <cmath>

int colWidth = 72;
std::string title = "DUNGEON CRAWLER";

namespace Color {
    const std::string RESET       = "\033[0m";
    const std::string RED         = "\033[31m";
    const std::string GREEN       = "\033[32m";
    const std::string YELLOW      = "\033[33m";
    const std::string CYAN        = "\033[36m";
    const std::string MAGENTA     = "\033[35m";
    const std::string WHITE_BOLD  = "\033[1;37m";
}

std::string colorize(const std::string& text, const std::string& color) {
    return color + text + Color::RESET;
}

void printColored(const std::string& text, const std::string& color) {
    std::cout << color << text << Color::RESET << std::endl;
}

int visibleLength(const std::string& s) {
    int len = 0;
    bool inEscape = false;
    size_t i = 0;
    while (i < s.size()) {
        unsigned char c = s[i];
        if (c == '\033') {
            inEscape = true;
            i++;
            continue;
        }
        if (inEscape) {
            if (c == 'm') inEscape = false;
            i++;
            continue;
        }
        if (c < 0x80) { len++; i++; }
        else if ((c & 0xE0) == 0xC0) { len++; i += 2; }
        else if ((c & 0xF0) == 0xE0) { len++; i += 3; }
        else if ((c & 0xF8) == 0xF0) { len++; i += 4; }
        else { len++; i++; }
    }
    return len;
}

std::string padToWidth(const std::string& text, int width) {
    int vis = visibleLength(text);
    int pad = std::max(0, width - vis);
    return text + std::string(pad, ' ');
}

void printBoxedLine(const std::string& line) {
    std::cout << "| " << padToWidth(line, colWidth - 2) << " |" << std::endl;
}

int getEnemyLevelForFloor(int floorNumber) {
    static const int levelRanges[7][2] = {
        {1, 5}, {5, 10}, {10, 16}, {16, 23}, {23, 31}, {31, 42}, {42, 0}
    };
    int layerIdx = std::min(6, (floorNumber - 1) / 10);
    int minLevel = levelRanges[layerIdx][0];
    int maxLevel = levelRanges[layerIdx][1];
    if (layerIdx < 6) {
        int floorInLayer = (floorNumber - 1) % 10;
        return minLevel + (floorInLayer * (maxLevel - minLevel) + 5) / 10;
    } else {
        return 42 + (floorNumber - 61) / 2;
    }
}

int getBossLevelForFloor(int floorNumber) {
    return getEnemyLevelForFloor(floorNumber) + EnemyLevel::BOSS_LEVEL_BONUS;
}

std::string getFloorLayer(int floorNum) {
    struct LayerDef { const char* name; const std::string* color; };
    LayerDef layers[] = {
        {"Lower Levels",    &Color::WHITE_BOLD},
        {"Entrance Level",  &Color::GREEN},
        {"Mushroom Depths", &Color::YELLOW},
        {"Crystal Caverns", &Color::CYAN},
        {"Magma Core",      &Color::RED},
        {"Abyssal Void",    &Color::MAGENTA},
        {"The Beyond",      &Color::WHITE_BOLD}
    };
    int idx = 0;
    if (floorNum > 1) {
        idx = std::min(6, (floorNum - 1) / 10);
    }
    return colorize(layers[idx].name, *layers[idx].color);
}

std::string getDynamicFloorName(int floorNum) {
    static const char* names[] = {
        "The Descent Begins",
        "Dim-lit Corridors",
        "Echoing Chambers",
        "Rusty Gateways",
        "Flickering Passages",
        "Gloomy Halls",
        "Moss-covered Floors",
        "Dripping Tunnels",
        "Slime Trails",
        "Broken Staircase",
        "Creaking Doors",
        "Forgotten Library",
        "Collapsed Passage",
        "Spider-webbed Corners",
        "Crumbling Walls",
        "Fungal Overgrowth",
        "Root-Infested Path",
        "Underground Stream",
        "Earthen Chambers",
        "Sacrificial Altars",
        "Bone-littered Floor",
        "Torch-lit Corridor",
        "Ancient Barracks",
        "Armory Ruins",
        "Training Grounds",
        "Watchtower Base",
        "Supply Cache",
        "Cramped Tunnels",
        "Expanding Caverns",
        "The Great Hall",
        "Gem-studded Walls",
        "Crystal Formations",
        "Reflecting Pools",
        "Geode Chambers",
        "Iridescent Passages",
        "Light-bending Halls",
        "Prismatic Corridors",
        "Glowing Depths",
        "Crystalline Labyrinth",
        "The Crystal Throne",
        "Warm Vents",
        "Smoldering Floor",
        "Ash-covered Path",
        "Ember-lit Corridor",
        "Blazing Gate",
        "Lava Tubes",
        "Obsidian Halls",
        "Sulfur Pits",
        "Burning Chambers",
        "Inferno Heart",
        "Dark Crevices",
        "Shadowy Depths",
        "Whispering Void",
        "Eternal Darkness",
        "Silent Abyss",
        "Void-touched Halls",
        "Null Space",
        "Echoes of Nothing",
        "The Event Horizon",
        "The Endless Pit"
    };
    static const int nameCount = sizeof(names) / sizeof(names[0]);
    int idx = (floorNum - 1) % nameCount;
    int cycle = (floorNum - 1) / nameCount;
    std::string result = names[idx];
    if (cycle > 0) {
        result += " (Depth " + std::to_string(cycle + 1) + ")";
    }
    return result;
}

std::string getFullFloorLabel(int floorNum, bool isBoss) {
    std::string prefix = isBoss ? "[BOSS] " : "";
    return prefix + "Floor " + std::to_string(floorNum) + " - "
           + getDynamicFloorName(floorNum) + " - "
           + getFloorLayer(floorNum);
}

std::string hpBar(float current, float max, int width) {
    if (max <= 0) max = 1;
    if (current < 0) current = 0;
    float ratio = current / max;
    int filled = static_cast<int>(std::round(ratio * width));

    const std::string* color;
    if (ratio > 0.6f) color = &Color::GREEN;
    else if (ratio > 0.3f) color = &Color::YELLOW;
    else color = &Color::RED;

    std::string bar = "[";
    for (int i = 0; i < width; i++) {
        if (i < filled) bar += "\u2588";
        else bar += "\u2591";
    }
    bar += "]";

    return *color + bar + Color::RESET;
}

std::string printCenter(const std::string& text) {
    int visLen = visibleLength(text);
    int padding = colWidth - visLen;
    int left_padding = padding/2;
    int right_padding = padding - left_padding;
    return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}

void printDivider(char divider) {
    std::cout << "|" << std::setfill(divider) << std::setw(colWidth) << "" << "|" << std::endl;
}

void printThreeCols(const std::string& s1, const std::string& s2, const std::string& s3) {
    int first_col = colWidth/3;
    int second_col = first_col;
    int third_col = colWidth - first_col - second_col;
    std::cout << "|"
            << padToWidth(s1, first_col)
            << padToWidth(s2, second_col)
            << padToWidth(s3, third_col)
            << "|" << std::endl;
}

void waitForEnter() {
    std::string _;
    std::cout << "Press Enter to continue...";
    if (!getline(std::cin, _)) {
        std::cout << std::endl;
        return;
    }
}
