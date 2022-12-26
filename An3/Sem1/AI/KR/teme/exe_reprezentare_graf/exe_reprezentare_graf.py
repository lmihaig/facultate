import collections
import json
from pprint import pprint


"""ENUNT:
Exercitiu de intelegere a reprezentarii unui graf.

Scrieti un program in care porniti de la matricea de adiacenta (se va citi din fisier), si obtineti lista de noduri si de muchii/arce asociate unui graf oarecare (veti scrie cele doua liste in fisier). In plus, afisati in consola daca matricea de adiacenta poate fi a unui graf neorientat sau nu. Faceti si transformarea inversa (de la lista de noduri si muchii la matricea de adiacenta).

Faceti acelasi lucru si pentru liste de vecini: trecerea de la matrice de adicenta la lista de vecini, trcerea de la lista de vecini la matrice de adiacenta.

Pe langa program(e), se vor uploada si fisierele de input si output (numele lor trebuie sa indice daca sunt de input sau output). In fisierul de input trebuie sa fie descris un graf de macar 7 noduri dintre care unul izolat. Se va uploada si un desen cu graful (de exemplu facut in paint sau desenta si fotografiat).
"""


def adiacenta_to_graf(matrice):
    neorientat = True

    for i in range(len(matrice)):
        for j in range(len(matrice)):
            if matrice[i][j]:
                if not matrice[j][i]:
                    neorientat = False

    muchii = []
    for i in range(len(matrice)):
        for j in range(len(matrice)):
            if matrice[i][j]:
                if neorientat:
                    if (j, i) not in muchii:
                        muchii.append((i, j))
                else:
                    muchii.append((i, j))

    graf = {
        "noduri": [i for i in range(len(matrice))],
        "muchii": muchii
    }

    if neorientat:
        print("Graful este neorientat")
    else:
        print("Graful este orientat")
    return graf, neorientat


def graf_to_adiacenta(graf, neorientat=True):
    nr_noduri = len(graf['noduri'])
    matrice = [[0 for i in range(nr_noduri)] for j in range(nr_noduri)]

    for i, j in graf['muchii']:
        matrice[i][j] = 1
        if neorientat:
            matrice[j][i] = 1

    return matrice


def adiacenta_to_vecini(matrice):
    graf = {i: [] for i in range(len(matrice))}
    for i in range(len(matrice)):
        for j in range(len(matrice)):
            if matrice[i][j]:
                graf[i].append(j)
    return graf


def vecini_to_adiacenta(graf):
    nr_noduri = len(graf.keys())
    matrice = [[0 for i in range(nr_noduri)] for j in range(nr_noduri)]

    for k, v in graf.items():
        for nod in v:
            matrice[k][nod] = 1

    return matrice


if __name__ == "__main__":
    matrice = open("m_adiacenta.txt", "r").readlines()
    matrice = [l.strip() for l in matrice]
    matrice = [[int(i) for i in l.split()] for l in matrice]

    graf, neorientat = adiacenta_to_graf(matrice)
    with open("graf.txt", "w") as f:
        for nod in graf["noduri"]:
            f.write(f"{nod} ")
        f.write("\n")
        for muchie in graf["muchii"]:
            f.write(f"{muchie} ")
    print("Matrice din fisier:\t", matrice)
    print("Graf:", graf)

    # citit din fisier?
    new_matrice = graf_to_adiacenta(graf, neorientat)
    print("Matrice din graf:\t", new_matrice)

    graf_vecini = adiacenta_to_vecini(matrice)
    print("Graf vecini:", graf_vecini)

    new_matrice = vecini_to_adiacenta(graf_vecini)
    print("Matrice din vecini:\t", new_matrice)
