"""
Titlu: Calcul Numeric, Laboratorul #03
Autor: Alexandru Ghita, martie 2021
"""
# Importarea librariei 'numpy' cu alias-ul 'np'
import numpy as np


def subs_desc(U, b, vectorized=True):
    """
        Metoda Substitutiei Descendente: Determina solutia sistemului superior triunghiular U * x = b
        folosind metoda substitutiei descendente.

    :param U (numpy square matrix) = Matrice superior triunghiulara.
    :param b (numpy column vector) = Coloana termenilor liberi.
    :param vectorized (bool) = Choose whether to vectorize or not.
    :return x (numpy column vector) = Solutia sistemului.
    """
    # Verifica daca matricea U este patratica
    assert np.shape(U)[0] == np.shape(U)[1], "U nu este matrice patratica!"
    n = np.shape(U)[0]  # Salvam in variabila 'n' dimensiunea matricei

    # Verifica daca matricea U este superior triunghiulara
    assert np.all(U == np.triu(U)), "U nu este superior triunghiulara!"

    # Verifica daca U si b au acelasi numar de linii
    assert n == np.shape(b)[0], "U si b nu au acelasi numar de linii!"

    # Verifica daca U este inversabila:
    # (Determinant matrice superior triunghiulara = Produs elemente diagonala principala)
    assert np.prod(U.diagonal()) != 0., "Matricea U nu este inversabila!"

    # Initializeaza vectorul x ca vector coloana numpy
    x = np.full(shape=b.shape, fill_value=np.nan)

    if vectorized:
        """ Metoda substitutiei descendente, vectorizata si optimizata. """
        # Mergem de la ultima linie la prima
        for i in range(n-1, -1, -1):
            x[i] = (b[i] - U[i, i+1:] @ x[i+1:]) / U[i, i]
    else:
        """ Metoda substitutiei descendente: Varianta explicita, nevectorizata. """
        # Pasul 1
        x[-1] = b[-1] / U[-1, -1]  # Ultima componenta a vectorului x

        # Pasul 2
        for i in range(n-2, -1, -1):
            suma = 0.
            for j in range(n-1, i, -1):  # Folosita ca sa calculeze suma din formula
                suma += U[i, j] * x[j]

            # Scrie componenta de pe pozitia 'i' a vectorului x
            x[i] = (b[i] - suma) / U[i, i]

    # Pasul 3
    return x


def meg_fp(a, b):
    """
        Metoda de eliminare Gauss fara pivotare, folosita pentru a rezolva sistemul A * x = b.
    :param a (numpy square matrix): Matricea sistemului.
    :param b: (numpy column vector): Coloana termenilor liberi.
    :return: x (numpy column vector): Solutia sistemului.
    """
    # Verifica daca matricea 'a' este patratica
    assert a.shape[0] == a.shape[1], 'Matricea A NU este patratica!'

    # Asigura compatibilitatea matricei 'a' cu vectorul 'b'.
    assert a.shape[0] == b.shape[0], 'Matricea A si vectorul b NU sunt compatibile!'

    # Pasul 1
    E = np.concatenate((a, b), axis=1)

    # Numarul de linii/coloane (pentru identarea in python)
    n = b.shape[0] - 1  # Cu '1' mai putin pentru ca in numpy plecam de la 0

    # Pasul 2
    for i in range(n):  # 0, 1, 2, ... , n-1
        # Pasul 3 (aflam pozitia pivotului de pe coloana k)
        if not E[i:, i].any():  # Verifica daca sunt zerouri in vectorul de sub pivot (inclusiv)
            raise AssertionError(
                'Sistem incompatibil sau sistem compatibil determinat.')
        else:
            # Pozitia primului element nenul din slice-ul coloanei i
            p = np.argmin(E[i:, i] == 0)
            # (incepand cu pivotul, in jos)
            p += i  # Ne intereseaza linia din matricea 'a'. Pozitia 'p' este cea din slice. Compensam cu numarul de
            # linii lipsa, 'i'.

        # Pasul 4 (schimba linia 'i' cu 'p' daca pivotul nu se afla pe diagonala principala)
        if i != p:
            """ a[[j, k], :] = a[[k, j], :] -> Rocada intre linia 'j' si 'k'. """
            E[[p, i], :] = E[[i, p], :]

        # Pasul 5 (zero pe coloana sub pozitia pivotului)
        for j in range(i+1, n+1):  # i+1, i+2, ... , n
            # Pasul 6
            m = E[j, i] / E[i, i]

            # Pasul 7
            E[j, :] -= m * E[i, :]

    # Pasul 8 (verifica si ultimul element de pe diagonala principala daca este zero)
    if E[n, n] == 0:
        raise AssertionError(
            'Sistem incompatibil sau sistem compatibil determinat.')

    # Pasul 9 (gaseste solutia numerica folosind metoda substitutiei descendente)
    x = subs_desc(E[:, :-1], E[:, -1])

    # Pasul 10
    return x


