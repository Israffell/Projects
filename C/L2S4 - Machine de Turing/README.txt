Les fichiers texte (.txt) des machines de Turing sont écrites de la même façon que sur le site turingmachinesimulator.com, sauf qu'on ne met pas de nom dans nos MT.

- mt1.txt est une MT qui renvoie le complémentaire du mot d'entrée (transforme les 0 en 1 et vice-versa)

- mt2.txt est une MT qui accepte les mots ayant un nombre pair de 0

- mt3.txt est une MT qui accepte les mots du langage (01*0), c'est-à-dire les mots commençant et se terminant par un 0, sans autre 0 ailleurs et ayant potentiellement mais uniquement des 1 entre les deux 0  

La structure MT est écrite dans le fichier mt.h
La fonction pour afficher la configuration de la MT est affichage_mt(MT mt) dans le fichier mt.c: la tête de lecture est montrée avec le caractère '^' 


Thomas a fait la question 6 et Alexandre a fait la question 7.

mtq6.txt est une MT qui accepte les mots du language 0.1^n et renvoie 1^n.0 (n appartient à N)
son équivalent en MT à ruban infini simple serait que lorsque la tête de lecture est sur le 0 en venant de droite,
il décalerait tout les caractères à droite du 0 compris 

mtq7.txt est une MT qui transforme le mot d'entrée d'alphabet {a,b,c,d}
en mot de la forme d^|n| avec n le nombre de lettres du mot d'entrée
