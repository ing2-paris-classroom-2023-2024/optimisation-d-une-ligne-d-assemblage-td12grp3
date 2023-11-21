#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

int genererStation(Station * station){ // générer les stations en fonction des exclusions

     station->tab = malloc(sizeof(int) * 100);

    if (station->tab == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }
}

void Repartition(Exclu * exclu, Exclu * som2){ // fonction pour répartir les sommmets dans les stations
    Station *station;
    genererStation(&station); // en cours
}

void afficherExclusions(Exclu *exclu){
    char nomFichier[] = "exclusions"; // ouverture fichier des exclusions
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture d exclusions .\n");
    }

    int c,nContrainte;
    while((c=fgetc(fichier)) != EOF)
    {
        if(c=='\n')
            nContrainte++;
    } // récupération du nombre de contraintes du fichier (nb de lignes)  pour la prochaine boucle
    fseek(fichier, 0, SEEK_SET);// remettre le curseur au début du fichier texte


    exclu = (Exclu *)malloc(nContrainte * sizeof(Exclu)); // allouer dynamiquement de la mémoire au pointeur de la structure exclusion

    for (int i = 0; i < nContrainte; i++){
        int som1, som2;
        fscanf(fichier,"%d %d", &som1, &som2);

        exclu->som1 = som1;
        exclu->som2 = som2;
        printf("%d %d\n",exclu->som1,exclu->som2);// affichage du fichier texte pour vérifier que tout fonctionne
        Repartition(exclu->som1, exclu->som2);
    }
    free(exclu);
    fclose(fichier);
}





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
    Exclu exclu;
    afficherExclusions(&exclu);
    precedences();
    operations();
    temps_cycle();
    printf("bien");
    return 0;
}
