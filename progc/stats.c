#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"


// Fonction qui lit le nombre maximum de trajets à partir d'un fichier
int lireNombreMaxTrajets() {
    
    // Ouvre le fichier en mode lecture
    FILE *nombreTrajetsFile = fopen("temp/nombre_trajets.txt", "r");
    // Vérifie si l'ouverture du fichier a réussi
    if (nombreTrajetsFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de nombre de trajets");
        exit(EXIT_FAILURE); // Quitte le programme avec un code d'erreur
    }

    // Lire le nombre maximal des trajets
    int max_trajets;
        if (fscanf(nombreTrajetsFile, "%d", &max_trajets) != 1) {
        perror("Erreur lors de la lecture du nombre de trajets");
        exit(EXIT_FAILURE); // Quitte le programme avec un code d'erreur si la lecture échoue
    }

    // Ferme le fichier après la lecture
    fclose(nombreTrajetsFile);
    // Renvoie le nombre maximum de trajets lu
    return max_trajets;
}



// Fonction de hachage pour calculer l'index d'un trajet dans le tableau
int hash(int id_trajet, int max_trajets) {
    return id_trajet % max_trajets;
}


// Fonction pour mettre à jour les informations d'un trajet
void updateTrajetInfo(TrajetInfo *info, double distance) {
    // Mettre à jour la distance minimale 
    if (distance < info->min_distance || info->nombre_etapes == 0) {
        info->min_distance = distance;
    }
    // Mettre à jour la distance maximale 
    if (distance > info->max_distance) {
        info->max_distance = distance;
    }
    // Ajoute la distance à la somme pour calculer la moyenne
    info->moyenne_distance += distance;
    // compteur du nombre d'étapes
    info->nombre_etapes++;  
}

// Fonction pour lire et traiter les données 
void lireEtTraiterDonnees(FILE *inputFile, Trajet **trajets, int max_trajets) {
    char buffer[MAX_BUFFER_SIZE];

    // Parcours le fichier ligne par ligne
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        int id_trajet;
        double distance;
        // Lit l'id du trajet et la distance à partir de la ligne
        sscanf(buffer, "%d;%lf", &id_trajet, &distance);

        // Calcule l'index du trajet dans le tableau à l'aide de la fonction de hachage
        int index = hash(id_trajet, max_trajets);

        // Si l'emplacement dans le tableau est vide, alloue de la mémoire pour un nouveau trajet
        if (trajets[index] == NULL) {
            trajets[index] = malloc(sizeof(Trajet));
            trajets[index]->id_trajet = id_trajet;
            memset(&trajets[index]->info, 0, sizeof(TrajetInfo));
        }

        // Met à jour les informations du trajet
        updateTrajetInfo(&trajets[index]->info, distance);
    }
}

// Fonction pour écrire les résultats dans un fichier de sortie
void ecrireResultats(FILE *outputFile, Trajet **trajets, int max_trajets) {
    for (int i = 0; i < max_trajets; i++) {
        if (trajets[i] != NULL) {
            TrajetInfo *info = &trajets[i]->info;
            // Vérifie si le trajet a au moins une étape
            if (info->nombre_etapes > 0) {
                // Calcule la moyenne de la distance
                info->moyenne_distance /= info->nombre_etapes;
                // Calcule la différence entre la distance maximale et minimale
                double difference_max_min = info->max_distance - info->min_distance;
                // Écrit les résultats dans le fichier de sortie
                fprintf(outputFile, "%d;%.2f;%.2f;%.2f;%.2f\n", trajets[i]->id_trajet,
                        info->min_distance, info->moyenne_distance, info->max_distance, difference_max_min);
            }
            // Libère la mémoire allouée pour le trajet
            free(trajets[i]);
        }
    }
}





