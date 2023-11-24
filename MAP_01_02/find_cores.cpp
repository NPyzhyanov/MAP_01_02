#include <thread>

#include "find_cores.h"

void find_cores(unsigned int* p_cores)
{
    *p_cores = std::thread::hardware_concurrency();
}
