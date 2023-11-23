"""ENUNT:
Modificați problema canibalilor și misionarilor astfel încât scopul să fie doar sa mutam misionarii pe un mal rămânând toti canibalii pe celălalt? Modificati testul pentru starea scop si euristica.

"""


"""
Dati enter dupa fiecare solutie afisata.

Presupunem ca avem costul de plimbare a unui canibal =2 si a unui misionar =1. Astfel A* are trebui sa prefere drumurile in care se muta mai rar canibalii
"""


# informatii despre un nod din arborele de parcurgere (nu din graful initial)


import math


class NodParcurgere:
    gr = None  # trebuie setat sa contina instanta problemei

    def __init__(self, info, parinte, cost=0, h=0):
        self.info = info
        self.parinte = parinte  # parintele din arborele de parcurgere
        self.g = cost  # consider cost=1 pentru o mutare
        self.h = h
        self.f = self.g + self.h

    def obtineDrum(self):
        l = [self]
        nod = self
        while nod.parinte is not None:
            l.insert(0, nod.parinte)
            nod = nod.parinte
        return l

    def afisDrum(
        self, afisCost=False, afisLung=False
    ):  # returneaza si lungimea drumului
        l = self.obtineDrum()
        for nod in l:
            if nod.parinte is not None:
                if nod.parinte.info[2] == 1:
                    mbarca1 = self.__class__.gr.malInitial
                    mbarca2 = self.__class__.gr.malFinal
                else:
                    mbarca1 = self.__class__.gr.malFinal
                    mbarca2 = self.__class__.gr.malInitial
                print(
                    ">>> Barca s-a deplasat de la malul {} la malul {} cu {} canibali si {} misionari.".format(
                        mbarca1,
                        mbarca2,
                        abs(nod.info[0] - nod.parinte.info[0]),
                        abs(nod.info[1] - nod.parinte.info[1]),
                    )
                )
            print(str(nod))
        if afisCost:
            print("Cost: ", self.g)
        if afisCost:
            print("Nr noduri: ", len(l))
        return len(l)

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if infoNodNou == nodDrum.info:
                return True
            nodDrum = nodDrum.parinte

        return False

    def __repr__(self):
        sir = ""
        sir += str(self.info)
        return sir

    # euristica banală: daca nu e stare scop, returnez 1, altfel 0

    def __str__(self):
        if self.info[2] == 1:
            barcaMalInitial = "<barca>"
            barcaMalFinal = "       "
        else:
            barcaMalInitial = "       "
            barcaMalFinal = "<barca>"
        return (
            "Mal: "
            + self.gr.malInitial
            + " Canibali: {} Misionari: {} {}  |||  Mal:"
            + self.gr.malFinal
            + " Canibali: {} Misionari: {} {}"
        ).format(
            self.info[0],
            self.info[1],
            barcaMalInitial,
            self.__class__.gr.N - self.info[0],
            self.__class__.gr.N - self.info[1],
            barcaMalFinal,
        )

    """
	def __str__(self):
		return str(self.info)+"\n"

	"""


