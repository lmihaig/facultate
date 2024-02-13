"""
Titlu: Calcul Numeric, Laboratorul #03, warmup
Autor: Alexandru Ghita, martie 2021
"""
# Importarea librariei 'numpy' cu alias-ul 'np'
import numpy as np

"""
    Obs 1. Pentru implementarea algoritmilor vom folosi libraria numpy. Pentru a beneficia de puterea maxima a acesteia,
    vom utiliza array-uri i.e. matrice.
    
    * Array-urile se definesc folosind metoda 'np.array(object)' 
        See the docs:  https://numpy.org/doc/stable/reference/generated/numpy.array.html
    
    1. Pentru a defini o matrice, vom trimite drept 'obiect' metodei 'np.array(object)' o lista de liste. Exemplu:
        A = np.array([
            [2, 3],
            [1, 5]
        ])
    
    2. Pentru a defini un vector (by default coloana), vom vrea o matrice cu o singura coloana, insa cu mai multe linii.
    Exemplu:
        b = np.array([
            [3],
            [1]
        ])
"""


"""
    Obs 2. Este foarte important tip-ul de date folosit de elementele array-ului creat. De exemplu, matricea 'A' si 
    vectorul 'b' definite mai sus vor fi interpretate de numpy ca avand tipul de date 'int64'. Pentru a evita erorile 
    provenite din calculul cu numere intregi, vom folosi doar date de tip 'float32'.
        Tipuri de date: https://numpy.org/devdocs/user/basics.types.html
    
    Pentru a converti un array la tipul de date dorit, putem utiliza una din metodele echivalente de mai jos:
        
        1. A = np.array([
               [2, 3],
               [1, 5]
           ], dtype=np.float32)
        
        2. A = np.array([
           [1, 0],
           [0, 1]
           ]).astype(np.float32)
           
        3. A = np.array([
               [2., 3.],
               [1., 5.]
           ])
            
"""


"""
    Obs 3. Pentru a afla dimensiunile array-ului i.e. numarul de linii/coloane, vom folosi metoda 'np.shape(array)' sau
    in mod echivalent, apelarea proprietatii 'shape' a array-ului creat. Ambele metode returneaza un tuplu. Pe prima
    pozitie se afla numarul de linii, iar pe a doua pozitie numarul de coloane.
        See the docs: https://numpy.org/devdocs/reference/generated/numpy.shape.html?highlight=shape#numpy.shape
        
        Exemple (pentru array-urile definite mai sus):
            
            1.  Pentru matrice:
                    np.shape(A)     -> (2, 2) i.e. doua linii si doua coloane
                    np.shape(A)[0]  -> Numarul de linii
                    np.shape(A)[1]  -> Numarul de coloane
            
            2. Pentru vectori:
                    np.shape(b)     -> (2, ) i.e. doua linii si nicio coloana
                    np.shape(b)[0]  -> Numarul de coloane
                    np.shape(b)[0] este echivalent, in acest caz, cu 'len(b)'.
"""


"""
    Obs 4. Apelarea elementelor dintr-un array:
    
        1. Pentru vectori.
        
        Exemplu pentru un vector b:
            
            b[i]    -> returneaza elementul de pe pozitia i, unde i = 0, 1, 2, ... , len(b) - 1
            b[-i]   -> returneaza elementul de pe pozitia i, numarand in sens invers.
                    b[-1]   -> returneaza ultimul element
                    b[-2]   -> returneaza penultimul element
            
            b[start:stop]   -> Returneaza un slice al vectorului, avand elementele de la pozita start (inclusiv)
                                si pana la stop (exclusiv)
            
            b[:stop] -> Returneaza un slice al vectorului, avand toate elementele incepand elementul de pe 
                        pozitia 0 (inclusiv) si pana la stop (exclusiv)
            
            b[start:]-> Returneaza un slice al vectorului, avand toate elementele incepand elementul de pe 
                        pozitia start (inclusiv) si pana la ultimul element (inclusiv)
                        
        2. Pentru matrice.
        
        Exemplu pentru o matrice A:
        
        A[i, j]     -> Returneaza elementul de pe linia i si coloana j (indexarea incepe de la zero!)
        A[i, :]     -> Returneaza linia i
        A[:, j]     -> Returneaza coloana j  
        A[i, :j]    -> Returneaza linia i, si toate coloanele incepand cu prima (inclusiv) si pana la j (exclusiv)      
"""


