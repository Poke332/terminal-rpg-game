#pragma once

#include "Enemy.h"

class AncientDragon : public Enemy {
public:
    enum class Element { INFERNO, FROST, STORM, SHADOW, PRIMORDIAL };

    AncientDragon(Element elem, const std::string& latinName);
    std::string className() const override;
    void useAbility(int slot, Character& target) override;

    static const char* randomLatinName();
    static const char* elementName(Element elem);
private:
    Element element_;
    std::string latinName_;
    std::string displayName_;
};
