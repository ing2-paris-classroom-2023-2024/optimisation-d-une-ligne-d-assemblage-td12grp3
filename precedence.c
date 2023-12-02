#include "headerPrecedence.h"



// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while(temp->arc_suivant != NULL)
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    Newgraphe->poid=(float*)malloc(ordre*sizeof(float));
    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}
glob_station * Creation_station(int ordre){
    glob_station  * NewStation = (glob_station*)malloc(sizeof(glob_station));
    NewStation->tot_station=(station*)malloc(sizeof(station)*ordre);
    NewStation->taille= ordre;
    for(int i=0; i<ordre; i++)
    {
        NewStation->tot_station[i].station=(int*)malloc(sizeof(int)*ordre);

    }
    return NewStation;
}

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe* lire_graphe(char* nomFichier, Graphe* graphe) {
    FILE* ifs = fopen("precedences.txt", "r");

    int s1, s2;
    char line[100];
    char line2[100];
    int edges_count = 0;

    int max_vertex = -1;
    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while (fgets(line, sizeof(line), ifs)) {
        char *token = strtok(line, " \n");

        while (token != NULL) {
            int vertex = atoi(token); // Convertir la chaîne en entier

            if (vertex > max_vertex) {
                max_vertex = vertex;
            }

            token = strtok(NULL, " \n");
        }
    }
    fseek(ifs, 0, SEEK_SET);
    while (fgets(line2, sizeof(line), ifs)) {
        // Incrémenter le compteur d'arêtes pour chaque ligne lue
        edges_count++;
    }
    fseek(ifs, 0, SEEK_SET);


    FILE* ope = fopen("operations.txt", "r");
    float poid;
    int num2;
    printf("edge : %d, sommet : %d",edges_count,max_vertex);
    graphe = CreerGraphe(max_vertex+1); // créer le graphe d'ordre sommets


    graphe->ordre = max_vertex+1;

    graphe->tab_sommet = (int*)malloc(graphe->ordre * sizeof(int)); // Tableau pour marquer les sommets visités
    printf("edge : %d, sommet : %d",edges_count,max_vertex);
    graphe->doublon = (int*)malloc(graphe->ordre * sizeof(int)); // Tableau pour enregistrer les doublons

    int rows = graphe->ordre; // Nombre de lignes
    int cols = graphe->ordre; // Nombre de colonnes
    graphe->matrice = (int **)malloc(rows * sizeof(int *));

    if (graphe->matrice == NULL) {
        printf("Allocation de mémoire échouée.\n");

    }
    printf("edge : %d, sommet : %d",edges_count,max_vertex);
    // Allocation dynamique pour chaque ligne
    for (int i = 0; i < rows; i++) {
        graphe->matrice[i] = (int *)malloc(cols * sizeof(int));
        if (graphe->matrice[i] == NULL) {
            printf("Allocation de mémoire échouée.\n");

        }
    }

    // Initialisation de la matrice
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            graphe->matrice[i][j] = 0;

        }
    }
    printf("edge : %d, sommet : %d",edges_count,max_vertex);



    for (int i = 0; i < graphe->ordre; i++) {
        graphe->doublon[i] = -1; // Initialiser à une valeur impossible pour repérer les doublons
    }

    // Créer les arêtes du graphe
    for (int i = 0; i < edges_count; ++i) {
        fscanf(ifs, "%d %d", &s1, &s2);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2);
        graphe->matrice[i][s2]=1;
        for (int o = 0; o < graphe->ordre; o++) {
            if (s2 == graphe->tab_sommet[o]) {
                graphe->doublon[o] = s2;

            }
        }
        graphe->tab_sommet[s2] = s2;
    }
    for (int o = 0; o < graphe->ordre; o++) {
        if (graphe->doublon[o] != -1) {
            printf("Doublon : %d \n", graphe->doublon[o]);
        }
    }
    for (int i=0; i<graphe->ordre;i++){
        fscanf(ope,"%d %f",&num2,&poid);
        graphe->poid[num2]=poid;
    }



    fclose(ifs);
    BFS(graphe, 1);
    return graphe;
}


