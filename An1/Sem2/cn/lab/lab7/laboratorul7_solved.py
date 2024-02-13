"""
Titlu: Calcul Numeric, Laboratorul #07
Autor: Alexandru Ghita, mai 2021
"""
import numpy as np
import matplotlib.pyplot as plt


def int_drept(a, b, f):
    assert a < b, 'Some error message!'

    # Pasul 1
    h = b - a

    # Pasul 2
    I = h * f((a + b) / 2.)

    # Pasul 3
    return I


def int_trap(a, b, f):
    # Pasul 1
    h = b - a

    # Pasul 2
    I = h/2. * (f(a) + f(b))

    # Pasul 3
    return I


def int_simp(a, b, f):
    # Pasul 1
    h = b - a

    # Pasul 2
    I = h/6. * (f(a) + 4*f((a + b) / 2.) + f(b))

    # Pasul 3
    return I


def func_ex1(x):
    y = 3*x / (x**2 - 9.)

    return y


def ex1():
    """ (a) """
    val_exact = 3./2. * np.log(16./7.)  # Valoarea exacta a integralei

    """ (b) """
    interval = [4, 5]  # [a, b]

    # Calcularea aproximarilor integralei cu cele trei metode
    I_0 = int_drept(a=interval[0], b=interval[1], f=func_ex1)  # Dreptunghi
    I_1 = int_trap(a=interval[0], b=interval[1], f=func_ex1)  # Trapez
    I_2 = int_simp(a=interval[0], b=interval[1], f=func_ex1)  # Simpson

    # Afisare la consola a rezultatelor
    print(f"Valoarea exacta a lui I(f) este: {val_exact:.6f}")
    print(f"Valoarea aproximata I_0 este: {I_0:.6f}")
    print(f"Valoarea aproximata I_1 este: {I_1:.6f}")
    print(f"Valoarea aproximata I_2 este: {I_2:.6f}")

    """ (c) """
    # Calculul erorilor
    E_0 = np.abs(val_exact - I_0)  # Dreptunghi
    E_1 = np.abs(val_exact - I_1)  # Trapez
    E_2 = np.abs(val_exact - I_2)  # Simpson

    # Afiasare la consola a erorilor
    print()  # Printeaza o linie goala
    print(f"Eroarea E_0 este: {E_0}")
    print(f"Eroarea E_1 este: {E_1}")
    print(f"Eroarea E_2 este: {E_2}")

    """ EXTRA. """
    domain = np.linspace(4, 5, 100)  # e.g. [4, 4.1, 4.2, ... , 5]
    f_values = func_ex1(domain)  # e.g. [f(4), f(4.1), ... , f(5)]

    # Folosit pentru a vedea graficul mai larg
    extra_domain = np.linspace(4 - 0.2, 5 + 0.2, 100)
    f_values_extra = func_ex1(extra_domain)

    # Generarea figurii
    plt.figure(0)
    plt.axhline(0, c='k')
    plt.plot(extra_domain, f_values_extra, label='f(x)')

    # Coloreaza aria de sub graficul functiei
    plt.fill_between(domain, f_values, color='orange', alpha=0.5, label='area')
    plt.axvline(4, c='k', linestyle='--', linewidth=0.5)
    plt.axvline(5, c='k', linestyle='--', linewidth=0.5)

    """" Dreptunghi. """
    middle_point = func_ex1((4. + 5.) / 2.)
    plt.plot((4, 4), (0, middle_point), marker='*', c='green')
    plt.plot((5, 5), (0, middle_point), marker='*', c='green')
    plt.plot((4, 5), (0, 0), marker='*', c='green')
    plt.plot((4, 5), (middle_point, middle_point), marker='*', c='green')

    """ Trapez. """
    # plt.plot((4, 4), (0, func_ex1(4)), marker='*', c='red')
    # plt.plot((5, 5), (0, func_ex1(5)), marker='*', c='red')
    # plt.plot((4, 5), (0, 0), marker='*', c='red')
    # plt.plot((4, 5), (func_ex1(4), func_ex1(5)), marker='*', c='red')
    #
    # plt.grid()
    # plt.legend()
    # plt.ylim([-0.2, 2.5])

    plt.show()


def func_ex2(x):
    y = 1. / (1. + x)

    return y


def ex2():
    """ EXTRA. """
    domain = np.linspace(0, 1)
    f_values = func_ex2(domain)
    m = 3
    X = np.linspace(0, 1, m + 1)  # Pentru Dreptunghi & Simpson 2*m + 1 puncte
    Y = np.zeros_like(X)

    plt.figure(1)
    for l in X:  # Pentru Simpson, din 2 in 2
        plt.axvline(l, c='k', linestyle='--', linewidth=0.5)

    plt.plot(domain, f_values, label='f(x)')
    plt.scatter(X, Y, marker='*', c='r', s=100, label='X')
    plt.ylim([-0.2, 1.1])
    plt.axhline(0, c='k')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    ex1()
    ex2()