class Graph:  # graful problemei
    def __init__(self, nume_fisier):
        f = open(nume_fisier, "r")
        textFisier = (
            f.read()
        )  # citeste tot fisierul si returneaza un string cu continutul lui
        listaInfoFisier = textFisier.split()  # ["3", "2", "stang", "drept"]
        # self.__class__ inseamna clasa curenta
        self.__class__.N = int(listaInfoFisier[0])
        self.__class__.M = int(listaInfoFisier[1])
        self.__class__.malInitial = listaInfoFisier[2]
        self.__class__.malFinal = listaInfoFisier[3]
        # memoram in stare doar canibalii si misionarii de pe malul stang; pe ceilalti ii deducem
        # (nrCanibaliMalInitial, numarMisionariMalInitial, locatieBarca)
        # locatieBarca= 1 daca e pe malul initial si 0 daca e pe malul final
        self.start = (
            self.__class__.N,
            self.__class__.N,
            1,
        )  # informatia nodului de start
        # self.scopuri=[(0,0,0)]

    def testeaza_scop(self, nodCurent):
        return (
            nodCurent.info[0] == Graph.N
            and nodCurent.info[1] == 0
            or nodCurent.info[0] == 0
            and nodCurent.info[1] == Graph.N
        )

    # functia de generare a succesorilor, facuta la laborator

    def genereazaSuccesori(self, nodCurent, tip_euristica="euristica banala"):
        # mal curent = mal cu barca; mal opus=mal fara barca
        def test_conditie(mis, can):
            return mis == 0 or mis >= can

        listaSuccesori = []
        # nodCurent.info va contine un triplet (c_i, m_i, mal_barca)
        barca = nodCurent.info[2]
        if barca == 1:  # malul barcii este cel initial malul curent e cel cu barca
            canMalCurent = nodCurent.info[0]
            misMalCurent = nodCurent.info[1]
            canMalOpus = Graph.N - canMalCurent
            misMalOpus = Graph.N - misMalCurent
        else:  # barca==0 adica malul final
            canMalOpus = nodCurent.info[0]  # malul opus (barcii) este cel initial
            misMalOpus = nodCurent.info[1]
            canMalCurent = Graph.N - canMalOpus
            misMalCurent = Graph.N - misMalOpus
        maxMisionariBarca = min(Graph.M, misMalCurent)
        for misBarca in range(maxMisionariBarca + 1):
            if misBarca == 0:
                maxCanibaliBarca = min(Graph.M, canMalCurent)
                minCanibaliBarca = 1
            else:
                maxCanibaliBarca = min(Graph.M - misBarca, canMalCurent, misBarca)
                minCanibaliBarca = 0
            for canBarca in range(minCanibaliBarca, maxCanibaliBarca + 1):
                # consideram mal curent nou ca fiind acelasi mal de pe care a plecat barca
                canMalCurentNou = canMalCurent - canBarca
                misMalCurentNou = misMalCurent - misBarca
                canMalOpusNou = canMalOpus + canBarca
                misMalOpusNou = misMalOpus + misBarca
                if not test_conditie(misMalCurentNou, canMalCurentNou):
                    continue
                if not test_conditie(misMalOpusNou, canMalOpusNou):
                    continue
                if (
                    barca == 1
                ):  # testul este pentru barca nodului curent (parinte) deci inainte de mutare
                    infoNodNou = (canMalCurentNou, misMalCurentNou, 0)
                else:
                    infoNodNou = (canMalOpusNou, misMalOpusNou, 1)
                if not nodCurent.contineInDrum(infoNodNou):
                    costSuccesor = 1
                    # costSuccesor=canBarca*2+misBarca
                    listaSuccesori.append(
                        NodParcurgere(
                            infoNodNou,
                            nodCurent,
                            cost=nodCurent.g + costSuccesor,
                            h=NodParcurgere.gr.calculeaza_h(infoNodNou, tip_euristica),
                        )
                    )

        return listaSuccesori

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    # aceasta este o functie mai eficienta de generare a succesorilor, care genereaza direct perechiile valide de numere de canibali si misionari care trec raul (respectand conditia problemei atat pe maluri cat si in barca; deci nu se mai genereaza acele perechi pe care le eliminam apoi pentru ca nu indeplineau conditia)

    # euristica banala

    def calculeaza_h(self, infoNod, tip_euristica="euristica banala"):
        match tip_euristica:
            case "euristica banala":
                if not (
                    infoNod[0] == Graph.N
                    and infoNod[1] == 0
                    or infoNod[0] == 0
                    and infoNod[1] == Graph.N
                ):
                    return 1
                return 0
            case "euristica nebanala":
                # calculez cati oameni mai am de mutat si impart la nr de locuri in barca
                # totalOameniDeMutat=infoNod[0]+infoNod[1]
                return (
                    2 * math.ceil((infoNod[0] + infoNod[1]) / (self.M - 1))
                    + (1 - infoNod[2])
                    - 1
                )  # (1-infoNod[2]) vine de la faptul ca daca barca e pe malul final trebuie sa mai faca o trecere spre malul initial ca sa ii ia pe oameni, pe cand daca e deja pe malul initial, nu se mai aduna acel 1
            case _:
                return 0

        """
		5c 5m  barca:3locuri
		----->b:3
		<---- b:1

		 2  --->b:3
		"""

        """
		21+21=42  3   42/3=14 drumuri dus, dar si intors
		<--- 14
		"""

    def __repr__(self):
        sir = ""
        for k, v in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir


def breadth_first(gr, nrSolutiiCautate):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start, None)]

    while len(c) > 0:
        # print("Coada actuala: " + str(c))
        # input()
        nodCurent = c.pop(0)

        if gr.testeaza_scop(nodCurent):
            print("Solutie:")
            nodCurent.afisDrum(afisCost=True, afisLung=True)
            print("\n----------------\n")
            input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        lSuccesori = gr.genereazaSuccesori(nodCurent)
        # print(nodCurent.info, lSuccesori)
        c.extend(lSuccesori)


def a_star(gr, nrSolutiiCautate, tip_euristica):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start, None, 0, gr.calculeaza_h(gr.start))]

    while len(c) > 0:
        nodCurent = c.pop(0)

        if gr.testeaza_scop(nodCurent):
            print("Solutie: ")
            nodCurent.afisDrum(afisCost=True, afisLung=True)
            print("\n----------------\n")
            input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        lSuccesori = gr.genereazaSuccesori(nodCurent, tip_euristica=tip_euristica)
        for s in lSuccesori:
            i = 0
            gasit_loc = False
            for i in range(len(c)):
                # diferenta fata de UCS e ca ordonez dupa f
                if c[i].f >= s.f:
                    gasit_loc = True
                    break
            if gasit_loc:
                c.insert(i, s)
            else:
                c.append(s)


gr = Graph("input.txt")
NodParcurgere.gr = gr
# Rezolvat cu breadth first
# print("Solutii obtinute cu breadth first:")
# breadth_first(gr, nrSolutiiCautate=3)

print("\n\n##################\nSolutii obtinute cu A*:")
nrSolutiiCautate = 3
a_star(gr, nrSolutiiCautate=3, tip_euristica="euristica nebanala")
