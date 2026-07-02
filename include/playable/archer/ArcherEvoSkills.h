#pragma once
#include "Skill.h"

class DeadlyShot : public Skill {
public:
    DeadlyShot();
    void skillImplementation(Character& user, Character& target) override;
};

class ArrowStorm : public Skill {
public:
    ArrowStorm();
    void skillImplementation(Character& user, Character& target) override;
};

class SwiftVolley : public Skill {
public:
    SwiftVolley();
    void skillImplementation(Character& user, Character& target) override;
};

class ExecutionersShot : public Skill {
public:
    ExecutionersShot();
    void skillImplementation(Character& user, Character& target) override;
};

class TempestVolley : public Skill {
public:
    TempestVolley();
    void skillImplementation(Character& user, Character& target) override;
};

class RapidFire : public Skill {
public:
    RapidFire();
    void skillImplementation(Character& user, Character& target) override;
};

class PerfectShot : public Skill {
public:
    PerfectShot();
    void skillImplementation(Character& user, Character& target) override;
};
