#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

//void ComparerExclu(Exclu * exclu->som1, Exclu * som2){}

void afficherExclusions(Exclu *exclu){
    char nomFichier[] = "exclusions"; // ouverture fichier des exclusions
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture d exclusions .\n");
    }
    int c,nLignes;


    while((c=fgetc(fichier)) != EOF)
    {
        if(c=='\n')
            nLignes++;
    } // récupération du nombre de lignes du fichier exclusions
    fseek(fichier, 0, SEEK_SET);// remettre le curseur au début du fichier texte


    exclu = (Exclu *)malloc(nLignes * sizeof(Exclu)); // allouer dynamiquement de la mémoire au pointeur de la structure exclusion

    for (int i = 0; i < nLignes; i++){
        int som1, som2;
        fscanf(fichier,"%d %d", &som1, &som2);

        exclu[i].som1 = som1;
        exclu[i].som2 = som2;
        printf("%d %d\n",exclu[i].som1,exclu[i].som2);
        //ComparerExclu(&exclu[i].som1, &exclu[i].som2);
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
