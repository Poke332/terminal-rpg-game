#pragma once
#include "Skill.h"

class Inferno : public Skill {
public:
    Inferno();
    void skillImplementation(Character& user, Character& target) override;
};

class ArcaneBarrage : public Skill {
public:
    ArcaneBarrage();
    void skillImplementation(Character& user, Character& target) override;
};

class GlacierNova : public Skill {
public:
    GlacierNova();
    void skillImplementation(Character& user, Character& target) override;
};

class Hellfire : public Skill {
public:
    Hellfire();
    void skillImplementation(Character& user, Character& target) override;
};

class ArcaneCataclysm : public Skill {
public:
    ArcaneCataclysm();
    void skillImplementation(Character& user, Character& target) override;
};

class AbsoluteZero : public Skill {
public:
    AbsoluteZero();
    void skillImplementation(Character& user, Character& target) override;
};

class ArcaneAnnihilation : public Skill {
public:
    ArcaneAnnihilation();
    void skillImplementation(Character& user, Character& target) override;
};
