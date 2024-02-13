"""
Titlu: Calcul Numeric, Laboratorul #02
Autor: Alexandru Ghita, februarie 2021
"""
import sys
import numpy as np
import matplotlib.pyplot as plt


def newton_raphson(f, df, x0, eps, max_iter):
    """
    O implementare a metodei Newton-Raphson.
    :param f: (function) Functia pentru care dorim solutia.
    :param df: (function) Derivata functiei pentru care dorim solutia
    :param x0: (float) Aproximarea initiala a solutiei.
    :param eps: (float) Toleranta erorii
    :param max_iter: (int) Numarul maxim de iteratii admis.

    :return x1: (float) Aproximarea solutiei
    :return i: (int) Numarul de iteratii
    """
    # Pasul 1
    i = 1  # Contorul iteratiilor

    # Pasul 2
    while i <= max_iter:
        # Pasul 3
        x1 = x0 - f(x0) / df(x0)  # Update al aproximarii

        # Pasul 4
        if np.abs(x1 - x0) < eps:  # np.abs(value) returneaza valoarea absoluta a lui' 'value'
            """
            Daca este indeplinita conditia 'if'-ului de mai sus functie returneaza x1 si i 
            si se iese din body-ul functiei.
            """
            return x1, i

        # Pasul 5
        i += 1  # Echivalent cu i = i + 1

        # Pasul 6
        x0 = x1  # Inverseaza valorile aproximarilor pentru a avea sens formula din bucla while

    # Pasul 7
    print(f'Metoda N-R nu a atins convergenta dupa {i} iteratii.')  # TODO: Este corect numarul de pasi 'i' aici?
    sys.exit(1)  # Opreste script-ul si returneaza exit code 1 -> Au fost erori in rulare.


def secanta(f, x0, x1, eps, max_iter):
    """
    O implementare a metodei secantei.
    :param f: (function) Functia pentru care dorim solutia.
    :param x0: (float) Una din aproximarile initiale.
    :param x1: (float) Una din aproximarile initiale.
    :param eps: Toleranta maxima a erorii
    :param max_iter: (int) Numarul maxim de iteratii admis.

    :return: x_star: (float) Aproximare solutiei.
    :return i (int) Numarul de iteratii
    """
    # Pasul 1
    i = 2  # Initializeaza contorul iteratiilor (2 pentru ca avem deja doua aproximari)
    y0 = f(x0)
    y1 = f(x1)

    # Pasul 2
    while i <= max_iter:
        # Pasul 3
        x_star = x1 - y1 * (x1 - x0) / (y1 - y0)

        # Pasul 4
        if np.abs(x_star - x1) < eps:  # Explicatii similare cu metoda N-R
            return x_star, i

        # Pasul 5
        i += 1

        # Pasul 6
        x0 = x1
        y0 = y1
        x1 = x_star
        y1 = f(x_star)

    # Pasul 7
    print(f'Metoda Secantei nu a atins convergenta dupa {i} iteratii.')  # TODO: Este corect numarul de pasi afisat?
    sys.exit(1)


def pozitie_falsa(f, x0, x1, eps, max_iter):
    # TODO: Arata ce poti! Implementeaza metoda conform pseudocodului prezentat.
    return 0, 0


def func1(x):
    """ Functia din exercitiul 2. """
    y = -x ** 3 - 2 * np.cos(x)  # O varianta
    # y = -np.power(x, 3) -2*np.cos(x)  # O alta varianta

    return y


def dfunc1(x):
    """ Derivata functiei din exercitiul 2. """
    y = -3 * x ** 2 + 2 * np.sin(x)

    return y


