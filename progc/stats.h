#ifndef STATS_H
#define STATS_H


typedef struct Distance {
    int id;
    double min;
    double moy;
    double max;
    double valeur;
    struct Distance *gauche;
    struct Distance *droite;
    int hauteur;
} Distance;
int max1(int a, int b);
Distance* nouveauNoeud_s(int id, double min, double moy, double max, double valeur);
int hauteur(Distance* distance);
Distance* rotationDroite_s(Distance* y);
Distance* rotationGauche_s(Distance* x);
int getBalance_s(Distance* distance);
Distance* insertAVL(Distance* racine, int id, double min, double moy, double max, double valeur);
void parcoursDecroissant(Distance* racine, FILE* fichierSortie);
void libererMemoireAVL(Distance* racine) ;

#endif /* STATS_H */
