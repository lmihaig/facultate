"""
Titlu: Calcul Numeric, Laboratorul #05
Autor: Alexandru Ghita, aprilie 2021
"""
import numpy as np
import matplotlib.pyplot as plt


def interp_directa(X, Y, z):
    dim = X.shape[0]
    A = np.vander(X, dim, increasing='True')

    a = np.linalg.solve(A, Y)

    t = 0
    for i in range(dim):
        t += a[i] * np.power(z, i)

    return t


def interp_lagrange(X, Y, z):
    dim = X.shape[0]

    t = 0
    for k in range(dim):
        prod = 1
        for j in range(dim):
            if j != k:
                prod *= (z-X[j])/(X[k]-X[j])
        t += prod * Y[k]

    return t


def interp_newton(X, Y, z):

    return 0


def interp_newton_dd(X, Y, z):

    return 0


def f(x):
    return np.sin(2*x) - 2*np.cos(3*x)


def ex1():
    """ (a) Generare date client si vizualizarea acestora. """
    # Genereaza datele
    x = np.linspace(-np.pi, np.pi, 20)
    y = f(x)
    # Creaza o figura noua in care sa vizualizezi datele generate
    plt.figure(0)
    # plt.axhline(0, c='black')
    # plt.axvline(0, c='black')
    # plt.xlabel('x')
    # plt.ylabel('f(x) = y')
    plt.grid()
    # plt.title('Date')
    plt.scatter(x, y, label="Date clienti", color="green", s=45, marker="*")

    """ (b) Aproximarea valorilor lipsa. """
    # Discretizeaza domeniul
    x1 = np.linspace(-np.pi, np.pi, 100)

    # Calculeaza aproximarea in fiecare punct din domeniu
    y1 = interp_directa(x, y, x1)

    """ (c) Generare grafic (verificare). """
    # Ploteaza in figura de la punctul (a) (plt.show() trebuie sa fie activ doar aici acum)
    plt.title("Prediction graph")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, f(x1), '-', linewidth=3, label="Functia f(x)")
    plt.plot(x1, y1, "r--", label="Interpolarea directa")
    plt.legend()

    """ (d) Graficul erorii de interpolare. """
    # Calculeaza eroarea
    error = np.abs(f(x1) - y1)

    # Genereaza o figura noua si afiseaza graficul erorii
    plt.figure(1)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, error, "b--", label="Graficul erorii")
    plt.legend()

    plt.show()


def ex2():
    """ (a) Generare date client si vizualizarea acestora. """
    # Genereaza datele
    x = np.linspace(-np.pi, np.pi, 20)
    y = f(x)
    # Creaza o figura noua in care sa vizualizezi datele generate
    plt.figure(2)
    # plt.axhline(0, c='black')
    # plt.axvline(0, c='black')
    # plt.xlabel('x')
    # plt.ylabel('f(x) = y')
    plt.grid()
    # plt.title('Date')
    plt.scatter(x, y, label="Date clienti", color="green", s=45, marker="*")

    """ (b) Aproximarea valorilor lipsa. """
    # Discretizeaza domeniul
    x1 = np.linspace(-np.pi, np.pi, 100)

    # Calculeaza aproximarea in fiecare punct din domeniu
    y1 = interp_lagrange(x, y, x1)

    """ (c) Generare grafic (verificare). """
    # Ploteaza in figura de la punctul (a) (plt.show() trebuie sa fie activ doar aici acum)
    plt.title("Prediction graph")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, f(x1), '-', linewidth=3, label="Functia f(x)")
    plt.plot(x1, y1, "r--", label="Interpolarea Lagrange")
    plt.legend()

    """ (d) Graficul erorii de interpolare. """
    # Calculeaza eroarea
    error = np.abs(f(x1) - y1)

    # Genereaza o figura noua si afiseaza graficul erorii
    plt.figure(3)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, error, "b--", label="Graficul erorii")
    plt.legend()

    plt.show()


def ex3():
    """ (a) Generare date client si vizualizarea acestora. """
    # Genereaza datele
    x = np.linspace(-np.pi, np.pi, 20)
    y = f(x)
    # Creaza o figura noua in care sa vizualizezi datele generate
    plt.figure(4)
    # plt.axhline(0, c='black')
    # plt.axvline(0, c='black')
    # plt.xlabel('x')
    # plt.ylabel('f(x) = y')
    plt.grid()
    # plt.title('Date')
    plt.scatter(x, y, label="Date clienti", color="green", s=45, marker="*")

    """ (b) Aproximarea valorilor lipsa. """
    # Discretizeaza domeniul
    x1 = np.linspace(-np.pi, np.pi, 100)

    # Calculeaza aproximarea in fiecare punct din domeniu
    y1 = interp_newton(x, y, x1)

    """ (c) Generare grafic (verificare). """
    # Ploteaza in figura de la punctul (a) (plt.show() trebuie sa fie activ doar aici acum)
    plt.title("Prediction graph")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, f(x1), '-', linewidth=3, label="Functia f(x)")
    plt.plot(x1, y1, "r--", label="Interpolarea Newton")
    plt.legend()

    """ (d) Graficul erorii de interpolare. """
    # Calculeaza eroarea
    error = np.abs(f(x1) - y1)

    # Genereaza o figura noua si afiseaza graficul erorii
    plt.figure(5)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, error, "b--", label="Graficul erorii")
    plt.legend()

    plt.show()


def ex4():
    """ (a) Generare date client si vizualizarea acestora. """
    # Genereaza datele
    x = np.linspace(-np.pi, np.pi, 20)
    y = f(x)
    # Creaza o figura noua in care sa vizualizezi datele generate
    plt.figure(6)
    # plt.axhline(0, c='black')
    # plt.axvline(0, c='black')
    # plt.xlabel('x')
    # plt.ylabel('f(x) = y')
    plt.grid()
    # plt.title('Date')
    plt.scatter(x, y, label="Date clienti", color="green", s=45, marker="*")

    """ (b) Aproximarea valorilor lipsa. """
    # Discretizeaza domeniul
    x1 = np.linspace(-np.pi, np.pi, 100)

    # Calculeaza aproximarea in fiecare punct din domeniu
    y1 = interp_newton_dd(x, y, x1)

    """ (c) Generare grafic (verificare). """
    # Ploteaza in figura de la punctul (a) (plt.show() trebuie sa fie activ doar aici acum)
    plt.title("Prediction graph")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, f(x1), '-', linewidth=3, label="Functia f(x)")
    plt.plot(x1, y1, "r--", label="Interpolarea Newton cu Diferente Divizate")
    plt.legend()

    """ (d) Graficul erorii de interpolare. """
    # Calculeaza eroarea
    error = np.abs(f(x1) - y1)

    # Genereaza o figura noua si afiseaza graficul erorii
    plt.figure(7)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, error, "b--", label="Graficul erorii")
    plt.legend()

    plt.show()


if __name__ == '__main__':
    # ex1()
    ex2()
    # ex3()
    # ex4()
