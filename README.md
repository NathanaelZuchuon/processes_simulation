# Simulation de Processus avec OpenGL (GLUT)

Ce projet simule l'exécution de processus utilisant différents algorithmes d'ordonnancement. Il est implémenté en C avec la bibliothèque OpenGL (GLUT) pour une visualisation graphique.

**Auteur :** Nathanael Zuchuon 3GI 2024-2025

**Algorithmes d'ordonnancement implémentés :**

* FCFS (First-Come, First-Served)
* PS (Priority Scheduling)
* RR (Round Robin)
* SJF (Shortest Job First)

## Fonctionnalités

* **Interface utilisateur graphique (GUI) :** L'application fournit une interface utilisateur intuitive basée sur GLUT pour sélectionner les algorithmes et visualiser la simulation.
* **Visualisation :** La simulation est représentée graphiquement, permettant de suivre l'exécution des processus.
* **Sélection d'algorithme :** L'utilisateur peut choisir l'algorithme d'ordonnancement à utiliser parmi les quatre implémentés.
* **Génération de processus :** L'application génère aléatoirement des processus avec des durées d'exécution variables. (Détails de la génération dans la section `Génération de processus`).
* **Gestion d'événements :** L'application gère les événements de clic de souris pour l'interaction utilisateur.

## Structure du code

Le code est organisé en plusieurs fichiers et dossiers pour une meilleure maintenabilité :

* **`include/algorithms/` :** Contient les implémentations des algorithmes d'ordonnancement (FCFS, PS, RR, SJF).
* **`include/algorithms/headVar.h` :** Fichier d'en-tête contenant les variables globales et les définitions.
* **`main.c` :** Contient la fonction `main` et la gestion principale de l'application GLUT.

## Compilation

Pour compiler le code, vous aurez besoin d'un compilateur C (comme GCC) et de la bibliothèque GLUT installée sur votre système. La commande de compilation peut varier légèrement selon votre environnement. Un exemple avec GCC :

```bash
cd bin | ./zuchuon_simulator.exe
```

Bibliothèques nécessaires:

* glut (OpenGL Utility Toolkit)
* GL (OpenGL)
* GLU (OpenGL Utility Library)
* m (mathématiques)

## Utilisation

1. Compilez le code comme indiqué ci-dessus.
2. Exécutez l'exécutable généré (processus_simulation).
3. Sélectionnez un algorithme d'ordonnancement.
4. Cliquez sur le bouton "START !" pour lancer la simulation.

## Génération de processus

La génération de processus est effectuée aléatoirement. Les paramètres suivants peuvent être modifiés dans le fichier headVar.h:

* NUM_PROCESSES: Le nombre de processus à générer.
* Autres paramètres de génération (durées d'exécution, priorités, etc.) sont potentiellement définis dans headVar.h.

## Limitations

* Simulation simplifiée: La simulation est une représentation simplifiée de l'ordonnancement de processus, ne prenant pas en compte certains aspects complexes des systèmes d'exploitation.
* Dépendance à GLUT: Le code dépend de la bibliothèque GLUT, qui peut ne pas être disponible sur tous les systèmes.

## Améliorations possibles

* Ajouter des fonctionnalités plus avancées, telles que la possibilité de modifier les paramètres des processus.
* Améliorer l'interface utilisateur pour une meilleure ergonomie.
* Implémenter d'autres algorithmes d'ordonnancement.
* Ajouter une documentation plus détaillée pour chaque fonction.

## Contact

Pour toute question ou suggestion, veuillez me contacter à <nzuchuon@gmail.com>.
