<th align="center">Projet IN620 – Métasimulation: </h1>



# Objectifs: Vous donnerez un fichier README qui explique comment utiliser votre code

Dans ce fichier, nous aurons à utiliser les instructions suivantes:
Ici A,B,R représentent chacun un entier naturel appartenant à l'ensemble N.
Ici X représente un entier relatif appartenant à l'ensemble Z.

1) Instructions arithmétiques :

ADD |   A,B,R   |  L'opération additionne A + B et le stock dans R
SUB |   A,B,R   |  L'opération soustraite A - B et le stock dans R
MUL |   A,B,R   |  L'opération multiplie  A * B et le stock dans R
DIV |   A,B,R   |  L'opération additionne A / B et le stock dans R

2) Instruction de contrôle :

JUMP|     X     |  Ici on utilise la valeur de X pour déterminer le nombre d'instruction à sauter
JE  |   A,B,X   |  Ici si A égale à B, on saute de X instructions
JL  |   A,B,X   |  Ici si A supérieur à B, on saute de X instructions



# Fonctionnement


Pour faire fonctionné le Programme machine RAM , nous allons utilisé plusieurs fichier afin de stocker et transformé l'information que nous souhaiton traité.
De plus nous allons utiliser des étapes spécifiques au traitement de l'information qui sont appelés des registres:

1) Liste des fichiers Utilisé:

   Ici les fichiers déjà présents avant la compilation:
    Partie 1:
    - Makefile      |  Permet l'automatisation de la compilation de l'enssemble du programme
    - RamProject.py |  Code en python comprenant les fonction du programme et permettant les calculs
    - regexp.l      |  Stock du code en lex permetant de définir la grammaire de travail du programme
    - regexp.y      |  Stock du code en yacc permetant de donner du contexte à la grammaire du lex
    - texteInput    |  Stockage des caractères initiaux ``qui seront traité par le Makefile``et autres fichiers
    
    - Tests Folder  |  Ficher stockant tous les exemples utilisés pour répondre aux questions

    - ex-a^b        |  Stockage des entiers a et b qui seront calculés en a exposant b soit: a^b                question 5
    - ex-triBulle   |  Stockage d'entiers seront triés via un tri à bulles

    Partie 2:
    - automate.jpg          |  Représentation graphique de l'automate                                           question 6
    Par ailleur je me suis aidé de chat GPT et copilote pour générer ces deux exemples.
    - ex-automateViable     |  Stockage des valeurs pour résoudre l'automate a^n_b^n                            question 7
    - ex-automateNonViable  |  Stockage des valeurs pour échouer à l'automate a^n_b^n

   Ici les fichiers présents après la compilation, généré par l'utilisation des fichiers Lex et Yacc:
    - regexp.output
    - regexp.tab.h
    - regexp.tab.c
    - regexp
    - main.py

2) Liste des fichiers Utilisé:

    - Registre d'entrée synthéthisé par **I** pour input, c'est ici que les donnée seront initialement stockés.

    - Registre de travail synthéthisé par **R** car il est le registre qui fait le lien entre **I** et **O** en stockant temporairement les valeurs transitoires.

    - Registre de sortie synthéthisé par **O** pour output, c'est ici que les données finale seront stockés.


3) Pour l'automate:

    - q = état initial
    - a = valeur lu
    - A = valeur sommet pille
    - Nbr = taille de w / si w= 2 alors on PUSH / si w= 1 on POP / si w=0 on ACCEPT ou REJECT
    - w = mot a mettre ou retirer de la pile
    - q'= état final

    - La représentation choisis dans les ex-automate.txt suit la demande faite dans les consigne Partie 2:
        - En stockant d’abord le nombre de transitions
        - Puis en stockant la taille du mot à traiter avec son caractère balise
        - Puis dans l'ordre les transitions nécessaire à la résolution du problème

    - L'affichage du résultat fonctionne de la même manière que les autres automates excepté que: 
        - Si l'automate est Viable il affichera:    O O0 : 1 || O1 : 1      cela signfie que pour l'Output O0 nous reconnaissons 1 valeur sur 01 qui est 1 = cela veut dire que la pile n'est pas vide et donc qu'il n'y a pas autant de a^n que de b^n à la suite.
        - Si l'automate est nonViable il affichera: O O0 : 1 || O1 : 0      cela signite à contrario que la pile est vide donc on a pu PUSH tout les a à la suite et puis les POP grâce aux B à la suite.

# Instruction

1. Vous devez tout d'abord choisir le texte à traiter par la machine en l'insérant dans le fichier ``textEntrance.1`` en utilisant les exemples précontruirs ou en les créants sous la forme:

valeur0=Taille de l'entrée, valeur 1 , valeur 2, ..., etc, ...; valeur finale
Première Instruction arithmétiques / de contrôle
.
.
etc
.
Dernière Instruction arithmétiques / de contrôle
----------------------------------------------------- 
Ce qui donne avec un exemple :

2,2,5
ADD(0,1,O0)
ADD(0,0,R0)
JE(R0,I2,3)
MUL(O0,I1,O0)
ADD(R0,1,R0)
JUMP(-2)

2. Pour éxécuter le programme veuillez écrire dans le terminal ``make`` 
3. Si vous souhaitez nettoyer les fichiers générés après compilation veuillez écrire ``make clean``
4. Si vous souhaitez nettoyer l'interface du Terminal veuillez écrire ``clear`` ou maintenir ``ctrl + L``