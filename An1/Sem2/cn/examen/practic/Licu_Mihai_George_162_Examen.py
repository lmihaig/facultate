import numpy as np
import matplotlib.pyplot as plt


# 1.a)
def int_romberg(a, b, f, n):
    # in caz ca capetle intervalului nu sunt alese corect
    assert b > a, "Interval incorect"

    # determinam h
    h = np.abs(b - a) + 1

    Q = np.full(shape=(n, n), fill_value=np.nan)

    # primul element al matricei
    Q[0, 0] = h/2*(f(a)+f(b))

    # prima coloana
    # indexul incepe de la zero deci cand ridicam la putere eliminam -1
    for i in range(1, n):
        suma = sum([f(a+(k-1)*h/(2**i)) for k in range(2, 2**i+1)])
        Q[i, 0] = h/(2**i) * (f(a) + f(b) + suma)

    # restul matricei
    # idem cu indexul
    for i in range(1, n):
        for j in range(1, i+1):
            Q[i, j] = (4**j*Q[i, j-1]-Q[i-1, j-1])/(4**j-1)
    I = Q[n-1, n-1]
    return I


def func(x):
    return 1/(1+x**2)


def ex1():

    # 1.b)
    Iexact = 2*np.arctan(6)
    print("Valoarea exacta a integralei = ", Iexact)

    # 1.c)
    Iaprox = int_romberg(a=-6, b=6, f=func, n=6)
    print("Aproximarea prin metoda Romberg = ", Iaprox)

    # 1.d)
    err = np.abs(Iexact - Iaprox)
    print("Eroarea = ", err)


def func2(x):
    return np.cos(4*x)


# 2.a)
def interp_lagrange(X, Y, z):
    n = X.shape[0]
    L = np.full(shape=n, fill_value=np.nan)
    t = 0

    # pasul 1
    for k in range(n):
        L[k] = 1
        for j in range(n):
            if j != k:
                L[k] *= (z-X[j])/(X[k]-X[j])

    # pasul 2
    t = sum([L[k] * Y[k] for k in range(n)])
    return t


def ex2():
    X = np.linspace(0, np.pi, 19)
    Y = func2(X)

    # 2.b)
    print("X = {0}\nY={1}".format(X, Y))

    # 2.c)
    plt.figure(0)
    plt.grid()
    plt.scatter(X, Y, label="Datele cunoscute",
                color="orange", s=50, marker="p")
    plt.title("Date")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')

    # 2.d)
    x1 = np.linspace(0, np.pi, 80)
    y1 = [interp_lagrange(X, Y, xi) for xi in x1] # list comprehension pentru a trimite fiecare element din x1 in parte

    # 2.e)
    plt.plot(x1, func2(x1), "c", label="Functia exacta", linewidth=4)
    plt.plot(x1, y1, "r--", label="Metoda Lagrange de interpolare Lagrange")
    plt.legend()

    # 2.f)
    err = np.abs(func2(x1)-y1)
    plt.figure(1)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, err, "m--", label="Graficul erorii")
    plt.legend()

    plt.show()


if __name__ == "__main__":
    ex1()
    ex2()
