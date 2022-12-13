

# informatii despre un nod din arborele de parcurgere (nu din graful initial)
import cProfile
from collections import deque
import itertools
from queue import LifoQueue
import random
import string


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
        # print(("->").join(l))
        # print("Lungime drum:", len(l)-1)
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
NUM = 1000
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

# =====================================================================================================================
# algoritm DFI
# presupunem ca vrem mai multe solutii (un numar fix)
# daca vrem doar o solutie, renuntam la variabila nrSolutiiCautate
# si doar oprim algoritmul la afisarea primei solutii


def depth_first_callstack(gr, nrSolutiiCautate):
    # vom simula o stiva prin relatia de parinte a nodului curent
    df_callstack(NodParcurgere(gr.noduri.index(start), start, None), nrSolutiiCautate, True)


def df_callstack(nodCurent, nrSolutiiCautate, continua):
    if not continua:
        return
    if nodCurent.info in scopuri:
        nodCurent.afisDrum()
        nrSolutiiCautate -= 1
        if nrSolutiiCautate == 0:
            continua = False
    lSuccesori = gr.genereazaSuccesori(nodCurent)
    for sc in lSuccesori:
        df_callstack(sc, nrSolutiiCautate, continua)


def depth_first_lista(gr, nrSolutiiCautate):
    stack = [NodParcurgere(gr.noduri.index(start), start, None)]
    visited = set()
    cont = True
    while stack and cont:
        node = stack.pop()

        if node.info in scopuri:
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                cont = False

        if node.info in visited:
            continue

        visited.add(node.info)
        for neighbor in gr.genereazaSuccesori(node):
            stack.append(neighbor)


def depth_first_deque(gr, nrSolutiiCautate):
    stack = deque()
    stack.append(NodParcurgere(gr.noduri.index(start), start, None))
    visited = set()
    cont = True
    while stack and cont:
        node = stack.pop()

        if node.info in scopuri:
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                cont = False

        if node.info in visited:
            continue

        visited.add(node.info)
        for neighbor in gr.genereazaSuccesori(node):
            stack.append(neighbor)


def depth_first_lifoqueue(gr, nrSolutiiCautate):
    stack = LifoQueue()
    stack.put(NodParcurgere(gr.noduri.index(start), start, None))
    visited = set()
    cont = True
    while not stack.empty() and cont:
        node = stack.get()

        if node.info in scopuri:
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                cont = False

        if node.info in visited:
            continue

        visited.add(node.info)
        for neighbor in gr.genereazaSuccesori(node):
            stack.put(neighbor)


# print("TARGET=", scopuri)
# print("============ DF CALLSTACK ============")
# cProfile.run("depth_first_callstack(gr, NR_SOLUTII)")

print("============ DF LISTA ============")
cProfile.run("depth_first_lista(gr, NR_SOLUTII)")


print("============ DF DEQUE ============")
cProfile.run("depth_first_deque(gr, NR_SOLUTII)")


print("============ DF LIFOQUEUE ============")
cProfile.run("depth_first_lifoqueue(gr, NR_SOLUTII)")


"""
============ DF LISTA ============
         1200619 function calls in 11.311 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.009    0.009   11.311   11.311 <string>:1(<module>)
        1    0.037    0.037   11.302   11.302 comparatie-implementari-df.py:126(depth_first_lista)
   247732    0.042    0.000    0.042    0.000 comparatie-implementari-df.py:13(__init__)
   454690   10.777    0.000   10.777    0.000 comparatie-implementari-df.py:32(contineInDrum)
      910    0.408    0.000   11.249    0.012 comparatie-implementari-df.py:64(genereazaSuccesori)
        1    0.000    0.000   11.311   11.311 {built-in method builtins.exec}
      910    0.000    0.000    0.000    0.000 {method 'add' of 'set' objects}
   495462    0.038    0.000    0.038    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        1    0.000    0.000    0.000    0.000 {method 'index' of 'list' objects}
      910    0.000    0.000    0.000    0.000 {method 'pop' of 'list' objects}


============ DF DEQUE ============
         1200620 function calls in 11.290 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.009    0.009   11.290   11.290 <string>:1(<module>)
   247732    0.042    0.000    0.042    0.000 comparatie-implementari-df.py:13(__init__)
        1    0.036    0.036   11.282   11.282 comparatie-implementari-df.py:146(depth_first_deque)
   454690   10.754    0.000   10.754    0.000 comparatie-implementari-df.py:32(contineInDrum)
      910    0.414    0.000   11.231    0.012 comparatie-implementari-df.py:64(genereazaSuccesori)
        1    0.000    0.000   11.290   11.290 {built-in method builtins.exec}
      910    0.000    0.000    0.000    0.000 {method 'add' of 'set' objects}
   247732    0.014    0.000    0.014    0.000 {method 'append' of 'collections.deque' objects}
   247731    0.021    0.000    0.021    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        1    0.000    0.000    0.000    0.000 {method 'index' of 'list' objects}
      910    0.000    0.000    0.000    0.000 {method 'pop' of 'collections.deque' objects}


============ DF LIFOQUEUE ============
         3443868 function calls in 12.114 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.009    0.009   12.114   12.114 <string>:1(<module>)
   247732    0.042    0.000    0.042    0.000 comparatie-implementari-df.py:13(__init__)
        1    0.062    0.062   12.105   12.105 comparatie-implementari-df.py:167(depth_first_lifoqueue)
   454690   10.838    0.000   10.838    0.000 comparatie-implementari-df.py:32(contineInDrum)
      910    0.424    0.000   11.326    0.012 comparatie-implementari-df.py:64(genereazaSuccesori)
   247732    0.293    0.000    0.710    0.000 queue.py:122(put)
      910    0.002    0.000    0.004    0.000 queue.py:154(get)
        1    0.000    0.000    0.000    0.000 queue.py:245(_init)
     1821    0.001    0.000    0.001    0.000 queue.py:248(_qsize)
   247732    0.061    0.000    0.081    0.000 queue.py:251(_put)
      910    0.000    0.000    0.001    0.000 queue.py:254(_get)
        1    0.000    0.000    0.000    0.000 queue.py:34(__init__)
      911    0.001    0.000    0.002    0.000 queue.py:97(empty)
        3    0.000    0.000    0.000    0.000 threading.py:236(__init__)
   248642    0.060    0.000    0.088    0.000 threading.py:264(__enter__)
   248642    0.059    0.000    0.077    0.000 threading.py:267(__exit__)
   248642    0.063    0.000    0.097    0.000 threading.py:279(_is_owned)
   248642    0.074    0.000    0.171    0.000 threading.py:359(notify)
        1    0.000    0.000    0.000    0.000 {built-in method _thread.allocate_lock}
        1    0.000    0.000   12.114   12.114 {built-in method builtins.exec}
     1821    0.000    0.000    0.000    0.000 {built-in method builtins.len}
   248642    0.029    0.000    0.029    0.000 {method '__enter__' of '_thread.lock' objects}
   249553    0.018    0.000    0.018    0.000 {method '__exit__' of '_thread.lock' objects}
   248642    0.035    0.000    0.035    0.000 {method 'acquire' of '_thread.lock' objects}
      910    0.000    0.000    0.000    0.000 {method 'add' of 'set' objects}
   495463    0.043    0.000    0.043    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        1    0.000    0.000    0.000    0.000 {method 'index' of 'list' objects}
      910    0.000    0.000    0.000    0.000 {method 'pop' of 'list' objects}


"""
