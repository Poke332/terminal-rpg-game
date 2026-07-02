#pragma once
#include "Skill.h"

class FortressStance : public Skill {
public:
    FortressStance();
    void skillImplementation(Character& user, Character& target) override;
};

class BattleCry : public Skill {
public:
    BattleCry();
    void skillImplementation(Character& user, Character& target) override;
};

class PowerBash : public Skill {
public:
    PowerBash();
    void skillImplementation(Character& user, Character& target) override;
};

class Bulwark : public Skill {
public:
    Bulwark();
    void skillImplementation(Character& user, Character& target) override;
};

class WarDrums : public Skill {
public:
    WarDrums();
    void skillImplementation(Character& user, Character& target) override;
};

class CrushingBlow : public Skill {
public:
    CrushingBlow();
    void skillImplementation(Character& user, Character& target) override;
};

class TitansStrike : public Skill {
public:
    TitansStrike();
    void skillImplementation(Character& user, Character& target) override;
};
