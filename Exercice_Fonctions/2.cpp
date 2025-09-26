#include <iostream>

int addition(int a, int b)
{
    return a + b;
}
int main()
{
    std::cout << "42+9: " << addition(42,9) << std::endl; // Affiche 51
}