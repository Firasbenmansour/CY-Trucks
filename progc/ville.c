#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ville.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

Ville* nouveauNoeud(char* nom, int nbTrajets,int nbDeparts) {
    Ville* ville = malloc(sizeof(Ville));
    if(ville == NULL){
       exit(10);
       }
    strcpy(ville->nom, nom);
    ville->nbTrajets = nbTrajets;
    ville->nbDeparts = nbDeparts;
    ville->gauche = ville->droite = NULL;
    ville->hauteur = 1;
    return ville;
}

int hauteur(Ville* ville) {
    if (ville == NULL) {
    return 0;}
    return ville->hauteur;
}

Ville* rotationDroite(Ville* y) {
    Ville* x = y->gauche;
    Ville* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    return x;
}

Ville* rotationGauche(Ville* x) {
    Ville* y = x->droite;
    Ville* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    return y;
}

int getBalance(Ville* ville) {
    if (ville == NULL){return 0;}
    return hauteur(ville->gauche) - hauteur(ville->droite);
}
Ville* insertionNbr(Ville* node, char* nom, int nbTrajets , int nbDeparts) {
    if (node == NULL){
       return nouveauNoeud(nom, nbTrajets, nbDeparts);
    }
    
    if (nbTrajets < node->nbTrajets){
        node->gauche = insertionNbr(node->gauche, nom, nbTrajets, nbDeparts);}
    else if (nbTrajets > node->nbTrajets){
        node->droite = insertionNbr(node->droite, nom, nbTrajets, nbDeparts);}
    else{
        return node;}

    node->hauteur = 1 + max(hauteur(node->gauche), hauteur(node->droite));

    int balance = getBalance(node);

    if (balance > 1 && nbTrajets < node->gauche->nbTrajets){
        return rotationDroite(node);
        }
    if (balance < -1 && nbTrajets > node->droite->nbTrajets){
        return rotationGauche(node);
        }
    if (balance > 1 && nbTrajets > node->gauche->nbTrajets) {
        node->gauche = rotationGauche(node->gauche);
        return rotationDroite(node);
    }

    if (balance < -1 && nbTrajets < node->droite->nbTrajets) {
        node->droite = rotationDroite(node->droite);
        return rotationGauche(node);
    }

    return node;
}

Ville* insertionAlpha(Ville* node, char* nom, int nbTrajets, int nbDeparts) {
    if (node == NULL) {
        return nouveauNoeud(nom, nbTrajets, nbDeparts);
    }

    int cmp = strcmp(nom, node->nom);

    if (cmp < 0) {
        node->gauche = insertionAlpha(node->gauche, nom, nbTrajets, nbDeparts);
    } else if (cmp > 0) {
        node->droite = insertionAlpha(node->droite, nom, nbTrajets, nbDeparts);
    } else {
        // Handle case where names are equal (you may want to define specific behavior)
        // For example, you might compare other fields or use a secondary criterion.
    }

    node->hauteur = 1 + max(hauteur(node->gauche), hauteur(node->droite));

    int balance = getBalance(node);

    if (balance > 1 && cmp < 0) {
        return rotationDroite(node);
    }

    if (balance < -1 && cmp > 0) {
        return rotationGauche(node);
    }

    if (balance > 1 && cmp > 0) {
        node->gauche = rotationGauche(node->gauche);
        return rotationDroite(node);
    }

    if (balance < -1 && cmp < 0) {
        node->droite = rotationDroite(node->droite);
        return rotationGauche(node);
    }

    return node;
}

void trierVillesAlpha(Ville* racine) {
    if (racine != NULL) {
        trierVillesAlpha(racine->gauche);
        printf("%s : %d : %d\n", racine->nom, racine->nbTrajets, racine->nbDeparts);
        trierVillesAlpha(racine->droite);
    }
}
void trierVilles(Ville* racine) {
    if (racine != NULL) {
        trierVilles(racine->droite);
        printf("%s : %d : %d\n", racine->nom, racine->nbTrajets,racine->nbDeparts);
        trierVilles(racine->gauche);
    }
}
