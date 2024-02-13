"""
Titlu: Calcul Numeric, Laboratorul #06
Autor: Alexandru Ghita, mai 2021
"""
import numpy as np
import matplotlib.pyplot as plt


def deriv_num(X, Y, metoda='ascendente'):
    """ Aproximare numerica a primei derivate a unei functii f folosind metoda diferentelor finite.

    :param X: X = [X0, X1, ..., Xn+1], ! Atentie ca numaratoarea incepe de la 0. In total, avem n+2 elemente.
              unde X0 si Xn+1 sunt puncte extra la stanga si dreapta domeniului pe care se doreste aproximarea.
              Artificiu necesar pentru a putea uni sub aceeasi metoda toate variantele diferentelor finite.
    :param Y: [Y0=f(X0), Y1=f(X1), ..., Yn+1=f(Xn+1)]
    :param metoda (str): Varianta a diferentelor finite ce urmeaza a fi folosita.
    :return: df: df = [df0, df1, ..., dfn-1]. Reprezinta aproximarea primei derivate pe domeniu cautat, fara punctele
                extra din stanga si dreapta.

    Fiecare lista contine pozitiile vectorilor reprezentati.
    Pentru exemplul nostru
                   [-1-.5 .5 1]
    domain =       [0, 1, 2, 3]
    X =         [0, 1, 2, 3, 4, 5]
    Y =         [0, 1, 2, 3, 4, 5]
    df =           [0, 1, 2, 3]
    """
    # Initializari
    n = len(X) - 2  # sau np.shape(X)[0] - 2
    df = np.zeros(shape=n)  # sau df = np.array([np.nan for _ in range(n))])
                            # sau np.full(shape=n, fill_value=np.nan)
    # Pasul 1
    if metoda.lower() == 'ascendente':  # sau metoda.lower() in ['ascendente'] -> Nu este o practica buna pt liste
                                        # cu un singur element
        # Pasul 2
        for i in range(1, n + 1):
            df[i - 1] = (Y[i+1] - Y[i]) / (X[i+1] - X[i])

    # Pasul 3
    elif metoda.lower() == 'descendente':
        # Pasul 4
        for i in range(1, n + 1):
            df[i - 1] = (Y[i] - Y[i-1]) / (X[i] - X[i-1])

    # Pasul 5
    elif metoda.lower() == 'centrale':
        # Pasul 6
        for i in range(1, n + 1):
            df[i - 1] = (Y[i+1] - Y[i-1]) / (X[i+1] - X[i-1])
    else:
        # Varianta 1
        # print('Some error message!')
        # import sys
        # sys.exit(1)

        # Varianta 2
        raise ValueError('Metoda aleasa nu este implementata!')

    # Pasul 7
    return df


def func1(x):
    """ Functia exercitiului 1. """
    y = 5*np.sin(2*x) - 2*np.cos(3*x) + 11.5*x

    return y


def dfunc1(x):
    """ Derivata functiei exercitiului 1. """
    dy = 10*np.cos(2*x) + 6*np.sin(3*x) + 11.5

    return dy


def ex1():
    """ Hint: Tine cont ca, in discretizarea intervalului ales, sunt create doua noduri suplimentare
    la capetele intervalului. """

    """ Valorile exacte ale primei derivate.
        Folosite pentru a putea compara aproximarea facuta pe grafic.
    """
    domain = np.linspace(-1, 1, 100)
    df_exact = dfunc1(domain)

    """ Iteram prin cele trei valori propuse in exercitiu. """
    for N in [20, 40, 70]:
        """ (a) """

        # Discretizarea domeniului X cu puncte extra stanga-dreapta
        X = np.full(shape=N+2, fill_value=np.nan)  # Vector in care vom scrie discretizarea
        X[1:-1] = np.linspace(-1, 1, N)  # Scrierea slice-ului interior (fara puncte extra)
        h = X[2] - X[1]  # Distanta dintre doua puncte
        X[0] = X[1] - h  # Scriere capat extra stanga
        X[-1] = X[-2] + h  # Scriere capat extra dreapta

        Y = func1(X)  # Valorile functiei in discretizarea X de mai sus

        """ Vectori ce contin aproximarea primei derivate pe domeniu (fara puncte extra stanga-dreapta) """
        df_ascendente = deriv_num(X=X, Y=Y, metoda='ascendente')
        df_descendente = deriv_num(X=X, Y=Y, metoda='descendente')
        df_centrale = deriv_num(X=X, Y=Y, metoda='centrale')

        """ Generare grafic (a) """
        plt.figure(0)
        plt.plot(domain, df_exact, c='k', label='df_exacta')
        # Slice interior al lui X (pentru a se potrivi cu vectorii df_METODA)
        plt.plot(X[1:-1], df_ascendente, c='orange', label='df_asc')
        plt.plot(X[1:-1], df_descendente, c='g', label='df_desc')
        plt.plot(X[1:-1], df_centrale, c='r', label='df_centrale')
        plt.legend()  # Afisare legenda
        plt.grid()  # Afisare grid
        plt.xlabel('points')  # Label pe axa OX
        plt.ylabel("f ' (points)")  # Label pe axa OY
        plt.title(f"Aproximarea f'(x) cu N={N}")  # Titlul figurii
        plt.show()  # Afisare figura

        """ (b) """
        # Vector folosit pentru a putea calcula eroarea de aproximare. Eroarea se calculeaza element-wise.
        df_for_error = dfunc1(X)

        """ Vectori ce contin eroarea de aproximare in fiecare punct. """
        err_ascendente = np.abs(df_for_error[1:-1] - df_ascendente)
        err_descendente = np.abs(df_for_error[1:-1] - df_descendente)
        err_centrale = np.abs(df_for_error[1:-1] - df_centrale)

        """ Generare grafic (b) """
        plt.figure(1)
        plt.plot(X[1:-1], err_ascendente, c='orange', label='asc')
        plt.plot(X[1:-1], err_descendente, c='g', label='desc')
        plt.plot(X[1:-1], err_centrale, c='r', label='centrale')
        plt.legend()  # Afisare legenda
        plt.grid()  # Afisare grid
        plt.xlabel('points')  # Label axa OX
        plt.ylabel("Eroor values")  # Label axa OY
        plt.title(f"Erorile pentru N={N}")  # Tilul figurii
        plt.show()  # Afisare figura


