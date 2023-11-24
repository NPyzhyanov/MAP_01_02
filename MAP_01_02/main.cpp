#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <mutex>

#include "fill_vector.h"
#include "sum_function.h"

std::once_flag flag;

int main()
{
    std::cout << "Threads: 1\t\t2\t\t4\t\t8\t\t16\n|Size|\n";
    
    unsigned int physical_cores_amount = 0;
        
    for (double v_power = 3.0; v_power <= 6.0; v_power++)
    {
        const int vector_size = static_cast<int>(pow(10.0, v_power));
        
        std::cout << "|10^" << v_power << "|";
        
        std::vector<double> vector_1(vector_size);
        std::vector<double> vector_2(vector_size);
        std::vector<double> vector_3_first(vector_size);
        
        fill_vector(&vector_1);
        fill_vector(&vector_2);
        
        for (double th_power = 0.0; th_power <= 4.0; th_power++)
        {
            const int threads_amount = static_cast<int>(pow(2.0, th_power));
            const int elems_per_thread = vector_size / threads_amount;
            
            std::vector<double> vector_3(vector_size);
            
            std::vector<std::vector<double>::iterator> marks_1(threads_amount + 1);
            std::vector<std::vector<double>::iterator> marks_2(threads_amount + 1);
            std::vector<std::vector<double>::iterator> marks_3(threads_amount + 1);
            
            *(marks_1.end() - 1) = vector_1.end();
            *(marks_2.end() - 1) = vector_2.end();
            *(marks_3.end() - 1) = vector_3.end();
            
            for (int th = 0; th < threads_amount; th++)
            {
                marks_1.at(th) = vector_1.begin() + th * elems_per_thread;
                marks_2.at(th) = vector_2.begin() + th * elems_per_thread;
                marks_3.at(th) = vector_3.begin() + th * elems_per_thread;
            }
            
            auto start = std::chrono::steady_clock::now(); // <-- Start recording
            
            std::vector<std::thread> Threads;
            
            for (int th = 0; th < threads_amount; th++)
            {
                Threads.push_back(std::thread(sum_function, marks_1.at(th), marks_1.at(th + 1), marks_2.at(th), marks_2.at(th + 1), marks_3.at(th), marks_3.at(th + 1), &physical_cores_amount));
            }
            
            for (auto& el : Threads)
            {
                el.join();
            }
            
            auto end = std::chrono::steady_clock::now(); // <-- Finish recording
            
            auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "\t" << diff.count() / 1000.0 << " ms ";
            
            if (threads_amount == 1)
            {
                vector_3_first = std::move(vector_3);
            }
            else
            {
                if (!std::equal(vector_3.begin(), vector_3.end(), vector_3_first.begin()))
                {
                    std::cerr << "Results are not equals!" << std::endl;
                }
            }
        }
        
        std::cout << std::endl;
    }
    
    std::cout <<"\nPhysical cores: " << physical_cores_amount << std::endl;
    
    return 0;
}
