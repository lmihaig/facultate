import numpy as np
import matplotlib.pyplot as plt

# Ex 1
# functia in sine
def functie(x):
    return x**3 + 4*x**2 - 17*x - 60

# 1.a) 
x = np.linspace(-5, 5, 85)

y = functie(x)

# 1.b)
plt.figure(0)

# 1.c) si 1.d) 
plt.axhline(0, c='black') 
plt.axvline(0, c='black')
plt.xlabel('x')
plt.ylabel('f(x) = y')

# 1.e)
plt.grid()

# 1.f)
plt.title('Titlu')

# 1.g)
plt.plot(x, y, label="f(x)", color="cyan")

# 1.h)
plt.legend()
plt.show()

# Ex 3
A = np.array([
    [0,1,-5],
    [-2,2,-2],
    [-1,-6,5]

], dtype = np.float32)

# 3.a)
print(f"Numarul de linii si coloane a matricei A: {np.shape(A)}")

# 3.b)
temp = A[:, 0]
print(f"Coloana 1 = {temp}")

# 3.c)
prod = A[0, :] @ A[:, 1]
print(f"Produsul scalar intre linia 1 si coloana 2: {prod}")

# 3.d)
A = A.astype(np.int32)

# Ex 2
def func(x):
    return x**2 - 31

def secanta(f, x0, x1, eps, max_iter):
    i = 2
    y0 = f(x0)
    y1 = f(x1)

    while i <= max_iter:
        x_star = x1 - y1 * (x1 - x0) / (y1 - y0)

        if np.abs(x_star - x1) < eps:
            return x_star, i
        
        i += 1

        x0, y0 = x1, y1
        x1 = x_star
        y1 = f(x_star)

    print(f'Metoda Secantei nu a atins convergenta dupa {i - 1} iteratii.')
    sys.exit(1)

x_num, steps = secanta(f=func, x0 = 5, x1=6, eps=1e-5, max_iter=1000)
print(f'Solutia ecuatiei f(x) = 0 cu metoda secantei este x_sol = {x_num:.6f} gasita in N = {steps} pasi.')