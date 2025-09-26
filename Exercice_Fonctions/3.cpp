#include <iostream>

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    std::cout << "max(42,66): " << max(42,66) << std::endl; // Affiche 66
    std::cout << "min(42,66): " << min(42,66) << std::endl; // Affiche 42
    return 0;
}