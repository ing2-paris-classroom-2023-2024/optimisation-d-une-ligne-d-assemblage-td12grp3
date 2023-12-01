#include <stdio.h>
#include "header1.h"

void precedences(){
    char nomFichier[] = "precedences.txt"; // ouverture fichier des precedences
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture des precedences.\n");
    }
}

void operations(){
    char nomFichier[] = "operations.txt"; // ouverture fichier des operations
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture des operation.\n");
    }
}

void temps_cycle(){
    char nomFichier[] = "temps_cycle.txt"; // ouverture fichier du temps de cycle
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du temps_cycle.\n");
    }
}

int main() {
    repartitionOperations();
    //recupererExclusions();
    precedences();
    operations();
    temps_cycle();
    printf("Ca fonctionne pas assez chef");
    return 0;
}

