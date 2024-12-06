import random


# revoie la valeur (s'il existe) de l'arête entre i et j
def arête(i, j):
    if (i < 1) or (i > 100) or (j < 1) or (j > 100):
        print("Erreur, un des nombres entrés n'est pas compris entre 1 et 100")
    else:
        if (liste[i - 1][j - 1] == 0):
            if (i == j):
                print("Vous avez sélectionné deux fois le sommet", i)
            print("Il n'y a pas d'arête entre les sommets", i, "et", j, )
        else:
            print("Arête du sommet", i, "à", j, "=", liste[i - 1][j - 1])


# renvoie la liste des voisins d'un sommet i
def voisins_sommet(i):
    if (i < 1) or (i > 100):
        print("Erreur, le nombre entré n'est pas compris entre 1 et 100")
    else:
        liste_voisins = []
        for j in range(100):
            if (liste[i - 1][j] > 0) and (i - 1 != j):  # ou (liste[j][i-1])
                liste_voisins += [j + 1]
        if (degré[i - 1] == 0):
            print("Le sommet", i, "n'a pas de voisin")  # normalement impossible
        else:
            print("Le sommet", i, "a", degré[i - 1], "voisins")
            print("La liste des voisins de ce sommet est:\n", liste_voisins)


# renvoie un chemin (s'il en existe) de i à j
def chemin_i_vers_j(i, j):
    if (i == j):
        print("Vous avez sélectionné deux fois le même sommet")
    else:
        chemin = [i]
        debut = i
        fin = 0
        while (fin != j):
            tmp = []  # liste temporaire des voisins d'un sommet qui ne sont pas dans le chemin final
            for k in range(1, 101):
                if (liste[debut - 1][k - 1] > 0) and (k in chemin) == False:
                    tmp += [k]
                    print(tmp)
                    if (j in tmp):
                        chemin += [j]
                        fin = j
                    fin = tmp[0]
                    chemin += [fin]
                    debut = fin

        print(chemin)


# partie 2.2
# le graphe est connexe si pour tout couple de sommets différents du graphe, il existe un chemin entre ces deux sommets
def verif_connexe():
    for i in range(1, 101):
        for j in range(i + 1, 101):
            chemin_i_vers_j(i, j)


# partie 2.3
# On utilise l'algorithme de Dijkstra:

# partie 2.4
def Dijkstra(i, j):
    nontraité = []
    valnontraité = []
    distances = [0] * 100
    origine = [0] * 100
    origine[i - 1] = -1
    chemin = [i]
    for j in range(100):
        if (j != i):
            nontraité += [j + 1]
            valnontraité += liste[i - 1][j]
    for k in nontraité:
        min = valnontraité[0]
        for l in nontraité[k + 1:len(nontraité)]:
            if valnontraité[l] < valnontraité[k]:
                min = valnontraité[l]
    for j in range(100):
        distances[j] = liste[i - 1][j]

    print("Le plus court chemin entre les noeuds", distances[j - 1])


# initialisation d'une matrice représentant l'ensemble des connexions entre chaque sommet, tous les éléments de la matrice sont initialisés à 0

liste = [[0] * 100 for _ in range(100)]

# initialisation d'un tableau contenant le degré de chaque sommet
degré = [0] * 100

# niveau 1: backbone (sommets 1 à 10)
for i in range(10):
    for j in range(i + 1, 10):
        alea = random.randint(1,
                              4)  # si alea est différent de 1, alors on crée l'arête de i à j (75% de chances que l'arête soit créée)
        if (alea != 1):
            degré[j] += 1
            degré[i] += 1
            liste[i][j] = random.randint(5, 10)
            liste[j][i] = liste[i][j]

# niveau 2: transit (sommets 11 à 30)
for i in range(10, 30):
    liste2_1 = random.sample(range(10), random.randint(1, 2))
    while (i in liste2_1) == True:  # si un élément de la liste est égal à i alors on change toute la liste
        liste2_1 = random.sample(range(10), random.randint(1, 2))
    for j in liste2_1:
        degré[j] += 1
        degré[i] += 1
        liste[i][j] = random.randint(11, 20)
        liste[j][i] = liste[i][j]

    liste2_2 = random.sample(range(10, 30), random.randint(2, 3))
    while (i in liste2_2) == True:
        liste2_2 = random.sample(range(10, 30), random.randint(2, 3))
    for j in liste2_2:
        degré[j] += 1
        degré[i] += 1
        liste[i][j] = random.randint(10, 20)
        liste[j][i] = liste[i][j]

# niveau 3 (sommets 31 à 100)
for i in range(30, 100):
    liste3_2 = random.sample(range(11, 30), 2)
    while (i in liste3_2) == True:
        liste3_2 = random.sample(range(11, 30), 2)
    for j in liste3_2:
        degré[j] += 1
        degré[i] += 1
        liste[i][j] = random.randint(15, 50)
        liste[j][i] = liste[i][j]

    liste3_3 = random.sample(range(31, 100), 1)
    while (i in liste3_3) == True:
        liste3_3 = random.sample(range(31, 100), 1)
    for j in liste3_3:
        degré[j] += 1
        degré[i] += 1
        liste[i][j] = random.randint(15, 50)
        liste[j][i] = liste[i][j]

print("Voici le menu principal:")
print("1: Liste des voisins d'un sommet")
print("2: Poids d'une arête entre deux sommets (si elle existe)")
print("3: Renvoie s'il existe un chemin entre deux sommets")
print("4: Plus court chemin entre deux sommets avec la méthode de Dijkstra")
print("0: Quitter (ATTENTION, toutes les informations seront perdues)")

n = 0
while (1):
    n = int(input("\nVeuillez entrer un nombre: "))
    if n == 1:
        i = int(input("Quel sommet ? "))
        voisins_sommet(i)
    elif n == 2:
        i = int(input("Sommet origine: "))
        j = int(input("Sommet destination: "))
        arête(i, j)
    elif n == 3:
        i = int(input("Sommet origine: "))
        j = int(input("Sommet destination: "))
        chemin_i_vers_j(i, j)
    elif n == 4:
        i = int(input("Sommet origine: "))
        j = int(input("Sommet destination: "))
        Dijkstra(i, j)
    elif n == 0:
        print("Vous avez quitté le menu principal.")
        exit(0)
    else:
        print("Erreur, vous n'avez pas sélectionné un nombre valide.")