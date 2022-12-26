"""ENUNT: 

Identificator: ex-cautare-informata-exemple-modificate
Se va implementa o problema asemanatoare cu a canibalilor si misionarilor, indeplinind urmatoare conditii:
Avem N1 canibali, N2 misionari si K unitati de hrana pe un mal (pe malul celalalt nu avem nimic) și o barcă cu M locuri. Ne intereseaza sa mutam toți canibalii si misionarii pe malul opus. Nu ne interesaza neaparat sa mutam si hrana.
In cazul in care intr-unul dintre locuri (barca sau maluri) avem mai multi canibali decat misionari, acestia o sa-i atace.
Totusi misionarii pot evita sa fie atacati, hrandin canibalii cu unitati de hrana. Astfel, daca sunt NM (NM > 0) misionari si NC canibali intr-o locatie si NC>NM, misionarii pot evita sa fie atacati de canibali hranindu-i cu (NC-NM)/2 unitati de hrana (practic un canibal se satura cu 0.5 unitati de hrana.
Hrana poate fi mutata cu barca (dar trebuie mereu sa fie un om care carmuieste barca; barca nu se poate deplasa fara oameni). O unitate de hrana ocupa loc cat un om (nu se pot deplasa decat unitati intregi de hrana, nu jumatati). Canibalii nu mananca din hrana daca sunt singuri (doar un misionar le poate da, si le da numai daca e nevoie, adica daca sunt canibali mai multi decat misionari).
In plus, barca se degradeaza in timp. La fiecare Nr deplasari cu barca (de la un mal la celalalt) un loc din barca se va degrada (adica numarul de locuri din barca scade cu 1). Se va preciza in afisarea solutiei, pentru fiecare tranziție si cate locuri au ramas in barca (adica locuri care nu s-au stricat).
Costul unei mutări e dat de numărul de oameni din barcă

Fișierul de input va conține toți parametrii problemei în formatul: "nume parametru=valoare". De exemplu:
N1=4
N2=4
K=2
M=2
Nr=3
MalInitial=vest
MalFinal=est
Solutiile vor reprezenta secventele de mutari. Afisarea în fișierul de output se va face scriind la fiecare moment de timp:

indicele stării (nodului) în drum
informații despre starea curenta (cati canibali, misionari si unități de hrană sunt pe malul de vest, cati canibali, misionari si hrană sunt pe malul de est)
Se va afișa între stări de la care mal pornesc bărcile si către care se duc și detaliat ce conțin.
Între două soluții se va afișa un separator, de exemplu "=======================".
"""


if __name__ == "__main__":
    missionaries = 3
    cannibals = 3
    food = 5
