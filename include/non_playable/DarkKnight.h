#pragma once
#include "Enemy.h"

class DarkKnight : public Enemy {
public:
    DarkKnight(const std::string& n);
    std::string className() const override;
};
