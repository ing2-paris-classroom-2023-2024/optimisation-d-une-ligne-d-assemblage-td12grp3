#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Structure pour représenter une opération
typedef struct {
    int id;
    char color;
} Operation;

// Matrice d'exclusion
int **exclusionMatrix;

// Liste des opérations
Operation *operations;

// Nombre total d'opérations
int numOperations;

// Nombre total de couleurs
int numColors;

// Vérifie si une couleur peut être attribuée à un sommet donné
bool couleurDispoPourSommet(int sommet, char c) {
    for (int i = 0; i < numOperations; i++)
        if (exclusionMatrix[sommet][i] && c == operations[i].color)
            return false;
    return true;
}

// Algorithme de coloration de graphe
void colorationGraphe() {
    for (int sommet = 0; sommet < numOperations; sommet++) {
        for (char c = 'A'; c < 'A' + numColors; c++) {
            if (couleurDispoPourSommet(sommet, c)) {
                operations[sommet].color = c;
                break;
            }
        }
    }
}

// Fonction pour lire les exclusions depuis le fichier
void readExclusionsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int op1, op2;
    while (fscanf(file, "%d %d", &op1, &op2) == 2) {
        exclusionMatrix[op1 - 1][op2 - 1] = exclusionMatrix[op2 - 1][op1 - 1] = 1;
    }

    fclose(file);
}

// Fonction pour effectuer la coloration et afficher les résultats
void performColoring() {
    // Lecture du nombre d'opérations et de couleurs depuis le fichier ou l'utilisateur
    printf("Entrez le nombre d'opérations : ");
    scanf("%d", &numOperations);

    printf("Entrez le nombre de couleurs : ");
    scanf("%d", &numColors);

    // Allocation dynamique de la mémoire
    exclusionMatrix = (int **)malloc(numOperations * sizeof(int *));
    operations = (Operation *)malloc(numOperations * sizeof(Operation));

    for (int i = 0; i < numOperations; i++) {
        exclusionMatrix[i] = (int *)malloc(numOperations * sizeof(int));
        operations[i].id = i + 1;
        operations[i].color = '0'; // Initialise à un caractère nul, car '0' ne sera jamais une couleur valide
    }

    // Initialisation de la matrice d'exclusion
    for (int i = 0; i < numOperations; i++) {
        for (int j = 0; j < numOperations; j++) {
            exclusionMatrix[i][j] = 0;
        }
    }

    // Lecture des exclusions depuis le fichier
    readExclusionsFromFile("exclusionExemple.txt");

    // Applique l'algorithme de coloration
    colorationGraphe();

    // Affiche les couleurs attribuées à chaque opération
    printf("Coloration des opérations :\n");
    for (int i = 0; i < numOperations; i++) {
        printf("Opération %d : Couleur %c\n", operations[i].id, operations[i].color);
    }

    // Libération de la mémoire allouée dynamiquement
    for (int i = 0; i < numOperations; i++) {
        free(exclusionMatrix[i]);
    }
    free(exclusionMatrix);
    free(operations);
}

// Fonction principale
int main() {
    // Appel du sous-programme pour effectuer la coloration et afficher les résultats
    performColoring();

    return 0;
}
//
// Created by clara on 30/11/2023.
//
