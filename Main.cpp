#include <iostream>
#include <cstdlib>
#include <chrono>

#include "JugsManager.h"

// ======================== USE INSTRUCTIONS ===========================
// INPUT FORMAT (all values separated by spaces or newlines):
//   <L> <S> <W> <method> <showTime> (<> are part of notation, not actual input)
//   - L: Capacity of the large jug (integer > 0)
//   - S: Capacity of the small jug (integer > 0, and L > S)
//   - W: Desired amount of water in the large jug (integer > 0, and W <= L)
//   * Note: the program finds the state: W in large jug, small jug empty
// 
//   - method: 1 for Graph-based solution, 2 for Hash Table-based solution
//   - showTime: 1 to display execution time, 0 to hide it
//
// OUTPUT:
//   - If a solution exists, prints the number of operations and the sequence of steps.
//   - If no solution exists, prints "No solution."
//   - If showTime is 1, prints the function execution time in microseconds.
//
// NOTES:
//   - All input values must be integers. Non-numeric input will result in an error.
//   - L must be greater than S, and W must be less than or equal to L.
//   - Only method 1 (graph) and method 2 (hash table) are supported.
//
// =====================================================================


bool isValidInput(int L, int S, int W, int method, int showTime)
{
    return L > 0 && S > 0 && W > 0 && W <= L && L > S
        && (method == 1 || method == 2)
        && (showTime == 0 || showTime == 1);
}

int main()
{
    int L, S, W, method, showTime;
    std::cin >> L >> S >> W >> method >> showTime;

    // check failed input
    if (std::cin.fail()) 
    {
        std::cerr << "invalid input (not a number)" << std::endl;
        exit(1);
    }
    // validate input
    if (!isValidInput(L, S, W, method, showTime))
    {
        std::cerr << "invalid input" << std::endl;
        exit(1);
    }

    JugsManager manager((size_t)L, (size_t)S, (size_t)W);

    if (method == 1)
    {
        if (showTime)
        {
            auto start = std::chrono::high_resolution_clock::now();
            manager.SolveWithGraph();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Function took " << duration.count() << " microseconds." << std::endl;
        }
        else
            manager.SolveWithGraph();
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
            manager.SolveWithHashTable();
    }

    return 0;
}
