#pragma once
# include <vector>
#include <string>

struct snake_segment_st
{
    int x = 0;
    int y = 0;
    int colour = 0;
    std::string name;
};


// Fonctions du snake
std::vector<snake_segment_st> snake_init (int size_snake);
