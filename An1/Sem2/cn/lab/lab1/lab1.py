import numpy as np
import matplotlib.pyplot as plt

# Metoda Bisectiei


def metoda_bisectiei(a, b, f, epsilon):
    """ O implementare a metodei bisectiei.
    :param a (float): Capatul din stanga al intervalului.
    :param b (float): Capatul din dreapta al intervalului.
    :param f (functie): Functia pentru care se va aplica metoda.
    :param epsilon (float): Eroarea acceptata.

    :return x_num (float): Solutia numerica.
    :return N (int): Numarul de iteratii.
    """

    # TODO: Scrie o intructiune a.i. programul sa inceteze la alegerea eronata a capetelor intervalului
    # (e.g. a=4, b=-3). Totodata, se va afisa si la consola un mesaj referitor la eroare.
    assert b > a, "Interval incorect"
    # Prima aproximare
    # x_num = (a + b) / 2.  # TODO: Cum poti rescrie expresia a.i. sa eviti 'overflow'-ul?
    x_num = (a / 2) + (b / 2)
    # Numarul de pasi necesari pentru a atinge eroarea acceptata.
    # Conversie la 'int' pentru ca `range` de mai jos nu accepta 'float'
    # TODO: Este necesara si aplicarea 'np.floor' in acest caz? # -> Nu, deoarece int() #
    N = int((np.log2((b - a) / epsilon)))

    # ==============================================================
    # Iteratiile algoritmului
    # ==============================================================

    for _ in range(1, N):   # Variabila '_' nu este folosita.
        if f(x_num) == 0:  # Daca prima aproximare reprezinta solutia (lucky!).
            break  # Intructiunea 'break' intrerupe bucla 'for'. # TODO: Cauta si instructiunea 'continue'. # -> Done
        elif np.sign(f(a)) * np.sign(f(x_num)) < 0:  # Este folosit doar semnul valorilor
            b = x_num  # Restrange intervalul -> Muta capatul b
        else:
            a = x_num  # Restrange intervalul -> Muta capatul a

        x_num = (a + b) / 2.  # Update al aproximarii

    return x_num, N


# ==============================================================
# Aplicare a metodei bisectiei pentru un exemplu
# ==============================================================
def functie_exemplu(x):
    """
    Functie folosita drept exemplu.
    :param x: Punct / vector pentru care dorim valorile functiei.
    :return: y: Punct / vector al valorilor functiei calculate in x.
    """
    y = x**3 - 7*x**2 + 14*x - 6  # Atribuirea in y a expresiei functiei

    return y


A = 0  # Capatul din stanga al intervalului
B = 4  # Capatul din dreapta al intervalului
EPSILON = 1e-3  # 1e-3 -> 10**(-3). Eroarea maxima acceptata
NUM_POINTS = 50  # In cate puncte sa discretizam intervalul
# Discretizare a intervalului [A, B] in NUM_POINTS puncte
x = np.linspace(A, B, NUM_POINTS)
y = functie_exemplu(x)  # Valorile functiei pentru punctele din discretizare

"""
Functia aleasa are trei solutii in intervalul ales. 
Pentru aflarea fiecarei solutii trebuie ales cate un interval
astfel incat sa fie respectate conditiile metodei (vezi curs/seminar). 
"""
# Calculeaza solutia numerica si numarul de iteratii
x_num1, N1 = metoda_bisectiei(a=0., b=1., f=functie_exemplu, epsilon=EPSILON)
x_num2, N2 = metoda_bisectiei(a=1., b=3.2, f=functie_exemplu, epsilon=EPSILON)
x_num3, N3 = metoda_bisectiei(a=3.2, b=4., f=functie_exemplu, epsilon=EPSILON)


# ==============================================================
# Afisare grafic
# ==============================================================
plt.figure(0)  # Initializare figura
plt.plot(x, y, label='f(x)')  # Plotarea functiei
plt.scatter(x_num1, 0, label='sol1')  # Adaugare solutie1 in grafic
plt.scatter(x_num2, 0, label='sol2')  # Adaugare solutie2 in grafic
plt.scatter(x_num3, 0, label='sol3')  # Adaugare solutie3 in grafic

plt.axhline(0, c='black')  # Adauga axa OX
plt.axvline(0, c='black')  # Adauga axa OY
plt.xlabel('x')  # Label pentru axa OX
plt.ylabel('f(x) = y')  # Label pentru axa OY
plt.title('Metoda Bisectiei')  # Titlul figurii
plt.grid(b=True)  # Adauga grid
plt.legend()  # Arata legenda
plt.show()  # Arata graficul
