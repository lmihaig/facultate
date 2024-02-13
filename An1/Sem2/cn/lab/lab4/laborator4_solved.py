"""
Titlu: Calcul Numeric, Laboratorul #04
Autor: Alexandru Ghita, aprilie 2021
"""
# Importarea librariei 'numpy' cu alias-ul 'np'
import numpy as np


def subs_desc(U, b, vectorized=True):
    """
        Metoda Substitutiei Descendente: Determina solutia sistemului superior triunghiular U * x = b
        folosind metoda substitutiei descendente.

    :param U (numpy square matrix) = matrice superior triunghiulara
    :param b (numpy column vector) = coloana termenilor liberi
    :param vectorized (bool) = choose whether to vectorize or not
    :return x (numpy column vector) = solutia sistemului
    """
    # Verifica daca matricea U este patratica
    assert np.shape(U)[0] == np.shape(U)[1], "U nu este matrice patratica!"
    n = np.shape(U)[0]  # Salvam in variabila n dimensiunea matricei

    # Verifica daca matricea U este superior triunghiulara
    # assert np.all(U == np.triu(U)), "U nu este superior triunghiulara!"
    # TODO: Modificare vs versiunea din laboratorul trecut!
    assert np.allclose(U, np.triu(
        U), atol=1e-7), "U nu este superior triunghiulara!"

    # Verifica daca U si b au acelasi numar de linii
    assert n == np.shape(b)[0], "U si b nu au acelasi numar de linii!"

    # Verifica daca U este inversabila:
    # Determinant matrice superior triunghiulara = Produs elemente diagonala
    assert np.abs(np.prod(U.diagonal())) > 0, "Matricea U nu este inversabila!"

    # Initializeaza vectorul x ca vector coloana numpy
    x = np.full(shape=b.shape, fill_value=np.nan)

    if vectorized:
        """ Metoda substitutiei descendente, vectorizata si optimizata. """
        # Mergem de la ultima linie la prima
        for k in range(n-1, -1, -1):
            x[k] = (b[k] - U[k, k+1:] @ x[k+1:]) / U[k, k]
    else:
        """ Metoda substitutiei descendente: Varianta explicita, nevectorizata. """
        x[n-1] = b[n-1] / U[n-1, n-1]
        for k in range(n-2, -1, -1):
            suma = 0
            for j in range(n-1, k, -1):
                suma += U[k, j] * x[j]
            x[k] = (b[k] - suma) / U[k, k]

    return x


def subs_asc(L, b):
    """
        Metoda Substitutiei Ascendente: Determina solutia sistemului inferior triunghiular L * x = b
        folosind metoda substitutiei ascendente.

    :param L (numpy square matrix) = matrice inferior triunghiulara
    :param b (numpy column vector) = coloana termenilor liberi
    :return x (numpy column vector) = solutia sistemului
    """
    # Verifica daca matricea L este patratica
    assert np.shape(L)[0] == np.shape(L)[1], "L nu este matrice patratica!"
    n = np.shape(L)[0]  # Salvam in variabila n dimensiunea matricei

    # Verifica daca matricea L este inferior triunghiulara
    # assert np.all(L == np.tril(L)), "L nu este inferior triunghiulara!"
    assert np.allclose(L, np.tril(
        L), atol=1e-7), "L nu este superior triunghiulara!"

    # Verifica daca L si b au acelasi numar de linii
    assert n == np.shape(b)[0], "L si b nu au acelasi numar de linii!"

    # Verifica daca L este inversabila:
    # Determinant matrice superior triunghiulara = Produs elemente diagonala
    assert np.abs(np.prod(L.diagonal())) > 0, "Matricea L nu este inversabila!"

    # Initializeaza vectorul x ca vector coloana numpy
    x = np.full(shape=b.shape, fill_value=np.nan)

    """ Metoda substitutiei ascendente, vectorizata si optimizata. """
    # Mergem de la prima linie la ultima
    for i in range(n):
        x[i] = (b[i] - L[i, :i] @ x[:i]) / L[i, i]

    return x


