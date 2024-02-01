#ifndef VILLE_H
#define VILLE_H

typedef struct Ville {
    char nom[100];
    int nbTrajets;
    int nbDeparts;
    struct Ville *gauche;
    struct Ville *droite;
    int hauteur;
} Ville;

int max(int a, int b);
Ville* nouveauNoeud(char* nom, int nbTrajets, int nbDeparts);
int hauteur(Ville* ville);
Ville* rotationDroite(Ville* y);
Ville* rotationGauche(Ville* x);
int getBalance(Ville* ville);
Ville* insertionNbr(Ville* node, char* nom, int nbTrajets , int nbDeparts);
Ville* insertionAlpha(Ville* node, char* nom, int nbTrajets,int nbDeparts);
void AffichageCroissant_t(Ville* racine);
void AffichageDecroissant_t(Ville* racine);
void libererMemoireAVL(Ville* racine);
#endif /* VILLE_H */
