"""ENUNT:
Se va implementa urmatorul joc:
Jocul se desfasoara pe un grid NxN, cu 10≥N≥4 (utilizatorul va fi întrebat la începutul jocului pe ce dimensiune de grid dorește să joace).
Este un joc turn based
Un jucator foloseste simbolul x si celalalt 0 ( o sa ii numim pe scurt jucatorii x si 0)
Jucatorul x pune simbolul primul pe tabla
Prima mutare, pentru fiecare dintre jucători nu are nicio restricție. De la a doua mutare încolo jucatorii pot pune simboluri doar pe linii care sunt la distanță mai mică sau egala cu K1 de o linie pe care se află deja un simbol al jucătorului care tocmai mută și distanță mai mică sau egala cu K2 față de o coloană pe care se află deja un simbol al jucătorului. Valorile pentru K1 și K2 se vor citi de la tastatură.

Scopul jocului este sa se creeze un numar cat mai mare de linii de câte 3 simboluri pe rand, coloana sau diagonala. Jocul se termina cand nu mai sunt spatii libere in grid. Castiga jucatorul care are cel mai mare numar de secvente (acest număr reprezentând și scorul) de 3 simboluri vecine in linie pe rand, coloana sau diagonala. Observație: secvențele de simboluri se pot intersecta (dacă sunt 4 simboluri vecine în linie, se vor însuma la scor ca două secvențe de câte 3). De exemplu, mai jos ambele seturi de câte 3 simboluri "0" se adună la punctaj.
La afișarea gridului în consolă, se vor afișa în dreptul liniilor și coloanelor și numerele lor (indicii începând de la 0) ca să poată identifica utilizatorul mai ușor coordonatele locului în care vrea să mute.

"""