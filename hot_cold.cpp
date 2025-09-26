#include <iomanip> // pour std::setprecision
#include <iostream>
#include <cstdlib> // pour la fonction rand() et srand()
#include <ctime>   // pour la fonction time()

struct AiData
{
    bool useIA = false;   // true si on utilise l'IA
    int minValue = 1;     // valeur minimale possible
    int maxValueIA = 100; // valeur maximale possible
    int levelIA = 5;      // niveau d'intelligence de l'IA (0 à 10)
};

int CompareAndDisplay(int guess, int valueToFind)
{
    // Compare la proposition avec la valeur à trouver et affiche le résultat
    if (guess < valueToFind)
    {
        std::cout << "Plus" << std::endl;
        return 1; // La valeur à trouver est plus grande
    }
    else if (guess > valueToFind)
    {
        std::cout << "Minus" << std::endl;
        return -1; // La valeur à trouver est plus petite
    }
    else
    {
        return 0; // Trouvé
    }
}

int IA_Guess(AiData ai, int min, int max)
{
    // Cette fonction génère une proposition IA selon son niveau
    int range = max - min;
    float intervalSize = range * (1.0f - ai.levelIA / 10.0f); // Taille de l'intervalle
    int interval = static_cast<int>(intervalSize);
    int center = (min + max) / 2; // Centre de l'intervalle
    int intervalMin = center - interval / 2;
    int intervalMax = center + interval / 2;
    // Ajuster si intervalle dépasse les bornes
    if (intervalMin < min)
        intervalMin = min;
    if (intervalMax > max)
        intervalMax = max;
    // Si le nombre de valeurs est pair, élargir l'intervalle à droite
    if ((intervalMax - intervalMin + 1) % 2 == 0 && intervalMax < max)
        intervalMax++;
    int intervalLength = intervalMax - intervalMin + 1;
    // Correction : si l'intervalle est nul ou négatif, retourner le centre
    if (intervalLength <= 0)
    {
        return center;
    }
    // Choisir aléatoirement dans l'intervalle
    int guess = intervalMin + rand() % intervalLength;
    return guess;
}

int AI_UpdateBounds(int result, int guess, int &min, int &max)
{
    // Met à jour les bornes min et max selon le résultat de la comparaison
    if (result == 1)
    { // "Plus" - le nombre à trouver est plus grand
        min = guess + 1;
    }
    else if (result == -1)
    { // "Minus" - le nombre à trouver est plus petit
        max = guess - 1;
    }
    return 0;
}

// Fonction statistique : fait jouer l'IA nbParties fois pour différents niveaux et affiche la moyenne de coups
// Cette fonction permet de comparer l'efficacité de l'IA selon son niveau
void statistiquesIA(int maxValue, int nbParties)
{
    int niveaux[] = {0, 5, 10}; // Niveaux d'IA à tester
    int nbNiveaux = sizeof(niveaux) / sizeof(niveaux[0]);
    srand(time(0)); // Initialisation du générateur aléatoire
    std::cout << "\n--- Statistiques IA sur " << nbParties << " parties (maxValue=" << maxValue << ") ---\n";
    for (int i = 0; i < nbNiveaux; ++i)
    {
        int totalAttempts = 0;  // Compteur total d'essais pour ce niveau
        int level = niveaux[i]; // Niveau d'IA courant
        for (int partie = 0; partie < nbParties; ++partie)
        {
            AiData ai;
            ai.useIA = true;                           // On utilise l'IA
            ai.levelIA = level;                        // Niveau d'IA
            ai.minValue = 1;                           // Borne minimale
            ai.maxValueIA = maxValue;                  // Borne maximale
            int valueToFind = rand() % (maxValue + 1); // Nombre à deviner
            int min = ai.minValue;
            int max = ai.maxValueIA;
            int attempts = 0; // Compteur d'essais pour cette partie
            int guess, gameStatus;
            // Boucle de jeu IA jusqu'à trouver le nombre
            do
            {
                attempts++;
                guess = IA_Guess(ai, min, max); // Proposition IA
                gameStatus = 0;
                if (guess < valueToFind)
                    gameStatus = 1;
                else if (guess > valueToFind)
                    gameStatus = -1;
                AI_UpdateBounds(gameStatus, guess, min, max); // Mise à jour des bornes
            } while (gameStatus != 0);
            totalAttempts += attempts; // Ajout au total
        }
        float moyenne = (float)totalAttempts / nbParties; // Calcul de la moyenne
        std::cout << "Niveau IA " << level << " : Moyenne de coups = " << std::setprecision(3) << moyenne << std::endl;
    }
    std::cout << "---------------------------------------------------\n";
}