def plot_function(interval, functions, points=None, fig_num=0, title=None):
    """
    Helper function. Este folosita pentru a genera graficul mai multor functii si al solutiilor in aceeasi figura.
    :param interval: (list) Lista cu doua valori, continand capetele intervalului pe care dorim plot-area.
    :param functions: (list) Lista care contine obiecte de tip tuple. Fiecare tuple are doua pozitii. Pe prima pozitie
                             se afla referinta catre functie pe care dorim sa o afisam. Pe a doua pozitie se afla
                             un str care va fi folosit in legenda graficului.
    :param points: (list) Lista care contine obiecte de tip tuple. Fiecare tuple are doua pozitii. Pe prima pozitie se
                          afla un numar de tip float, reprezentand coordonata in x a solutiei gasite pentru functia
                          studiata. Metoda este 'hard-codata' in sensul ca valoarea in y a punctului este data drept 0.
                          Acest lucru este fortat pentru a afisa punctul fix pe axa OX.
    :param fig_num: (int) Numarul figurii.
    :param title: (str) Titlul figurii
    :return: None
    """
    plt.figure(fig_num)  # Initializeaza figura
    domain = np.linspace(start=interval[0], stop=interval[1])  # Discretizarea domeniului in 50 de puncte

    for element in functions:
        """ Itereaza prin fiecare tuplu din lista si afiseaza graficul fiecarei functii in figura. 
            Pune, totodata si label-ul care va fi afisat in legenda.
        """
        values = element[0](domain)  # Valorile functiei in punctele din domeniu.
        legend_label = element[1]  # Labelul ce va fi afisat in legenda.

        plt.plot(domain, values, label=legend_label)  # Afisarea graficului in figura.

    if points is not None:  # Verifica daca avem puncte de afisat.
        for point in points:
            plt.scatter(point[0], 0, label=point[1])  # Afiseaza punctul in figura.

    plt.axhline(0, c='black')  # Afiseaza axa OX
    plt.axvline(0, c='black')  # Afiseaza axa OY
    plt.xlabel('points')  # Afiseaza label pe axa OX
    plt.ylabel('values')  # Afiseaza label pe axa OY
    plt.grid()  # Afiseaza grid ("patratele")
    plt.legend()  # Afiseaza legenda (cauta parametrul 'label' in plot sau scatter de mai sus.)

    if title is not None:  # Verifica daca avem titlul setat
        plt.title(title)  # Afiseaza titlul

    plt.show()  # Afiseaza graficul


def ex2_newton_raphson():
    X0 = -3.
    EPS = 1e-5  # Echivalent 10**(-5)
    MAX_ITER = 1000
    x_num, steps = newton_raphson(f=func1, df=dfunc1, x0=X0, eps=EPS, max_iter=MAX_ITER)
    print(f'Solutia ecuatiei f(x) = 0 cu metoda Newton-Raphson este x_sol = {x_num:.8f} gasita in N = {steps} pasi.')
    print('-' * 72)

    plot_function(interval=[-3, 3],
                  functions=[
                      (func1, 'f(x)'),  # Primul obiect
                      (dfunc1, "f'(x)")  # Al doilea obiect
                  ],
                  points=[
                      (x_num, 'x_aprox')
                  ],
                  title='Exercitiul 2, Metoda NR'
                  )


def ex2_secanta():
    EPS = 1e-5
    MAX_ITER = 1000
    x_num, steps = secanta(f=func1, x0=-3., x1=3., eps=EPS, max_iter=MAX_ITER)

    print(f'Solutia ecuatiei f(x) = 0 cu metoda secantei este x_sol = {x_num:.8f} gasita in N = {steps} pasi.')

    plot_function(interval=[-3, 3],
                  functions=[(func1, 'f(x)')],
                  points=[(x_num, 'xnum')],
                  title='Exercitiul 1, Metoda Secantei')


def ex2_pozitie_falsa():
    EPS = 1e-5
    MAX_ITER = 1000
    x_num, steps = pozitie_falsa(f=func1, x0=-3, x1=3, eps=EPS, max_iter=MAX_ITER)

    print(f'Solutia ecuatiei f(x) = 0 cu metoda pozitiei false este x_sol = {x_num:.5f} gasita in N = {steps} pasi.')

    plot_function(interval=[-3, 3],
                  functions=[(func1, 'f(x)')],
                  points=[(x_num, 'xnum')],
                  title='Exercitiul 1, Metoda Pozitiei False')


if __name__ == '__main__':  # Stand alone
    """ Decomenteaza una dintre metodele de mai jos pentru a rula exercitiul specificat. """
    ex2_newton_raphson()
    # ex2_secanta()
    # ex2_pozitie_falsa()
