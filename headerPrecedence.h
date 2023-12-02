//
// Created by coren on 02/12/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12GRP3_HEADERPRECEDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12GRP3_HEADERPRECEDENCE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{    struct Arc* arc;
    int valeur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int orientation;
    int ordre;
    pSommet* pSommet;
    int** matrice;
    int *tab_sommet;
    int* doublon;
    float* poid;
} Graphe;



// Structure pour un élément de la file de priorité
typedef struct ElementFilePriorite {
    int sommet;
    int predecesseur;
} ElementFilePriorite;


typedef struct {
    int * station;
    float temps_max;
}station;

typedef struct{
    station * tot_station;
    int taille;
}glob_station;
// créer le graphe
Graphe* CreerGraphe(int ordre);

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier, Graphe* graphe);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2);


void BFS(Graphe* graphe, int sommetInitial);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12GRP3_HEADERPRECEDENCE_H
