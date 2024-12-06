Les fichiers texte (.txt) des machines de Turing sont écrites de la même façon que sur le site turingmachinesimulator.com, sauf qu'on ne met pas de nom dans nos MT.

- left.txt est une MT qui permet de positionner la tête de lecture sur le dernier caractère de la bande.

- SEARCH.txt est une MT qui cherche le premier 0 ou 1 (selon la demande).

- ERASE.txt est une MT suprimer tous les caractères d'une bande pour laisser place à des blanc écrit '_'

- q5-copy.c est le fichier permettant la copie d'une bande i sur une bande j et permettant le support de SEARCH.txt et ERASE.txt.

- q5-search.c est le fichier permettant le support de SEARCH.txt.



Pour exécuter la question 5)LEFT  : Tapez: make q5LE       ;étant lié à la question ERASE, vous aurez accès aux deux exercises en même temps.
                            SEARCH: Tapez: make q5search
                            ERASE : Tapez: make q5LE
                            COPY  : Tapez: make q5copy

De plus toutes les informations nécessaires pour intéragir avec l'interface seront à votre disposition.



La fonction pour afficher la configuration de la MT est affichage_mt(MT mt) dans le fichier q5-copy.c et/ou q5-search.c, en fontion de la question.
La tête de lecture est montrée avec le caractère '^' 

Alexandre a travailler sur la question 7 et Brice sur la question 8.

q7.txt est le début de recherche d'un algorithme pour écrire une MT qui permet la mutiplication des x et y via la méthode égyptienne.

Q8.txt est le début de la machine de turing répondant a la question 8 elle n'est pas fonctionel.