#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ville.h"


// Fonction pour retourner le maximum entre deux entiers
int max(int a, int b) {
    return (a > b) ? a : b;
}


// Fonction pour créer un nouveau nœud dans l'arbre AVL
Ville* nouveauNoeud(char* nom, int nbTrajets,int nbDeparts) {
    // Alloue de la mémoire pour un nouveau nœud
    Ville* ville = malloc(sizeof(Ville));
    // Vérifie si l'allocation a réussi
    if(ville == NULL){
       exit(10);
       }
       
       
    // Initialise les valeurs du nœud avec les paramètres fournis
    strcpy(ville->nom, nom);
    ville->nbTrajets = nbTrajets;
    ville->nbDeparts = nbDeparts;
    ville->gauche = ville->droite = NULL;
    ville->hauteur = 1;
    return ville;
}


// Fonction pour obtenir la hauteur d'un nœud dans l'arbre AVL
int hauteur(Ville* ville) {
    if (ville == NULL) {
    return 0;}
    return ville->hauteur;
}


// Fonctions de rotation droite l'arbre AVL
Ville* rotationDroite(Ville* y) {
    Ville* x = y->gauche;
    Ville* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    return x;
}


// Fonctions de rotation gauche l'arbre AVL
Ville* rotationGauche(Ville* x) {
    Ville* y = x->droite;
    Ville* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    return y;
}


// Fonction pour obtenir le facteur d'équilibre d'un nœud dans l'arbre AVL
int getBalance(Ville* ville) {
    if (ville == NULL){return 0;}
    return hauteur(ville->gauche) - hauteur(ville->droite);
}


// Fonction pour insérer un nœud dans l'arbre AVL (tri par le nombre de trajets)
Ville* insertionNbr(Ville* node, char* nom, int nbTrajets, int nbDeparts) {
    // Si le nœud est vide, crée un nouveau nœud avec les données fournies
    if (node == NULL){
       return nouveauNoeud(nom, nbTrajets, nbDeparts);
    }
    
    // Compare le nombre de trajets avec celui du nœud actuel
    if (nbTrajets < node->nbTrajets){
        node->gauche = insertionNbr(node->gauche, nom, nbTrajets, nbDeparts);
    } else if (nbTrajets > node->nbTrajets){
        node->droite = insertionNbr(node->droite, nom, nbTrajets, nbDeparts);
    } else {
        // Si les nombres de trajets sont égaux, ne fait rien (le nœud existant est conservé)
        return node;
    }

    // Met à jour la hauteur du nœud actuel
    node->hauteur = 1 + max(hauteur(node->gauche), hauteur(node->droite));

    // Obtient le facteur d'équilibre du nœud
    int balance = getBalance(node);

    // Cas de rotation à droite
    if (balance > 1 && nbTrajets < node->gauche->nbTrajets){
        return rotationDroite(node);
    }
    
    // Cas de rotation à gauche
    if (balance < -1 && nbTrajets > node->droite->nbTrajets){
        return rotationGauche(node);
    }

    // Cas de double rotation : gauche-droite
    if (balance > 1 && nbTrajets > node->gauche->nbTrajets) {
        node->gauche = rotationGauche(node->gauche);
        return rotationDroite(node);
    }

    // Cas de double rotation : droite-gauche
    if (balance < -1 && nbTrajets < node->droite->nbTrajets) {
        node->droite = rotationDroite(node->droite);
        return rotationGauche(node);
    }

    return node;
}


// Fonction pour insérer un nœud dans l'arbre AVL (trier les noms des villes)
Ville* insertionAlpha(Ville* node, char* nom, int nbTrajets, int nbDeparts) {
    // Si le nœud est vide, crée un nouveau nœud avec les données fournies
    if (node == NULL) {
        return nouveauNoeud(nom, nbTrajets, nbDeparts);
    }

    int cmp = strcmp(nom, node->nom); // Compare le nom de la ville avec celui du nœud actuel

    if (cmp < 0) { // Si le nom est inférieur, récursion du côté gauche
        node->gauche = insertionAlpha(node->gauche, nom, nbTrajets, nbDeparts);
    } else if (cmp > 0) { // Si le nom est supérieur, récursion du côté droit
        node->droite = insertionAlpha(node->droite, nom, nbTrajets, nbDeparts);
    } 
    
    // Met à jour la hauteur du nœud actuel
    node->hauteur = 1 + max(hauteur(node->gauche), hauteur(node->droite));

    int balance = getBalance(node); // Obtient le facteur d'équilibre du nœud

    if (balance > 1 && cmp < 0) { // Cas de rotation à droite
        return rotationDroite(node);
    }

    if (balance < -1 && cmp > 0) { // Cas de rotation à gauche
        return rotationGauche(node);
    }

    if (balance > 1 && cmp > 0) { // Cas de double rotation : gauche-droite
        node->gauche = rotationGauche(node->gauche);
        return rotationDroite(node);
    }

    if (balance < -1 && cmp < 0) { // Cas de double rotation : droite-gauche
        node->droite = rotationDroite(node->droite);
        return rotationGauche(node);
    }

    return node;
}


// Fonction récursive pour afficher les nœuds de l'arbre dans l'ordre croissant
void AffichageCroissant_t(Ville* racine) {
    if (racine != NULL) {
        AffichageCroissant_t(racine->gauche);
        printf("%s : %d : %d\n", racine->nom, racine->nbTrajets, racine->nbDeparts);
        AffichageCroissant_t(racine->droite);
    }
}


// Fonction récursive pour afficher les nœuds de l'arbre dans l'ordre décroissant
void AffichageDecroissant_t(Ville* racine) {
    if (racine != NULL) {
        AffichageDecroissant_t(racine->droite);
        printf("%s : %d : %d\n", racine->nom, racine->nbTrajets,racine->nbDeparts);
        AffichageDecroissant_t(racine->gauche);
    }
}


// Fonction pour libérer la mémoire utilisée par l'arbre AVL
void libererMemoireAVL(Ville* racine) {
    if (racine != NULL) {
        // Libération récursive de la mémoire des nœuds
        libererMemoireAVL(racine->gauche);
        libererMemoireAVL(racine->droite);
        // Libération de la mémoire du nœud courant
        free(racine);
    }
}
