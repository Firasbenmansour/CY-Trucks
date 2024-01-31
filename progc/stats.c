#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

int hash(int id_trajet, int max_trajets) {
    return id_trajet % max_trajets;
}

void updateTrajetInfo(TrajetInfo *info, double distance) {
    if (distance < info->min_distance || info->nombre_etapes == 0) {
        info->min_distance = distance;
    }
    if (distance > info->max_distance) {
        info->max_distance = distance;
    }
    info->moyenne_distance += distance;
    info->nombre_etapes++;  
}

int lireNombreMaxTrajets() {
    FILE *nombreTrajetsFile = fopen("temp/nombre_trajets.txt", "r");
    if (nombreTrajetsFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de nombre de trajets");
        exit(EXIT_FAILURE);
    }

    int max_trajets;
    if (fscanf(nombreTrajetsFile, "%d", &max_trajets) != 1) {
        perror("Erreur lors de la lecture du nombre de trajets");
        exit(EXIT_FAILURE);
    }

    fclose(nombreTrajetsFile);
    return max_trajets;
}
void lireEtTraiterDonnees(FILE *inputFile, Trajet **trajets, int max_trajets) {
    char buffer[MAX_BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        int id_trajet;
        double distance;
        sscanf(buffer, "%d;%lf", &id_trajet, &distance);

        int index = hash(id_trajet, max_trajets);

        if (trajets[index] == NULL) {
            trajets[index] = malloc(sizeof(Trajet));
            trajets[index]->id_trajet = id_trajet;
            memset(&trajets[index]->info, 0, sizeof(TrajetInfo));
        }

        updateTrajetInfo(&trajets[index]->info, distance);
    }
}

void ecrireResultats(FILE *outputFile, Trajet **trajets, int max_trajets) {
    for (int i = 0; i < max_trajets; i++) {
        if (trajets[i] != NULL) {
            TrajetInfo *info = &trajets[i]->info;
            if (info->nombre_etapes > 0) {
                info->moyenne_distance /= info->nombre_etapes;
                double difference_max_min = info->max_distance - info->min_distance;
                fprintf(outputFile, "%d;%.2f;%.2f;%.2f;%.2f\n", trajets[i]->id_trajet,
                        info->min_distance, info->moyenne_distance, info->max_distance, difference_max_min);
            }
            free(trajets[i]);
        }
    }
}

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
