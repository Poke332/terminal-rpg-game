#include "../include/utils.h"

#include <iostream>
#include <iomanip>

int colWidth = 72;
std::string title = "DUNGEON CRAWLER";

std::string printCenter(const std::string& text) {
    int len = text.length();
    int padding = colWidth - len;
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
    std::cout << "|" << std::setfill(' ')
            << std::left << std::setw(first_col) << s1
            << std::left << std::setw(second_col) << s2
            << std::left << std::setw(third_col) << s3
            << "|" << std::endl;
}

void waitForEnter() {
    std::string _;
    std::cout << "Press Enter to continue...";
    getline(std::cin, _);
}
