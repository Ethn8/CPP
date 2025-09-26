#include <iostream>

int distance(int a, int b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}

int main()
{
    std::cout << "distance(25, 42): " << distance(25, 42) << std::endl; // Affiche 17

    std::cout << "distance(42, 25): " << distance(42, 25) << std::endl; // Affiche également 17
    return 0;
}