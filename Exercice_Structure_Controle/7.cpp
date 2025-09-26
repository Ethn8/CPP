#include <iostream>

int main() {

    int tab[5];
    for (int i = 0; i < 5; i++) {
        tab[i] = i * i;
    }
    for (int i = 0; i < 5; i++) {
        std::cout << tab[i] << " " << std::endl;
    }
    return 0;
}