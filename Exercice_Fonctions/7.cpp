#include <iostream>

int fib(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}
int main (){
    std::cout << "fib(7): " << fib(7) << std::endl; // Affiche 13
    std::cout << "fib(11): " << fib(11) << std::endl; // Affiche 89

    return 0;
}