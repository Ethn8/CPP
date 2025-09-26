#include <iostream>

int main() {
    int tab[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tab[i][j] = (i+j) % 2;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << tab[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