def interp_directa(X, Y, z):
    """ Author: Stefan Catalin Cucu (163) -- version from Lab#5

    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param z: Punct in care doresti o valoare aproximata a functiei
    """
    A = np.vander(X, increasing=True)
    a = np.linalg.solve(A, Y)
    t = np.polyval(np.flip(a), z)

    return t


def spline_liniara(X, Y, z):
    """ Metoda de interpolare spline liniara.

    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param z: Punct in care doresti o valoare aproximata a functiei
    :return: t: Valoarea aproximata calculata in z
    """
    # Initializari
    n = len(X) - 1

    # Pasul 1
    for i in range(n):
        # Pasul 2
        if X[i] <= z <= X[i+1]:
            a = Y[i]
            b = (Y[i+1] - Y[i]) / (X[i+1] - X[i])
            t = a + b*(z - X[i])

            # Varianta 1
            # Pasul 3
            return t

            # # Varianta 2
            # break

    # # Pasul 3 (Varianta 2)
    # return t


def spline_patratica(X, Y, dfa, z):
    """ Metoda de interpolare spline patratica.

    :param X: X = [X0, X1, ..., Xn]
    :param Y: [Y0=f(X0), Y1=F(X1), ..., Yn=f(Xn)]
    :param dfa: Valoarea derivatei in capatul din stanga al intervalului folosit
    :param z: Punct in care doresti o valoare aproximata a functiei
    :return: t: Valoarea aproximata calculata in z
    """

    return 0, 0


def func2(x):
    y = np.sin(2*x) - 2*np.cos(3*x)

    return y


def dfunc2(x):
    return 0


def ex2():
    # Discretizarea valorilor exacte
    domain = np.linspace(-np.pi, np.pi, 100)
    f_exact = func2(domain)

    for N in [10, 15, 30]:
        # Discretizarea datelor pentru obtinerea aproximarilor
        X = np.full(shape=N+1, fill_value=np.nan)
        X[:-1] = np.linspace(-np.pi, np.pi, N)
        h = X[2] - X[1]
        X[-1] = X[-2] + h

        Y = func2(X)

        # Valorile aproximarii
        f_spline_liniara = np.array([spline_liniara(X, Y, z) for z in domain])

        """ Graficul exercitiului """
        plt.figure(3)
        plt.scatter(X, Y, s=15, c='red', marker='*', label='Date cunoscute')
        plt.plot(domain, f_exact, c='k', label='f exact')
        plt.plot(domain, f_spline_liniara, c='orange', label='spline liniara')
        plt.grid()
        plt.xlabel('points')
        plt.ylabel('Values')
        plt.legend()
        plt.title(f'Interpolari pentru N={N}')
        plt.show()


def ex3():
    """ Exercitiu de demo.
    """

    """ Datele cunoscute """
    x_clicks_all = [55., 69, 75, 81, 88, 91, 95, 96, 102, 108, 116, 126, 145, 156, 168, 179, 193, 205, 222, 230, 235,
                    240, 242, 244, 253, 259]

    y_clicks_all = [162., 176, 188, 209, 229, 238, 244, 256, 262, 259, 254, 260, 262, 265, 263, 260, 259, 252, 244, 239,
                    233, 227, 226, 224, 224, 221]

    # TODO: Incearca diferite valori intre 1 si 7
    select_from = 7  # Extrage click-uri din 'select_from' in 'select_from'

    x_clicks = x_clicks_all[::select_from]
    y_clicks = y_clicks_all[::select_from]

    # Discretizare domeniu -> Se vor calcula valori aproximate in toate punctele de aici
    domain = np.linspace(x_clicks[0], x_clicks[-1], 100)

    N = len(x_clicks) - 1

    """ Inlocuiti cu apelarea metodelor. Vezi ex. 1 & 2 pentru exemple. """
    inter_lagr_direct = np.zeros_like(domain)  # TODO: To be modified
    inter_spline_liniara = np.zeros_like(domain)  # TODO: To be modified
    dfa = 0  # TODO: To be modified
    inter_spline_patratica = np.zeros_like(domain)  # TODO: To be modified

    # Afisare grafic figura
    plt.figure(5)

    # Afisare date client pe grafic
    plt.scatter(x_clicks, y_clicks, marker='*', c='red', s=10, label='Clicks')

    # Afisare doggo
    image = np.load('frida_doggo.npy')
    plt.imshow(image, extent=[0, 300, 0, 300])

    # Afisare grafic aproximare
    plt.plot(domain, inter_lagr_direct, c='w', linewidth=2, linestyle='-.', label='Metoda Lagrange')
    plt.plot(domain, inter_spline_liniara, c='g', linewidth=2, linestyle='-', label='Spline Liniara')
    plt.plot(domain, inter_spline_patratica, c='b', linewidth=2, linestyle='--', label='Spline Patratica')
    plt.title('Interpolare, N={}'.format(N))
    plt.legend()
    plt.xlim([-1, 305])
    plt.ylim([-1, 305])
    plt.xlabel('x')
    plt.ylabel('y = f(x)')
    plt.show()


if __name__ == '__main__':
    ex1()
    ex2()
    # ex3()