"""
    Obs 5. Numpy permite inmultirea array-urilor folosind operatorul '@'.
    Exemple:
        1. Pentru matrice: 
            Daca A are dimensiunea (n, m), iar B are dimensiunea (m, p), atunci
                C = A @ B reprezinta produsul matricelor A si B si are dimensiunea (n, p)

        2. Pentru vectori:
            Produsul scalar dintre doi vectori poate fi realizat folosind acelasi operator '@'.
        
    Consulta, totodata si metodele 'matmul' si 'dot'.
    See the docs: 
        matmul: https://numpy.org/devdocs/reference/generated/numpy.matmul.html?highlight=matmul#numpy.matmul
        dot: https://numpy.org/devdocs/reference/generated/numpy.dot.html?highlight=dot#numpy.dot
"""


def ex1():
    """
        Cerinte:
            1. Creaza o matrice A, avand patru linii si 5 coloane cu elemente de tip float32.
               Printeaza matricea la consola.
            2. Afla dimensiunile matricei, folosind o metoda din numpy si printeaza la consola rezultatul.
            3. Converteste tipul de date al matricei la intregi si printeaza matricea rezultatul la consola.
                   Hint: Foloseste metoda 'astype'.
            4. Creaza o alta matrice C avand 3 lini si 3 coloane si elemente de tip float32 si
               printeaza la consola rezultatul
            5. Creaza un vector b avand 3 linii si o coloana si elemente de tip float32 si
               printeaza la consula rezultatul
            6. Inmulteste matricele A si C si printeaza rezultatul la consola.
            7. Inmulteste matricea C si vectorul b si afiseaza rezultatul la consola.
    """

    # 1. Creaza matricea A
    A = np.array([
               [2, 3, 4, 5, 6],
               [3, 4, 5, 6, 7],
               [4, 5, 6, 7, 6],
               [5, 6, 7, 8, 9]
           ], dtype=np.float32)
    print('1. Matricea A este:\n', A, '\n')

    # 2. Afla dimensiunile matricei
    dims = np.shape(A)
    print(f'2. Dimensiunile matricei A sunt {dims}\n')

    # 3. Converteste matricea
    A = A.astype(np.int)
    print('3. Matricea A convertita este\n', A, '\n')

    # 4. Creeaza matricea C
    C = np.array([
               [2, 3, 4],
               [3, 4, 5],
               [4, 5, 6]
           ], dtype=np.float32)
    print('4. Matricea C este\n', C, '\n')

    # 5. Creaza vectorul b
    b = np.array([
            [3],
            [1],
            [3],
        ], dtype=np.float32)
    print('5. Vectorul b este\n', b, '\n')

    # 6. Inmulteste A si C
    rezultat = A @ C
    print('6. Inmultirea lui A cu C\n', rezultat, '\n')

    # 7. Inmulteste C si b
    rezultat = C @ b
    print('7. Inmultirea lui C cu b\n', rezultat, '\n')


def ex2():
    """
        Cerinte:
            1. Creaza un vector coloana b, cu elemente de tip float32, avand 5 linii si printeaza rezultatul la consola.
            2. Printeaza la consola primul si ultimul element al vectorului b.
            3. Printeaza la consola penultimul element al vectorului b.
            4. Extrage elementele vectorului b fara primul si ultimul element al acestuia si printeaza
               rezultatul la consola.

            5. Creaza o matrice A, cu elemente de tip float32, avand 4 linii si 4 coloane si printeaza rezultatul la
               consola.
            6. Extrage a doua linie a matricei A si printeaza la consola rezultatul.
            7. Extrage a treia coloana a matricei A si printeaza la consola rezultatul.
    """

    # 1. Creaza vectorul b
    b = np.array([
            [3],
            [1],
            [3],
            [5],
            [10]
        ], dtype=np.float32)
    print('1. Vectorul b este\n', b, '\n')

    # 2. Primul si ultimul element al lui b
    primul = b[0]
    ultimul = b[-1]
    print(f'2. Primul element al lui b este {primul}, iar ultimul element al lui b este {ultimul}.\n')

    # 3. Penultimul element
    penultim = b[-2]
    print(f'3. Penultimul element al lui b este {penultim}\n')

    # 4. Extragerea fara primul si ultimul
    slice = b[1:-1]
    print('4. Slice-ul lui b fara primul si ultimul element este\n', slice, '\n')

    # 5. Creaza matricea A
    A = np.array([
               [2, 3, 4, 1],
               [3, 4, 5, 1],
               [4, 5, 6, 1]
           ], dtype=np.float32)
    print('5. Matricea A este\n', A, '\n')

    # 6. Extrage a doua linie
    second_line = A[1, :]
    print('6. A doua linie a matricei A este\n', second_line, '\n')

    # 7. Extrage a treia coloana
    third_column = A[:, 2]
    print('7. A treia coloana a matricei A este\n', third_column, '\n')


if __name__ == '__main__':
    """ Comenteaza exercitiul pe care nu doresti sa il rezolvi. """
    # ex1()
    ex2()