def meg_pp(a, b):
    # TODO (antrenament): Hint: Diferenta fata de meg_fp este data de 'Pasul 3'.
    # Verifica daca matricea 'a' este patratica
    assert a.shape[0] == a.shape[1], 'Matricea A NU este patratica!'

    # Asigura compatibilitatea matricei 'a' cu vectorul 'b'.
    assert a.shape[0] == b.shape[0], 'Matricea A si vectorul b NU sunt compatibile!'

    # Pasul 1
    E = np.concatenate((a, b), axis=1)

    # Numarul de linii/coloane (pentru identarea in python)
    n = b.shape[0] - 1  # Cu '1' mai putin pentru ca in numpy plecam de la 0

    # Pasul 2
    for i in range(n):  # 0, 1, 2, ... , n-1
        # Pasul 3 (aflam pozitia pivotului de pe coloana k)
        if not E[i:, i].any():  # Verifica daca sunt zerouri in vectorul de sub pivot (inclusiv)
            raise AssertionError(
                'Sistem incompatibil sau sistem compatibil determinat.')
        else:
            p = np.argmax(np.abs(E[i:, i]))
            p += i

        # Pasul 4 (schimba linia 'i' cu 'p' daca pivotul nu se afla pe diagonala principala)
        if i != p:
            """ a[[j, k], :] = a[[k, j], :] -> Rocada intre linia 'j' si 'k'. """
            E[[p, i], :] = E[[i, p], :]

        # Pasul 5 (zero pe coloana sub pozitia pivotului)
        for j in range(i+1, n+1):  # i+1, i+2, ... , n
            # Pasul 6
            m = E[j, i] / E[i, i]

            # Pasul 7
            E[j, :] -= m * E[i, :]

    # Pasul 8 (verifica si ultimul element de pe diagonala principala daca este zero)
    if E[n, n] == 0:
        raise AssertionError(
            'Sistem incompatibil sau sistem compatibil determinat.')

    # Pasul 9 (gaseste solutia numerica folosind metoda substitutiei descendente)
    x = subs_desc(E[:, :-1], E[:, -1])

    # Pasul 10
    return x


def ex2():
    #  Matricea A cu tipul de date 'float32'
    A = np.array([
        [2, 3, 0],
        [3, 4, 2],
        [1, 3, 1]
    ], dtype=np.float32)

    # Vectorul coloana 'b' cu tipul de date 'float32'
    b = np.array([
        [8],
        [17],
        [10]
    ], dtype=np.float32)

    # Solutia sistemului A * x = b folosind Metoda de eliminare Gauss fara pivotare
    sol1 = meg_fp(a=A, b=b)
    print('Solutia gasita cu MEG_FP este x_sol = ', sol1)

    # Solutia sistemului A * x = b folosind Metoda de eliminare Gauss cu pivotare partiala
    sol2 = meg_pp(a=A, b=b)
    print('Solutia gasita cu MEG_PP este x_sol = ', sol2)


if __name__ == '__main__':
    # Apelarea exercitiul 2, atunci cand script-ul este rulat si NU importat in alt fisier.
    ex2()
