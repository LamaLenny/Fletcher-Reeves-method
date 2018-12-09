#pragma once
#include <random>

//!Generator of uniform on(0, 1) distribution
class Generator
{
public:
    static std::mt19937 mt;
public:
    static std::mt19937& get_mt();
};

double get_01();


