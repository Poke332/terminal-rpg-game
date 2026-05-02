#pragma once

#include <string>

extern int colWidth;
extern std::string title;

std::string printCenter(const std::string& text);
void printDivider(char divider);
void printThreeCols(const std::string& s1, const std::string& s2, const std::string& s3);
void waitForEnter();
