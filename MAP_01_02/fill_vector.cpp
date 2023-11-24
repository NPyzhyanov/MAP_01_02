#include <vector>
#include <random>

#include "fill_vector.h"

void fill_vector(std::vector<double>* p_vector)
{
    const double max_abs_value = 1000.0;
    
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist(-max_abs_value, max_abs_value);
    
    for (auto it = p_vector->begin(); it != p_vector->end(); it++)
    {
        *it = dist(gen);
    }
}
