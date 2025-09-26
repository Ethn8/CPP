#include <iostream>
#include <windows.h>


int main() {

    SetConsoleOutputCP(CP_UTF8); // Pour afficher les accents correctement

    int annee;

    std::cout << "Quelles années est bissextile ?" << std::endl;
    std::cout << "choisissez votre année : " << std::endl;
    std::cin >> annee;

    // Vérifie si l'année saisie est bissextile
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        std::cout << annee << " est une année bissextile." << std::endl;
    } else {
        std::cout << annee << " n'est pas une année bissextile." << std::endl;
    }

    for (annee = 2000; annee <= 2021; annee++) {
        if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
            std::cout << annee << " est une année bissextile." << std::endl;
        } else {
            std::cout << annee << " n'est pas une année bissextile." << std::endl;
        }
    }

    return 0;
}