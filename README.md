# C-Fetch 

Un outil en ligne de commande (CLI) minimaliste inspiré de [Neofetch](https://github.com/dylanaraps/neofetch), écrit entièrement en **C**.

Ce programme affiche les informations de base du système (OS, Kernel, Uptime, CPU, RAM) accompagnées d'un logo ASCII, directement dans le terminal.
Cet outil ne fonctionne que sur une distribution Linux.

## Contexte du projet

L'objectif principal n'était pas de remplacer Neofetch, mais de comprendre :
* La syntaxe et la logique du langage **C**.
* La manipulation des fichiers systèmes (parsing de `/proc/cpuinfo`, `/proc/meminfo`, etc.).
* La gestion des chaînes de caractères et de la mémoire.

> **Note :** Étant en cours d'apprentissage, le code est perfectible et sujet à améliorations.

## Fonctionnalités

- [X] Affichage de l'OS et du Kernel
- [X] Calcul de l'Uptime
- [X] Modèle de CPU
- [] (À venir) Utilisation du CPU
- [X] Utilisation de la RAM
- [] (À venir) Détection du Shell et du WM

## Installation & Utilisation

Pour tester le projet :

1. Clonez le repo :
   ```bash
   git clone [hhttps://github.com/lvlDylan/newfetch.git](https://github.com/lvlDylan/newfetch.git)
   cd newfetch
   ```