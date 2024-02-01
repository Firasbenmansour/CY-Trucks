#ifndef STATS_H
#define STATS_H

#define MAX_BUFFER_SIZE 1024

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

typedef struct {
    double min_distance;
    double max_distance;
    double moyenne_distance;
    int nombre_etapes;
} TrajetInfo;

typedef struct {
    int id_trajet;
    TrajetInfo info;
} Trajet;


int hash(int id_trajet, int max_trajets);
void updateTrajetInfo(TrajetInfo *info, double distance);
void lireEtTraiterDonnees(FILE *inputFile, Trajet **trajets, int max_trajets);
void ecrireResultats(FILE *outputFile, Trajet **trajets, int max_trajets);
int lireNombreMaxTrajets();
int max_s(int a, int b);
Distance* nouveauNoeud_s(int id, double min, double moy, double max, double valeur);
int hauteur(Distance* distance);
Distance* rotationDroite_s(Distance* y);
Distance* rotationGauche_s(Distance* x);
int getBalance_s(Distance* distance);
Distance* insertAVL(Distance* racine, int id, double min, double moy, double max, double valeur);
void AffichageDecroissant(Distance* racine, FILE* fichierSortie);
void libererMemoireAVL_s(Distance* racine) ;

#endif /* STATS_H */
