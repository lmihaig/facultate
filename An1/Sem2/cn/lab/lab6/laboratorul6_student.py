"""
Titlu: Calcul Numeric, Laboratorul #06
Autor: Alexandru Ghita, mai 2021
"""
import numpy as np
import matplotlib.pyplot as plt


def deriv_num(X, Y, metoda='ascendente'):
    n = np.shape(X)[0] - 2
    # np.zeroes(shape=n) sau np.full(shape=n, fill_value=np.none)
    df = np.empty(shape=n)

    if metoda.lower() == 'ascendente':
        for i in range(1, n+1):
            df[i-1] = (Y[i+1] - Y[i])/(X[i+1] - X[i])
    elif metoda.lower() == 'descendente':
        for i in range(1, n+1):
            df[i-1] = (Y[i] - Y[i-1]) / (X[i] - X[i-1])
    elif metoda.lower() == 'centrale':
        for i in range(1, n+1):
            df[i-1] = (Y[i+1] - Y[i-1]) / (X[i+1] - X[i-1])
    else:
        raise ValueError('Parametrul "metoda" nu este corect!')

    return df


def func1(x):
    return 5*np.sin(2*x) - 2*np.cos(3*x) + 11.5*x


def dfunc1(x):
    return 6*np.sin(3*x) + 10*np.cos(2*x) + 11.5


def ex1():
    """ Hint: Tine cont ca, in discretizarea intervalului ales, sunt create doua noduri suplimentare
    la capetele intervalului. """
    domain = np.linspace(-1, 1, 100)
    df_exact = dfunc1(domain)

    N = 70
    X = np.full(shape=N+2, fill_value=np.nan)
    X[1:-1] = np.linspace(-1, 1, N)
    h = X[3] - X[2]
    X[0] = X[1] - h
    X[-1] = X[-2] + h

    Y = func1(X)
    dy_ascendente = deriv_num(X=X, Y=Y, metoda='ascendente')
    dy_descendente = deriv_num(X=X, Y=Y, metoda='descendente')
    dy_centrale = deriv_num(X=X, Y=Y, metoda='centrale')

    plt.figure(0)
    plt.plot(domain, df_exact, c='k', linewidth=2, label='dy_exact')
    plt.plot(X[1:-1], dy_ascendente, c='orange', linewidth=2,
             linestyle='--', label='dy_ascendente')
    plt.plot(X[1:-1], dy_descendente, c='green', linewidth=2,
             linestyle='--', label='dy_descendente')
    plt.plot(X[1:-1], dy_centrale, c='red', linewidth=2,
             linestyle='--', label='dy_centrale')

    plt.legend()
    plt.show()

    dy_exact_for_error = dfunc1(X)[1:-1]
    plt.figure(1)
    plt.plot(X[1:-1], np.abs(dy_exact_for_error -
                             dy_ascendente), c='orange', label="asc")
    plt.plot(X[1:-1], np.abs(dy_exact_for_error -
                             dy_descendente), c='green', label="desc")
    plt.plot(X[1:-1], np.abs(dy_exact_for_error -
                             dy_centrale), c='red', label="cen")
    plt.legend()
    plt.show()


def interp_directa(X, Y, z):
    """ Stefan Catalin Cucu (163) version from Lab#5 """
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
    n = len(X)
    for i in range(n):
        if X[i] <= z <= X[i+1]:
            a = Y[i]
            b = (Y[i+1] - Y[i]) / (X[i+1] - X[i])
            t = a+b*(z-X[i])
            return t


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
    return 0


def dfunc2(x):
    return 0


def ex2():
    pass


def ex3():
    x_clicks_all = [55., 69, 75, 81, 88, 91, 95, 96, 102, 108, 116, 126, 145, 156, 168, 179, 193, 205, 222, 230, 235,
                    240, 242, 244, 253, 259]

    y_clicks_all = [162., 176, 188, 209, 229, 238, 244, 256, 262, 259, 254, 260, 262, 265, 263, 260, 259, 252, 244, 239,
                    233, 227, 226, 224, 224, 221]

    select_from = 1  # Extrage click-uri din 'select_from' in 'select_from'

    x_clicks = x_clicks_all[::select_from]
    y_clicks = y_clicks_all[::select_from]

    domain = np.linspace(x_clicks[0], x_clicks[-1], 100)

    N = len(x_clicks) - 1

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
    plt.plot(domain, inter_lagr_direct, c='w', linewidth=2,
             linestyle='-.', label='Metoda Lagrange')
    plt.plot(domain, inter_spline_liniara, c='g', linewidth=2,
             linestyle='-', label='Spline Liniara')
    plt.plot(domain, inter_spline_patratica, c='b', linewidth=2,
             linestyle='--', label='Spline Patratica')
    plt.title('Interpolare, N={}'.format(N))
    plt.legend()
    plt.xlim([-1, 305])
    plt.ylim([-1, 305])
    plt.xlabel('x')
    plt.ylabel('y = f(x)')
    plt.show()


if __name__ == '__main__':
    # ex1()
    # ex2()
    ex3()
