#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"


int max1(int a, int b) {
    return (a > b) ? a : b;
}

Distance* nouveauNoeud_s(int id, double min, double moy, double max, double valeur) {
    Distance* distance = malloc(sizeof(Distance));
    if (distance == NULL) {
        exit(10);
    }

    distance->id = id;
    distance->min = min;
    distance->moy = moy;
    distance->max = max;
    distance->valeur = valeur;
    distance->gauche = distance->droite = NULL;
    distance->hauteur = 1;

    return distance;
}

int hauteur_s(Distance* distance) {
    if (distance == NULL) {
        return 0;
    }
    return distance->hauteur;
}

Distance* rotationDroite_s(Distance* y) {
    Distance* x = y->gauche;
    Distance* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max1(hauteur_s(y->gauche), hauteur_s(y->droite)) + 1;
    x->hauteur = max1(hauteur_s(x->gauche), hauteur_s(x->droite)) + 1;

    return x;
}

Distance* rotationGauche_s(Distance* x) {
    Distance* y = x->droite;
    Distance* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max1(hauteur_s(x->gauche), hauteur_s(x->droite)) + 1;
    y->hauteur = max1(hauteur_s(y->gauche), hauteur_s(y->droite)) + 1;

    return y;
}

int getBalance_s(Distance* distance) {
    if (distance == NULL) {
        return 0;
    }
    return hauteur_s(distance->gauche) - hauteur_s(distance->droite);
}

Distance* insertAVL(Distance* racine, int id, double min, double moy, double max, double valeur) {
    if (racine == NULL) {
        return nouveauNoeud_s(id, min, moy, max, valeur);
    }

    if (valeur < racine->valeur) {
        racine->gauche = insertAVL(racine->gauche, id, min, moy, max, valeur);
    } else if (valeur > racine->valeur) {
        racine->droite = insertAVL(racine->droite, id, min, moy, max, valeur);
    } else {
        return racine;
    }

    racine->hauteur = 1 + max1(hauteur_s(racine->gauche), hauteur_s(racine->droite));

    int balance = getBalance_s(racine);

    if (balance > 1 && valeur < racine->gauche->valeur) {
        return rotationDroite_s(racine);
    }

    if (balance < -1 && valeur > racine->droite->valeur) {
        return rotationGauche_s(racine);
    }

    if (balance > 1 && valeur > racine->gauche->valeur) {
        racine->gauche = rotationGauche_s(racine->gauche);
        return rotationDroite_s(racine);
    }

    if (balance < -1 && valeur < racine->droite->valeur) {
        racine->droite = rotationDroite_s(racine->droite);
        return rotationGauche_s(racine);
    }

    return racine;
}

void parcoursDecroissant(Distance* racine, FILE* fichierSortie) {
    if (racine != NULL) {
        parcoursDecroissant(racine->droite, fichierSortie);
        fprintf(fichierSortie, "%d;%.3f;%.3f;%.3f;%.3f\n", racine->id, racine->min, racine->moy, racine->max, racine->valeur);
        parcoursDecroissant(racine->gauche, fichierSortie);
    }
}

// Fonction pour libérer la mémoire utilisée par l'AVL
void libererMemoireAVL(Distance* racine) {
    if (racine != NULL) {
        libererMemoireAVL(racine->gauche);
        libererMemoireAVL(racine->droite);
        free(racine);
    }
}