int main()
{
    // Appel de la fonction statistique pour afficher les performances de l'IA
    statistiquesIA(100, 100);

    // --- Jeu classique interactif ---
    AiData ai;        // structure de l'IA
    int maxValue;     // valeur max définie par le joueur
    int valueToFind;  // valeur à trouver
    int guess;        // proposition
    int attempts = 0; // nombre d'essais
    int gameStatus;   // variable pour stocker la valeur de retour de la fonction
    char response;

    // 1. Demander à l'utilisateur de choisir une valeur maximale
    std::cout << "Bienvenue dans le jeu du Plus-Moins !" << std::endl;
    std::cout << "Choisissez une valeur maximale pour le nombre a deviner : ";
    std::cin >> maxValue;

    // 2. Initialiser le générateur de nombres aléatoires
    // Le time(0) assure que le nombre est différent à chaque exécution
    srand(time(0));

    // 3. Générer le nombre secret aléatoire
    // garantit que le nombre est entre 0 et maxValue inclus
    valueToFind = rand() % (maxValue + 1);

    std::cout << "Le nombre a deviner a ete choisi." << std::endl;

    // 4. Demander si l'utilisateur veut utiliser l'IA
    std::cout << "Voulez-vous utiliser une IA ? (y/n) : ";
    std::cin.ignore(); // Ignorer le \n restant du cin précédent
    ai.useIA = (std::cin.get() == 'y');

    // Initialiser les bornes pour l'IA
    ai.maxValueIA = maxValue;

    if (ai.useIA)
    {
        std::cout << "Choisissez le niveau d'IA entre 0 et 10 : ";
        std::cin >> ai.levelIA;
        if (ai.levelIA < 0)
            ai.levelIA = 0;
        if (ai.levelIA > 10)
            ai.levelIA = 10;
        std::cout << "L'IA va jouer au niveau " << ai.levelIA << " !" << std::endl;

        // Boucle de jeu IA
        do
        {
            attempts++;
            // L'IA propose une valeur selon son niveau
            guess = IA_Guess(ai, ai.minValue, ai.maxValueIA);
            std::cout << "Essai " << attempts << " - L'IA propose : " << guess << std::endl;

            // Appel de la fonction pour comparer
            gameStatus = CompareAndDisplay(guess, valueToFind);

            // Mettre à jour les bornes selon le résultat
            AI_UpdateBounds(gameStatus, guess, ai.minValue, ai.maxValueIA);

        } while (gameStatus != 0); // La boucle continue tant que le nombre n'est pas trouvé

        std::cout << "Bravo ! L'IA a trouve le nombre " << valueToFind << " en " << attempts << " essais." << std::endl;
    }
    else
    { // non utilisation de l'IA
        std::cout << "C'est a vous de jouer !" << std::endl;
        // Boucle de jeu joueur
        do
        {
            attempts++;
            std::cout << "Essai " << attempts << " - Entrez votre proposition : ";
            std::cin >> guess;

            // Appel de la fonction
            gameStatus = CompareAndDisplay(guess, valueToFind);

        } while (gameStatus != 0); // La boucle continue tant que le nombre n'est pas trouvé

        std::cout << "Bravo ! Vous avez trouve le nombre " << valueToFind << " en " << attempts << " essais." << std::endl;
    }

    system("pause");

    return 0;
}