def fact_lu(A):
    assert A.shape[0] == A.shape[1], 'Matricea A nu este patratica!'
    n = A.shape[0]  # Salvan numarul de linii/coloane in variabila n

    # Asigura ca matricea este inversabila
    assert np.linalg.det(A) != 0, 'Matricea A nu admite factorizare LU!'

    # Pasul 1
    L = np.eye(n, dtype=np.float32)  # sau L = np.identity(n)

    w = np.array(range(n))  # sau w = list(range(n)) sau w = np.arange(n)

    # Pasul 2
    for i in range(n-1):
        # Pasul 3
        if not np.any(A[i:, i]):  # Verifica daca sunt zerouri in vectorul de sub pivot (inclusiv)
            # (incepand cu pivotul, in jos)
            raise AssertionError('Matricea A nu admite factorizare LU!')
        else:
            # Pozitia primului element nenul din slice-ul coloanei i
            p = np.argmax(np.abs(A[i:, i]))
            p += i  # Ne intereseaza linia din matricea 'a'. Pozitia 'p' este cea din slice. Compensam cu numarul de
            # linii lipsa, 'i'.

        # Pasul 4
        if p != i:
            A[[p, i], :] = A[[i, p], :]  # Schimba linia 'i' cu linia 'p'
            w[[p, i]] = w[[i, p]]  # Memoreaza schimbarea de mai sus

            # Pasul 5
            if i != 0:
                # Schimbarea subliniilor 'i' si 'p' din matricea L
                L[[p, i], :i] = L[[i, p], :i]

        # Pasul 6
        for j in range(i+1, n):
            # Pasul 7
            # Salvarea multiplicatorilor in matricea L
            L[j, i] = A[j, i] / A[i, i]

            # Pasul 8
            A[j, :] -= L[j, i]*A[i, :]  # Zero sub pivot, pe coloana

    # Pasul 9
    if A[-1, -1] == 0:  # Extra-verificare daca matricea are rang maxim!
        raise AssertionError('Matricea A nu admite factorizarea LU!')

    # Pasul 10
    U = A  # Salveaza in variabila 'U' matricea 'A'

    # Pasul 11  # Returnarea variabilelor cerute
    return L, U, w


def fact_qr(A):
    # TODO: Arata ce poti! Urmareste pseudo-codul din PDF si incearca implementarea de unul singur!
    return 0, 0


def ex1():
    A = np.array([
        [2., 0., 0.],
        [3., 4., 0.],
        [1., 3., 1.]
    ], dtype=np.float32)

    b = np.array([
        [2],
        [11],
        [10]
    ], dtype=np.float32)

    x = np.array([
        [1],
        [2],
        [3]
    ], dtype=np.float32)

    x_sol = subs_asc(L=A, b=b)

    is_correct = np.allclose(x, x_sol)
    print(
        f'Am implementat corect metoda substitutiei ascendente? {is_correct}')


def ex2():
    A = np.array([
        [2., 3., 0.],
        [3., 4., 2.],
        [1., 3., 1.]
    ], dtype=np.float32)

    b = np.array([
        [8],
        [17],
        [10]
    ], dtype=np.float32)

    x = np.array([
        [1],
        [2],
        [3]
    ], dtype=np.float32)

    L, U, w = fact_lu(A=A)

    # Modificarea lui b (permuta elementele lui b a.i. acestea sa corespunda ecuatiilor originale)
    b_prime = b[w]

    # Primul sistem
    y = subs_asc(L=L, b=b_prime)

    # Al doilea sistem
    x_sol = subs_desc(U=U, b=y)

    # Verificarea implementarii
    is_correct = np.allclose(x, x_sol)
    print(f'Am implementat corect factorizarea LU? {is_correct}')


def ex3():
    A = np.array([
        [2., 3., 0.],
        [3., 4., 2.],
        [1., 3., 1.]
    ], dtype=np.float32)

    b = np.array([
        [8],
        [17],
        [10]
    ], dtype=np.float32)

    x = np.array([
        [1],
        [2],
        [3]
    ], dtype=np.float32)

    Q, R = fact_qr(A=A)

    # Modificarea lui b
    b_mod = Q.T @ b

    # Rezolvarea sistemului
    x_sol = subs_desc(U=R, b=b_mod)

    # Verificarea implementarii
    is_correct = np.allclose(x, x_sol)
    print(f'Am implementat corect factorizarea QR? {is_correct}')


if __name__ == '__main__':
    ex1()
    ex2()
    # ex3()
