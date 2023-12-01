#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header1.h"

int genererStation(int som, Station *station){ // générer les stations en fonction des exclusions

    station->tab = malloc(sizeof(int) * 100);

    if (station->tab == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }
    //station->tab = som;


}

void Repartition(int som1, int som2, int countStation) { // fonction pour répartir les sommets dans les stations
    Station *station;
    int same1, same2;



    // tester si sommet 1 est déjà placé
    for (int i = 1; i <= countStation; i++) {
        for (int j; j < sizeof(station[i].tab); j++) {
            if (station[i].tab[j] == som1) {
                same1 = i;
            } else
                same1 = -1;
        }
    }
    // // // // // // //



    // si som 1 est déjà dans une station

    if (same1 >= 0) {
        for (int i = 1; i <= countStation; i++) { // alors on vérifie tous num de chacun des tab de toutes les stations précédentes pour voir si le sommet 2 est déjà dans une station
            for (int j; j < sizeof( station[i].tab); j++) {
                if (station[i].tab[j] == som2) { // si le sommet 2 n'appartient à aucune des stations ou s'il se trouve dans la même station que le som1
                    if (station[same1].tab[j] == som2){ // si le sommet 2 est dans la même station que le sommet 1
                        genererStation(som2,  &station[(countStation + 1)]);  //(manque un element dans l'appel) on crée une nouvelle station
                        countStation++; // on ajoute 1 au compteur
                    }// si le sommet 2 n'est pas dans la même station que le sommet 1 pas besoin de le changer de place
                }
                else{ // si le sommet 2 n'appartient pas à une station
                    // dérouler les stations pour le placer dans la première station où le sommet 1 ne se trouve pas
                }

            }
        }
    }
    // // // // // // //



    // si som 1 n'est pas dans une station
    else {

        // tester si sommet 2 est déjà placé
        for (int i = 1; i <= countStation; i++) {
            for (int j; j < sizeof(station[i].tab); j++) {
                if (station[i].tab[j] == som2) {
                    same2 = i;
                } else
                    same2 = -1;
            }
        }
        // // // // // //


        // si le sommet 2 est déjà dans une station
        if (same2 >= 0) {
            // on place le sommet 1 dans la première station où le sommet 2 ne se trouve pas
        }



        // si le sommet 2 n'est pas dans une station
        else { // si aucun des deux n'est déjà placé

            if (countStation == 0 ){ // s'il n'y a pas encore de stations créées
                genererStation(som1,&station[(countStation + 1)]);
                genererStation(som2,&station[(countStation + 2)]);

                countStation = countStation+2; // on ajoute 2 stations
            }
            else{ // s'il y a déjà des stations créées
                station[1].tab;//rajouter [i] en fonction du sommet que l'on veut remplacer = som1; //on place les sommets dans les deux premières stations créées
                station[2].tab;//rajouter [i] en fonction du sommet que l'on veut remplacer = som2;

            }

        }
    }

    // // // // // // //



    if (same1 == 0 & same2 == 0){ // si aucun des sommets n'est déjà dans un tableau
        genererStation(som1, &station[1]); // on les associe à des stations différentes mais on ne vérifie pas si ces stations contiennent des sommets auquels ils ne peuvent pas être associés
        genererStation(som2, &station[2]);
    }
    if (same1 > 0 & same2 ==0){ // si le som1 est déjà dans un tableau
        // on ne touche pas au som1 qui est déjà placé
        genererStation(som2, &station[(same1+1)]);  // on place le som2 dans la station suivante
    }

    if (same1 ==0 & same2 >0){// si le sommet 2 est déjà dans un tableau
        genererStation(som1, &station[(same2+1)]);  // on place le som1 dans la station suivante
        // on ne touche pas au som2
    }

    // si les deux sont déjà dans des stations on vérifie qu'ils ne soient pas dans la même station
    if (same1 >0 & same2 >0) {
        if (same1 == same2){
            genererStation(som2,&station[(same1+1)]); // on place le som2 dans la station suivante pour qu'il ne soit pas avec le som1
        }
    }




}

void recupererExclusions(){
    char nomFichier[] = "exclusions"; // ouverture fichier des exclusions
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture d exclusions .\n");
    }

    int c,nContrainte; // nContraine = nombre de lignes du fichier texte
    while((c=fgetc(fichier)) != EOF)
    {
        if(c=='\n')
            nContrainte++;
    } // récupération du nombre de contraintes du fichier (nb de lignes)  pour la prochaine boucle
    fseek(fichier, 0, SEEK_SET);// remettre le curseur au début du fichier texte

    int countStation; // début du compteur de station à l'exterieur de la boucle pour ne pas perdre le total

    for (int i = 0; i < nContrainte; i++){ // on lit le fichier texte ligne par ligne

        int som1 = 0, som2 = 0;
        fscanf(fichier,"%d %d", &som1, &som2);
        printf("%d %d\n",som1,som2);// affichage du fichier texte pour faire une vérification
        Repartition(som1, som2, countStation); // ouverture sous programme qui réparti les sommets dans les stations
    }
    printf("\n Il y'a %d stations ",countStation);
    fclose(fichier);
}

