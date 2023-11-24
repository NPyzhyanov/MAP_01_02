#include <vector>
#include <iostream>
#include <mutex>

#include "sum_function.h"
#include "find_cores.h"

extern std::once_flag flag;

void sum_function(std::vector<double>::iterator begin_1, std::vector<double>::iterator end_1, std::vector<double>::iterator begin_2, 
                  std::vector<double>::iterator end_2, std::vector<double>::iterator begin_3, std::vector<double>::iterator end_3, unsigned int* p_cores)
{
    std::call_once(flag, find_cores, p_cores);
    
    auto it_1 = begin_1;
    auto it_2 = begin_2;
    for (auto it_3 = begin_3; it_3 != end_3; it_3++)
    {
        if (it_1 > end_1 || it_2 > end_2)
        {
            std::cerr << "Incorrect length of input vector!\n";
            break;
        }
        
        *it_3 = *it_2 + *it_1;
        
        it_1++;
        it_2++;
    }
}
