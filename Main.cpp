#include <iostream>
#include <cstdlib>
#include <chrono>

#include "JugsManager.h"

bool isValidInput(size_t L, size_t S, size_t W, size_t method)
{
    return L > 0 && S > 0 && W > 0 && W <= L && L > S && (method == 1 || method == 2);
}

int main()
{
    size_t L, S, W, method, showTime;
    std::cin >> L >> S >> W >> method >> showTime;

    if (!isValidInput(L, S, W, method))
    {
        std::cerr << "invalid input" << std::endl;
        exit(1);
    }

    JugsManager manager(L, S, W);

    if (method == 1)
    {
        // TODO: check only zero or 1
        if (showTime)
        {
            auto start = std::chrono::high_resolution_clock::now();
            manager.SolveWithGraph();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Function took " << duration.count() << " microseconds." << std::endl;
        }
        else
        {
            manager.SolveWithGraph();
        }
    }
    else
    {
        if (showTime)
        {
            auto start = std::chrono::high_resolution_clock::now();
            manager.SolveWithHashTable();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Function took " << duration.count() << " microseconds." << std::endl;
        }
        else
        {
            manager.SolveWithHashTable();
        }
    }

    return 0;
}