// Fonction principale BFS avec la stratégie spécifiée
void BFS(Graphe* graphe, int sommetInitial)
{
    if (graphe == NULL || sommetInitial < 0 || sommetInitial >= graphe->ordre)
    {
        printf("Graphe non valide ou sommet initial invalide.\n");
        return;
    }
    glob_station * Grand_station= Creation_station(graphe->ordre);
    for (int a =0;a<graphe->ordre;a++){
        for (int i = 0 ; i < graphe->ordre;i++){
            Grand_station->tot_station[a].station[i]=-1;
        }

    }
    int n = 0,m=0;
    char* visite = (char*)malloc(graphe->ordre * sizeof(char)); // Tableau pour marquer les sommets visités
    int ordre = 0;
    float compteur;
    // Initialiser le tableau de visite et la file de priorité
    for (int i = 0; i < graphe->ordre; i++)
    {
        visite[i] = '0'; // '0' pour non marqué, '1' pour marqué
    }

    ElementFilePriorite* filePriorite = (ElementFilePriorite*)malloc(graphe->ordre * sizeof(ElementFilePriorite));
    int debut = 0, fin = 0;

    // Enfiler le sommet initial avec un prédécesseur fictif (-1)
    filePriorite[fin].sommet = sommetInitial;
    filePriorite[fin].predecesseur = -1;
    visite[sommetInitial] = '1';
    fin++;
    int p = 0 ;
    while (debut < fin)
    {
        // Défiler le prochain sommet selon la stratégie

        int sommetCourant = filePriorite[debut].sommet;
        int predecesseurCourant = filePriorite[debut].predecesseur;
        debut++;

        // Noter le prédécesseur du sommet courant
        printf("Sommet %d visite (ordre %d) avec predecesseur %d\n", sommetCourant, ++ordre, predecesseurCourant);

        pArc arc = graphe->pSommet[sommetCourant]->arc;
        int o=0;
        // Parcourir tous les successeurs non visités
        while (arc != NULL)
        {
            int sommetSuivant = arc->sommet;

            if (sommetSuivant==graphe->doublon[sommetSuivant]){
                for (int y = 0  ; y<graphe->ordre; y++ ){
                    if (graphe->matrice[y][sommetSuivant]==1){
                        o++;
                    }
                }

                for (int y = 0  ; y<graphe->ordre; y++ ){
                    if ((graphe->matrice[y][sommetSuivant]==1)&&(o!=1)&& (visite[y]=='0')){

                        if (arc->arc_suivant == NULL) {

                            p = 1;
                            graphe->matrice[y][sommetSuivant]=0;
                            break;}
                        arc = arc->arc_suivant;
                        sommetSuivant = arc->sommet;
                        p=0;

                        graphe->matrice[y][sommetSuivant]=0;
                        break;
                    }
                }
            }
            if (p==0) {
                if (visite[sommetSuivant] == '0') // Si le sommet n'a pas encore été visité
                {
                    // Enfiler le successeur avec le prédécesseur actuel
                    filePriorite[fin].sommet = sommetSuivant;
                    filePriorite[fin].predecesseur = sommetCourant;
                    visite[sommetSuivant] = '1';
                    fin++;

                    // Afficher le sommet adjacent

                }
            }

            arc = arc->arc_suivant;
            p=0;
        }
        if ((compteur+graphe->poid[sommetCourant])<=5.000000){
            compteur=compteur+graphe->poid[sommetCourant];
            Grand_station->tot_station[m].station[n]=sommetCourant;
            Grand_station->tot_station[m].temps_max=compteur;
            n++;
        }
        else{
            compteur=0;
            m++;
            n=0;
            compteur=graphe->poid[sommetCourant];
            Grand_station->tot_station[m].station[n]=sommetCourant;
            Grand_station->tot_station[m].temps_max=compteur;
        }

    }
    for (int a =0;a<graphe->ordre;a++){
        for (int i = 0 ; i < graphe->ordre;i++){
            if (Grand_station->tot_station[a].station[i]!=-1)
                printf("%d, ",Grand_station->tot_station[a].station[i]);
        }
        if (Grand_station->tot_station[a].temps_max>0.001){
            printf(" temps max  :  %f\n",Grand_station->tot_station[a].temps_max);}
    }

    free(visite);
    free(filePriorite);
}


