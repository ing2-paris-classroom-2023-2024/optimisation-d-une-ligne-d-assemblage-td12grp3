#include <stdio.h>
#include <stdlib.h>

// Définir la taille maximale de l'ensemble d'opérations
#define MAX_OPERATIONS 35

// Définir une structure de station
struct Station {
    int operations[MAX_OPERATIONS];
    int taille;
};

// Fonction pour lire les opérations à partir d'un fichier
int lireOperations(char *nom_fichier, int *operations) {
    FILE *f_operations = fopen(nom_fichier, "r");
    if (f_operations == NULL) {
        perror("Erreur lors de la lecture du fichier d'opérations");
        return -1;
    }

    int taille = 0;

    while (fscanf(f_operations, "%d", &operations[taille]) == 1) {
        ++taille;
    }

    fclose(f_operations);

    return taille;
}

// Fonction pour lire les paires d'opérations à partir d'un fichier
int lireExclusions(char *nom_fichier, int exclusions[][2]) {
    FILE *f_exclusions = fopen(nom_fichier, "r");
    if (f_exclusions == NULL) {
        perror("Erreur lors de la lecture du fichier d'exclusions");
        return -1;
    }

    int taille = 0;

    while (fscanf(f_exclusions, "%d %d", &exclusions[taille][0], &exclusions[taille][1]) == 2) {
        ++taille;
    }

    fclose(f_exclusions);

    return taille;
}

// Fonction pour vérifier si une opération peut être affectée à une station en respectant les contraintes d'exclusion
int peutAffecter(int operation, struct Station *station, int E[][2], int taille_E) {
    for (int i = 0; i < station->taille; ++i) {
        for (int j = 0; j < taille_E; ++j) {
            if ((station->operations[i] == E[j][0] && operation == E[j][1]) ||
                (station->operations[i] == E[j][1] && operation == E[j][0])) {
                return 0; // Ne peut pas affecter
            }
        }
    }
    return 1; // Peut affecter
}

// Fonction pour affecter une opération à une station disponible
void affecterOperation(int operation, struct Station *stations, int *nombre_stations, int E[][2], int taille_E) {
    int stationDisponible = -1;

    for (int i = 0; i < *nombre_stations; ++i) {
        if (peutAffecter(operation, &stations[i], E, taille_E)) {
            stationDisponible = i;
            break;
        }
    }

    if (stationDisponible == -1) {
        // Créer une nouvelle station
        stations[*nombre_stations].operations[0] = operation;
        stations[*nombre_stations].taille = 1;
        ++(*nombre_stations);
    } else {
        // Affecter à la station disponible
        stations[stationDisponible].operations[stations[stationDisponible].taille] = operation;
        ++stations[stationDisponible].taille;
    }
}

// Fonction principale
void repartitionOperations() {
    int V[MAX_OPERATIONS];
    int taille_V = lireOperations("operations_a_faire.txt", V);

    int E[MAX_OPERATIONS][2];
    int taille_E = lireExclusions("exclusion.txt", E);

    // Si la lecture des fichiers a échoué, quitter la fonction
    if (taille_V == -1 || taille_E == -1) {
        return;
    }

    // Initialiser une liste pour représenter les stations de travail
    struct Station stations[MAX_OPERATIONS];
    int nombre_stations = 0;

    // Pour chaque opération, affecter à une station disponible
    for (int i = 0; i < taille_V; ++i) {
        affecterOperation(V[i], stations, &nombre_stations, E, taille_E);
    }

    // Afficher la répartition des opérations par station
    for (int i = 0; i < nombre_stations; ++i) {
        printf("Station %d: ", i + 1);
        for (int j = 0; j < stations[i].taille; ++j) {
            printf("%d ", stations[i].operations[j]);
        }
        printf("\n");
        }
}