// Fonction pour retourner le maximum entre deux entiers
int max_s(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction pour créer un nouveau nœud dans l'arbre AVL
Distance* nouveauNoeud_s(int id, double min, double moy, double max, double valeur) {
    // Alloue de la mémoire pour un nouveau nœud
    Distance* distance = malloc(sizeof(Distance));
    // Vérifie si l'allocation a réussi
    if (distance == NULL) {
        exit(10); 
    }

    // Initialise les valeurs du nœud avec les paramètres fournis
    distance->id = id;
    distance->min = min;
    distance->moy = moy;
    distance->max = max;
    distance->valeur = valeur;
    distance->gauche = distance->droite = NULL;
    distance->hauteur = 1;

    return distance;
}


// Fonction pour obtenir la hauteur d'un nœud dans l'arbre AVL
int hauteur_s(Distance* distance) {
    if (distance == NULL) {
        return 0;
    }
    return distance->hauteur;
}


// Fonctions de rotation droite l'arbre AVL
Distance* rotationDroite_s(Distance* y) {
    Distance* x = y->gauche;
    Distance* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max_s(hauteur_s(y->gauche), hauteur_s(y->droite)) + 1;
    x->hauteur = max_s(hauteur_s(x->gauche), hauteur_s(x->droite)) + 1;

    return x;
}


// Fonctions de rotation gauche l'arbre AVL
Distance* rotationGauche_s(Distance* x) {
    Distance* y = x->droite;
    Distance* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max_s(hauteur_s(x->gauche), hauteur_s(x->droite)) + 1;
    y->hauteur = max_s(hauteur_s(y->gauche), hauteur_s(y->droite)) + 1;

    return y;
}


// Fonction pour obtenir le facteur d'équilibre d'un nœud dans l'arbre AVL
int getBalance_s(Distance* distance) {
    if (distance == NULL) {
        return 0;
    }
    return hauteur_s(distance->gauche) - hauteur_s(distance->droite);
}

// Fonction pour insérer un nœud dans l'arbre AVL
Distance* insertAVL(Distance* racine, int id, double min, double moy, double max, double valeur) {
    // Si l'arbre est vide, crée un nouveau nœud avec les valeurs fournies
    if (racine == NULL) {
        return nouveauNoeud_s(id, min, moy, max, valeur);
    }

    // Si la valeur à insérer est plus petite, récursion du côté gauche
    if (valeur < racine->valeur) {
        racine->gauche = insertAVL(racine->gauche, id, min, moy, max, valeur);
    }
    // Si la valeur à insérer est plus grande, récursion du côté droit
    else if (valeur > racine->valeur) {
        racine->droite = insertAVL(racine->droite, id, min, moy, max, valeur);
    }
    // Si la valeur à insérer est égale, retourne le nœud actuel (pas d'insertion)
    else {
        return racine;
    }

    // Met à jour la hauteur du nœud courant
    racine->hauteur = 1 + max_s(hauteur_s(racine->gauche), hauteur_s(racine->droite));

    // Vérifie l'équilibre de l'arbre après l'insertion
    int balance = getBalance_s(racine);

    // Cas de rotation à droite
    if (balance > 1 && valeur < racine->gauche->valeur) {
        return rotationDroite_s(racine);
    }

    // Cas de rotation à gauche
    if (balance < -1 && valeur > racine->droite->valeur) {
        return rotationGauche_s(racine);
    }

    // Cas de double rotation : gauche-droite
    if (balance > 1 && valeur > racine->gauche->valeur) {
        racine->gauche = rotationGauche_s(racine->gauche);
        return rotationDroite_s(racine);
    }

    // Cas de double rotation : droite-gauche
    if (balance < -1 && valeur < racine->droite->valeur) {
        racine->droite = rotationDroite_s(racine->droite);
        return rotationGauche_s(racine);
    }

    // Aucune rotation nécessaire, retourne le nœud courant
    return racine;
}

// Fonction récursive pour afficher les nœuds de l'arbre dans l'ordre décroissant
void AffichageDecroissant(Distance* racine, FILE* fichierSortie) {
    if (racine != NULL) {
        AffichageDecroissant(racine->droite, fichierSortie);
        // Écriture des informations du nœud dans le fichier de sortie
        fprintf(fichierSortie, "%d;%.3f;%.3f;%.3f;%.3f\n", racine->id, racine->min, racine->moy, racine->max, racine->valeur);
        AffichageDecroissant(racine->gauche, fichierSortie);
    }
}


// Fonction pour libérer la mémoire utilisée par l'arbre AVL
void libererMemoireAVL_s(Distance* racine) {
    if (racine != NULL) {
        // Libération récursive de la mémoire des nœuds
        libererMemoireAVL_s(racine->gauche);
        libererMemoireAVL_s(racine->droite);
        // Libération de la mémoire du nœud courant
        free(racine);
    }
}
