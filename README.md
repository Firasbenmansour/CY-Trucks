# **Cy-trucks**

Bienvenue dans le monde de Cy-trucks, votre outil avancé de gestion logistique pour les sociétés nationales de transport routier. Cet outil a été spécialement conçu pour simplifier l'analyse et la consolidation de données massives issues de fichiers CSV dans le domaine du transport routier.
Cy-trucks émerge comme une solution essentielle pour les gestionnaires de sociétés de transport qui cherchent à tirer des insights significatifs de leurs activités, tout en évitant la complexité inhérente aux données volumineuses et hétérogènes.

### ***Traitements Disponibles***
---
- TRAITEMENT [D1] : conducteurs avec le plus de trajets.
- TRAITEMENT [D2] : conducteurs et la plus grande distance.
- TRAITEMENT [L]  : les 10 trajets les plus longs.
- TRAITEMENT [T]  : les 10 villes les plus traversées.
- TRAITEMENT [S]  : statistiques sur les étapes.
  
### ***Dépendances***
---
Assurez-vous d'avoir les éléments suivants installés avant d'exécuter ce projet : <br />

- **gcc (GNU Compiler Collection)** : Utilisé pour la compilation du code source. <br />

- **gnuplot** : Utilisé pour la génération des histogrammes. <br />

- **convert (ImageMagick)** : Utilisé pour la manipulation d'images. <br />

- **make** : Utilisé pour la gestion de la construction du logiciel. <br />

#### ***Installation des Dépendances***

Si vous ne disposez pas déjà des dépendances nécessaires, vous pouvez les installer en utilisant les commandes suivantes : <br />
`sudo apt-get update` <br />
`sudo apt-get install gcc gnuplot imagemagick make` <br />

### ***Utilisation***
---
1. Enregistrez les fichiers dans un espace personnel.
2. Ajoutez le fichier de données que vous souhaitez analyser dans le dossier. Assurez-vous que le fichier de données soit au format CSV et nommé `data.csv`.
3. Ouvrez le Terminal.
4. Tapez `cd`, suivi d'un espace et de l'emplacement où les fichiers du programme sont enregistrés.
5. Tapez `chmod +x main.sh` pour modifier les droits d'exécution du fichier main.sh.
6. Enfin, tapez `./main.sh -option` pour lancer le programme, en remplaçant `option` par l'option spécifique que vous souhaitez utiliser. <br />
- les option disponibles : <br /> 
$~~~~~~~~~~~$`-h   :  aide` <br />
$~~~~~~~~~~~$`-d1  :  Exécuter le traitement D1` <br />
$~~~~~~~~~~~$`-d2  :  Exécuter le traitement D2` <br />
$~~~~~~~~~~~$`-l   :  Exécuter le traitement L` <br />
$~~~~~~~~~~~$`-s   :  Exécuter le traitement S` <br />
$~~~~~~~~~~~$`-t   :  Exécuter le traitement T` <br />

### ***Fichiers nécessaires***
---
#### *Dans le répertoire courant :* <br />
- `main.sh` <br />
- `d1.sh` <br />
- `d2.sh` <br />
- `l.sh` <br />
- `t.sh` <br />
- `s.sh` <br />
#### *Dans le dosssier progc :* <br />
- `s_avl.c` <br />
- `s_calcul.c` <br />
- `stats.c` <br />
- `stats.h` <br />
- `t_avl_nbTrajets.c` <br />
- `t_avl_ordreAlpha.c` <br />
- `ville.c` <br />
- `ville.h` <br />
- `Makefile` <br />
---
***Explorez et profitez pleinement des fonctionnalités de Cy-trucks pour simplifier la gestion logistique de votre entreprise.*** <br />
*Travail élaboré par le trinôme-MI5-I : BENMANSOUR Firas / MOUHAMADIMAME Tawfik / SOFACK KENFACK Berlyse Dafna*
