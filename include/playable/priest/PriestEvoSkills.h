#pragma once
#include "Skill.h"

class MassHeal : public Skill {
public:
    MassHeal();
    void skillImplementation(Character& user, Character& target) override;
};

class HolyWrath : public Skill {
public:
    HolyWrath();
    void skillImplementation(Character& user, Character& target) override;
};

class DivineFavor : public Skill {
public:
    DivineFavor();
    void skillImplementation(Character& user, Character& target) override;
};

class SanctuaryHeal : public Skill {
public:
    SanctuaryHeal();
    void skillImplementation(Character& user, Character& target) override;
};

class Judgment : public Skill {
public:
    Judgment();
    void skillImplementation(Character& user, Character& target) override;
};

class HolyCovenant : public Skill {
public:
    HolyCovenant();
    void skillImplementation(Character& user, Character& target) override;
};

class DivineIntervention : public Skill {
public:
    DivineIntervention();
    void skillImplementation(Character& user, Character& target) override;
};
