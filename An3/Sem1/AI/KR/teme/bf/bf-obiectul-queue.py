import itertools
import random
from collections import deque
import cProfile
import string

# informatii despre un nod din arborele de parcurgere (nu din graful initial)

"""ENUNT:
Implementati BF folosind un obiect de tip Queue din Python si afisati toate solutiile. Scoateti apelurile de tip print al cozii si input din programul dat la laborator. Comparati cu cProfile programul vostru si cel dat la laborator. Ce structura e mai eficienta? Observatie: daca diferentele de timp sunt prea mici, mariti numarul de noduri si de muchii in matricea de adiacenta.
"""


class NodParcurgere:
    def __init__(self, id, info, parinte):
        self.id = id  # este indicele din vectorul de noduri
        self.info = info
        self.parinte = parinte  # parintele din arborele de parcurgere

    def obtineDrum(self):
        l = [self.info]
        nod = self
        while nod.parinte is not None:
            l.insert(0, nod.parinte.info)
            nod = nod.parinte
        return l

    def afisDrum(self):  # returneaza si lungimea drumului
        l = self.obtineDrum()
        # print("----> Solutie:" + ("->").join(l))
        # print("Lungime:", len(l)-1)
        # print("\n")
        return len(l)

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if (infoNodNou == nodDrum.info):
                return True
            nodDrum = nodDrum.parinte

        return False

    def __repr__(self):
        sir = ""
        sir += self.info+"("
        sir += "id = {}, ".format(self.id)
        sir += "drum="
        drum = self.obtineDrum()
        sir += ("->").join(drum)
        sir += ")"
        return (sir)


class Graph:  # graful problemei
    def __init__(self, noduri, matrice, start, scopuri):
        self.noduri = noduri
        self.matrice = matrice
        self.nrNoduri = len(matrice)
        self.start = start
        self.scopuri = scopuri

    def indiceNod(self, n):
        return self.noduri.index(n)

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def genereazaSuccesori(self, nodCurent):
        listaSuccesori = []
        for i in range(self.nrNoduri):
            if self.matrice[nodCurent.id][i] == 1 and not nodCurent.contineInDrum(self.noduri[i]):
                nodNou = NodParcurgere(i, self.noduri[i], nodCurent)
                listaSuccesori.append(nodNou)
        return listaSuccesori

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return (sir)


##############################################################################################
#                                 Initializare problema                                      #
##############################################################################################

# pozitia i din vectorul de noduri da si numarul liniei/coloanei corespunzatoare din matricea de adiacenta


# bodge de generare de grafuri
NUM = 5000
noduri = ["".join(i) for i in itertools.product(string.ascii_lowercase, repeat=4)][:NUM]
m = [[0 for i in range(NUM)] for j in range(NUM)]

opt = [0, 1]

for i in range(NUM):
    for j in range(NUM):
        if i != j:
            m[i][j] = random.choice(opt)


start = noduri[0]
NR_SOLUTII = 5
scopuri = [random.choice(noduri) for i in range(NR_SOLUTII)]
gr = Graph(noduri, m, start, scopuri)


# algoritm BF
# presupunem ca vrem mai multe solutii (un numar fix)
# daca vrem doar o solutie, renuntam la variabila nrSolutiiCautate
# si doar oprim algoritmul la afisarea primei solutii


def breadth_first(gr):
    global nrSolutiiCautate
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.noduri.index(start), start, None)]
    continua = True  # variabila pe care o setez la false cand consider ca s-au afisat suficiente solutii
    while (len(c) > 0 and continua):
        # print("Coada actuala: " + str(c))
        nodCurent = c.pop(0)
        # print(f"Se extinde nodul {nodCurent.info} din drumul {nodCurent.obtineDrum()}")

        if nodCurent.info in scopuri:
            nodCurent.afisDrum()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                continua = False
        lSuccesori = gr.genereazaSuccesori(nodCurent)
        # print(f"Se adauga in coada: {[l.info for l in lSuccesori]}")

        c.extend(lSuccesori)


def fast_bfs(gr):
    global nrSolutiiCautate
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = deque()
    c.append(NodParcurgere(gr.noduri.index(start), start, None))
    continua = True  # variabila pe care o setez la false cand consider ca s-au afisat suficiente solutii
    while (len(c) > 0 and continua):
        # print("Coada actuala: " + str(c))
        nodCurent = c.popleft()
        # print(f"Se extinde nodul {nodCurent.info} din drumul {nodCurent.obtineDrum()}")

        if nodCurent.info in scopuri:
            nodCurent.afisDrum()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                continua = False
        lSuccesori = gr.genereazaSuccesori(nodCurent)
        # print(f"Se adauga in coada: {[l.info for l in lSuccesori]}")

        c.extend(lSuccesori)


nrSolutiiCautate = NR_SOLUTII
cProfile.run("breadth_first(gr)")

nrSolutiiCautate = NR_SOLUTII
cProfile.run("fast_bfs(gr)")


"""
         29172029 function calls in 30.388 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.405    0.405   30.388   30.388 <string>:1(<module>)
  9717959    1.550    0.000    1.550    0.000 bf-obiectul-queue.py:11(__init__)
        1    0.058    0.058   29.983   29.983 bf-obiectul-queue.py:110(breadth_first)
        5    0.000    0.000    0.000    0.000 bf-obiectul-queue.py:16(obtineDrum)
        5    0.000    0.000    0.000    0.000 bf-obiectul-queue.py:24(afisDrum)
  9720524    2.795    0.000    2.795    0.000 bf-obiectul-queue.py:31(contineInDrum)
     3890   13.454    0.003   18.441    0.005 bf-obiectul-queue.py:63(genereazaSuccesori)
        1    0.000    0.000   30.388   30.388 {built-in method builtins.exec}
     3896    0.002    0.000    0.002    0.000 {built-in method builtins.len}
  9717958    0.642    0.000    0.642    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
     3890    0.196    0.000    0.196    0.000 {method 'extend' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'index' of 'list' objects}
        7    0.000    0.000    0.000    0.000 {method 'insert' of 'list' objects}
     3890   11.286    0.003   11.286    0.003 {method 'pop' of 'list' objects}


DEQUE

         29172030 function calls in 18.334 seconds
   Ordered by: standard name
   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.374    0.374   18.334   18.334 <string>:1(<module>)
  9717959    1.529    0.000    1.529    0.000 bf-obiectul-queue.py:11(__init__)
        1    0.039    0.039   17.959   17.959 bf-obiectul-queue.py:131(fast_bfs)
        5    0.000    0.000    0.000    0.000 bf-obiectul-queue.py:16(obtineDrum)
        5    0.000    0.000    0.000    0.000 bf-obiectul-queue.py:24(afisDrum)
  9720524    2.782    0.000    2.782    0.000 bf-obiectul-queue.py:31(contineInDrum)
     3890   12.889    0.003   17.835    0.005 bf-obiectul-queue.py:63(genereazaSuccesori)
        1    0.000    0.000   18.334   18.334 {built-in method builtins.exec}
     3896    0.001    0.000    0.001    0.000 {built-in method builtins.len}
        1    0.000    0.000    0.000    0.000 {method 'append' of 'collections.deque' objects}
  9717958    0.635    0.000    0.635    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
     3890    0.083    0.000    0.083    0.000 {method 'extend' of 'collections.deque' objects}
        1    0.000    0.000    0.000    0.000 {method 'index' of 'list' objects}
        7    0.000    0.000    0.000    0.000 {method 'insert' of 'list' objects}
     3890    0.001    0.000    0.001    0.000 {method 'popleft' of 'collections.deque' objects}
"""
