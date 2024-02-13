from sys import platform
import numpy as np
import matplotlib.pyplot as plt


def bisectie(a, b, f, epsilon):

    # programul inceteaza daca intervalele nu sunt alese corect
    assert b > a, "Interval incorect"
    # aproximarea initiala
    x_num = (a / 2) + (b / 2)
    # numarul de pasi necesari
    N = int((np.log2((b - a) / epsilon)))

    for _ in range(1, N):
        if f(x_num) == 0:
            break
        elif np.sign(f(a)) * np.sign(f(x_num)) < 0:
            b = x_num  # schimba capatul b
        else:
            a = x_num  # schimba capatul a

        x_num = (a + b) / 2.  # update al aproximarii

    return x_num


def func(x):
    return x**2 - 13


def ex1():
    # a)
    EPS = 1e-7  # Eroarea maxima acceptata
    # Descretizam intervalul [-5,5] in 200 de puncte echidistante
    x = np.linspace(-5, 5, 200)
    y = func(x)  # Valorile functiei f(x)

    x_num1 = bisectie(a=-5., b=0., f=func, epsilon=EPS)
    x_num2 = bisectie(a=0., b=5., f=func, epsilon=EPS)
    print(f"Solutiile ecuatiei de gradul II sunt: {x_num1} si {x_num2}")

    # b)
    plt.figure(0)
    plt.plot(x, y, label="f(x)")  # Graficul functiei in sine
    plt.scatter(x_num1, 0, label="Solutia1", s=50, marker="*",
                color="green")  # Prima solutie pe grafic
    plt.scatter(x_num2, 0, label="Solutia2", s=50, marker="*",
                color="orange")  # A doua solutie pe grafic
    plt.axhline(0, c="black")  # Axa Ox
    plt.axvline(0, c="black")  # Axa Oy
    plt.grid()
    plt.xlabel("x")
    plt.ylabel("f(x) = y")
    plt.title("Graficul functiei cu solutiile aflate prin Metoda Bisectiei")
    plt.legend()
    plt.show()


def interp_neville(X, Y, z):
    n = X.shape[0]
    Q = np.full(shape=(n, n), fill_value=np.nan)
    Q[:, 0] = Y
    # indicii se schimba din transcirerea din pseudocod
    for i in range(1, n):
        for j in range(1, i+1):
            Q[i, j] = (Q[i, j-1] * (z - X[i-j]) - Q[i-1, j-1]
                       * (z - X[i]))/(X[i]-X[i-j])
    t = Q[n-1, n-1]
    return t


def func2(x):
    return np.exp(2*x)  # e^(2*x)


def ex2():
    X = np.linspace(-1, 1, 23)
    Y = func2(X)
    x1 = np.linspace(-1, 1, 75)
    # a)
    # list comprehension ca ``TypeError: only size-1 arrays can be converted to Python scalars``
    y1 = [interp_neville(X=X, Y=Y, z=z1) for z1 in x1]

    # b)
    plt.figure(1)
    plt.grid()
    plt.scatter(X, Y, label="Datele clientului",
                color="orange", s=55, marker="*")
    plt.title("Predictie")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, func2(x1), '-', linewidth=3, label="Functia f(x)")
    plt.plot(x1, y1, "r--", label="Interpolarea directa")
    plt.legend()

    # c)
    error = np.abs(func2(x1) - y1)
    plt.figure(2)
    plt.title("Eroare")
    plt.axhline(0, c='black')
    plt.axvline(0, c='black')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('f(x) = y')
    plt.plot(x1, error, "b--", label="Graficul erorii")
    plt.legend()

    plt.show()


def fact_qr_new(A):
    # Verificam daca matricea este patratica si inversabila
    assert np.shape(A)[0] == np.shape(A)[1], "A nu este patratica"
    assert np.linalg.det(A), "A nu este inversabila"

    n = A.shape[0]
    Q = np.full(shape=(n, n), fill_value=np.nan)
    R = np.full(shape=(n, n), fill_value=np.nan)
    # Pasul 1: initializare
    suma = sum([A[i, 1]**2 for i in range(n)])
    R[0, 0] = np.sqrt(suma)
    for i in range(n):
        Q[i, 0] = A[i, 0]/R[0, 0]

    for j in range(1, n):
        R[0, j] = sum([Q[s, 0] * A[s, j] for s in range(n)])

    # Pasul 2: ...


def ex3():
    A = np.array([
        [0, -6, -6, -10],
        [7, -2, -9, -4],
        [-6, -10, 9, 1],
        [7, 6, -10, -5]
    ]).astype(np.float32)

    b = np.array([
        [-158],
        [-72],
        [-19],
        [-39]
    ]).astype(np.float32)

    raspuns_corect = np.linalg.solve(A, b)
    print(raspuns_corect)

    fact_qr_new(A)


if __name__ == "__main__":
    ex1()
    ex2()
    ex3()
