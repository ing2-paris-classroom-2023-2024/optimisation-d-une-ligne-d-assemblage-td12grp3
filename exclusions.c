/*#include <stdio.h>
#include <stdlib.h>

// Définir la taille maximale de l'ensemble d'opérations
#define MAX_OPERATIONS 100

// Définir une structure de station
struct Station {
    int *tab;
    int taille;
};

// Fonction pour initialiser une station
void initialiserStation(struct Station *station) {
    station->tab = malloc(sizeof(int) * MAX_OPERATIONS);
    if (station->tab == NULL) {
        printf("Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    station->taille = 0;
}

// Fonction pour vérifier si une opération peut être affectée à une station en respectant les contraintes d'exclusion
int peutAffecter(int operation, struct Station *station, int E[][2], int taille_E) {
    for (int i = 0; i < station->taille; ++i) {
        for (int j = 0; j < taille_E; ++j) {
            if ((station->tab[i] == E[j][0] && operation == E[j][1]) ||
                (station->tab[i] == E[j][1] && operation == E[j][0])) {
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
        initialiserStation(&stations[*nombre_stations]);
        stations[*nombre_stations].tab[0] = operation;
        stations[*nombre_stations].taille = 1;
        ++(*nombre_stations);
    } else {
        // Affecter à la station disponible
        stations[stationDisponible].tab[stations[stationDisponible].taille] = operation;
        ++stations[stationDisponible].taille;
    }
}

// Fonction principale
void repartitionOperations() {
    // Initialiser une liste pour représenter les stations de travail
    struct Station stations[MAX_OPERATIONS];
    int nombre_stations = 0;

    // Initialiser les opérations et les exclusions (à remplacer par votre propre mécanisme)
    int V[MAX_OPERATIONS] = {1, 2, 3, 4, 5};
    int E[MAX_OPERATIONS][2] = {{1, 2}, {3, 4}};

    // Pour chaque opération, affecter à une station disponible
    for (int i = 0; i < sizeof(V) / sizeof(V[0]); ++i) {
        affecterOperation(V[i], stations, &nombre_stations, E, sizeof(E) / sizeof(E[0]));
    }

    // Afficher la répartition des opérations par station
    for (int i = 0; i < nombre_stations; ++i) {
        printf("Station %d: ", i + 1);
        for (int j = 0; j < stations[i].taille; ++j) {
            printf("%d ", stations[i].tab[j]);
        }
        printf("\n");
    }

    // Libérer la mémoire allouée
    for (int i = 0; i < nombre_stations; ++i) {
        free(stations[i].tab);
    }
}

*/