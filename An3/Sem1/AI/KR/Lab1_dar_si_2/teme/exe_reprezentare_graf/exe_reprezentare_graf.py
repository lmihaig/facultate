import collections
import json
from pprint import pprint


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

