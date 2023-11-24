#include <stdio.h>
#include <stdlib.h>
#include "header1.h"

int genererStation(Station *station){ // générer les stations en fonction des exclusions

    station->tab = malloc(sizeof(int) * 100);

    if (station->tab == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }
}

void Repartition(int som1, int som2){ // fonction pour répartir les sommmets dans les stations
    Station *station;
    genererStation(&station); // en cours
}

void afficherExclusions(){
    int test1;
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

    for (int i = 0; i < nContrainte; i++){
        int som1 = 0, som2 = 0;
        fscanf(fichier,"%d %d", &som1, &som2);
        som1 = som1;
        som2 = som2;
        printf("%d %d\n",som1,som2);// affichage du fichier texte pour vérifier que tout fonctionne
        Repartition(som1, som2);
    }
    fclose(fichier);
}

