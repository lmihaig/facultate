import random
from itertools import chain, cycle
import numpy as np


def clip(x, l, u):
    return max(l, min(u, x))


class Elev:
    _i = 1
    _activitati_posibile = {}

    def __init__(self, nume=None, sanatate=90, inteligenta=20, oboseala=0, buna_dispozitie=100, lista_activitati=[]):
        if nume:
            self.nume = nume
        else:
            self.nume = f"Necunoscut_{self.__class__._i}"
            self.__class__._i += 1
        self.sanatate = sanatate
        self.inteligenta = inteligenta
        self.oboseala = oboseala
        self.buna_dispozitie = buna_dispozitie
        self.lista_activitati = lista_activitati
        self.activitate_curenta = None

    def __repr__(self) -> str:
        return str(self.__dict__)

    def __str__(self) -> str:
        return f"{self.nume} {self.activitate_curenta} {self.timp_executat_activ+1}/{self.__class__._activitati_posibile[self.activitate_curenta].durata} (snt: {self.sanatate}, intel: {self.inteligenta}, obos: {self.oboseala}, dispoz: {self.buna_dispozitie})"

    def incepe_activitate(self, activitate):
        self.activitate_curenta = activitate
        self.timp_executat_activ = 0

    def trece_ora(self, ora_curenta):
        if self.activitate_curenta:
            pass
        else:
            act = self.lista_activitati.pop(0)
            self.lista_activitati.append(act)
            self.incepe_activitate(act)

        actv = self.__class__._activitati_posibile[self.activitate_curenta]
        d = actv.durata

        self.timp_executat_activ += 1

        fo = actv.factor_oboseala
        fs = actv.factor_sanatate
        fi = actv.factor_inteligenta
        fd = actv.factor_dispozitie

        if not (ora_curenta >= 6 and ora_curenta <= 22) and self.activitate_curenta != "dormit":
            self.sanatate = clip(self.sanatate-1, 0, 100)

        self.oboseala = clip(self.oboseala + fo, 0, 100)
        aport = 0.5 if self.oboseala == 100 else 1

        for stat, modif in zip([self.sanatate, self.inteligenta, self.buna_dispozitie], [fs, fi, fd]):
            if modif > 0:
                stat = clip(stat + modif*aport, 0, 100)
            else:
                stat = clip(stat + modif, 0, 100)

        self.sanatate = newstat(self.sanatate, fs, aport)
        self.inteligenta = newstat(self.inteligenta, fi, aport)
        self.buna_dispozitie = newstat(self.buna_dispozitie, fd, aport)

        if self.timp_executat_activ == d:
            if self.lista_activitati:
                self.incepe_activitate(self.lista_activitati.pop(0))
            else:
                return False

        return True

    def testeaza_final(self):
        if self.sanatate == 0:
            return True, f"Elevul {self.nume} este bolnav"
        if self.buna_dispozitie == 0:
            return True, f"Elevul {self.nume} a dat in depresie"
        if self.inteligenta == 100:
            return True, f"Elevul {self.nume} a absolvit scoala!"
        return False, ""


def newstat(stat, modif, aport):
    if modif > 0:
        stat = int(clip(stat + modif*aport, 0, 100))
    else:
        stat = clip(stat + modif, 0, 100)
    return stat


class Activitate:
    def __init__(self, factor_sanatate, factor_inteligenta, factor_oboseala, factor_dispozitie, durata):
        self.factor_sanatate = factor_sanatate
        self.factor_inteligenta = factor_inteligenta
        self.factor_oboseala = factor_oboseala
        self.factor_dispozitie = factor_dispozitie
        self.durata = durata


def get_activitati_random(num):
    activitati = []
    num_h = 0
    # nu va fi FIX num ore fiindca enervant
    while num_h < num:
        act = random.choice(list(Elev._activitati_posibile.keys()))
        num_h += Elev._activitati_posibile[act].durata
        activitati.append(act)
    return activitati


def porneste_simulare(elevi):
    skip = 0
    ore = [i for i in range(9, 24)] + [i for i in range(9)]
    dead = 0
    for ora in cycle(ore):
        if not elevi:
            print("s-a terminat")
            break
        print(f"Ora: {ora}:00")
        for elev in elevi:
            if elev.trece_ora(ora):
                print(elev)
                with open(f"raport_{elev.nume}.txt", "a") as f:
                    f.write(str(elev))
                    f.write("\n")
        num_elevi = len(elevi)
        new_elevi = []

        for elev in elevi:
            ended, message = elev.testeaza_final()
            if not ended:
                if elev.lista_activitati:
                    new_elevi.append(elev)
            else:
                with open(f"raport_{elev.nume}.txt", "a") as f:
                    f.write(message)
                    f.write("\n")

        elevi = new_elevi
        if dead and num_elevi != len(elevi):
            dead = 0
            skip = 0
        elif dead:
            skip = 1

        if skip:
            skip -= 1
        else:
            match input("comanda=").split():
                case ["c", "final_elev"]: dead = 1
                case ["c", i]: skip = max(0, int(i))
                case ["c"]: continue
                case ["b"]: break
                case x: print(f"{x} nu este o comanda")

    return True


# confuz daca asta cere cerinta prin "statica"?
with open("activitati.txt", "r") as f:
    lines = f.readlines()[1:]
    lines = [line.strip().split() for line in lines]
    for line in lines:
        Elev._activitati_posibile[line[0]] = Activitate(*[int(i) for i in line[1:]])

with open("elevi.txt", "r") as f:
    lines = f.readlines()
nr_elevi, ore_default = [int(i) for i in lines[0].strip().split()]
lines = lines[1:]
elevi = []
i = 1
for line in lines:
    line = line.split()
    date = line[1:4]
    activitati = line[5:]
    match_activitate = activitati[0]
    lista_act = []

    # nu am implementat random(numar) si random(lista activitati) fiindca enervant
    # am modificat inputul in elevi.txt
    match match_activitate:
        case 'random': lista_act = get_activitati_random(ore_default)
        # case '':
        # case '':
        case _: lista_act = list(chain.from_iterable([[act]*int(i) for act, i in zip(activitati[0::2], activitati[1::2])]))
    elevi.append(Elev(line[0], lista_activitati=lista_act, *[int(i) for i in date]))
    i += 1


for _ in range(i, nr_elevi+1):
    elevi.append(Elev(lista_activitati=get_activitati_random(ore_default)))

if __name__ == '__main__':
    porneste_simulare(elevi)
