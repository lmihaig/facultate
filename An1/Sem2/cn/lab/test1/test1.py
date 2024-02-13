import numpy as np
import matplotlib.pyplot as plt


# Ex 1
A = np.array([
    [-4,5,0],
    [-5,-5,-4],
    [3,-4,3]

], dtype = np.float32)

# 1.(a)
temp = A[:, 1]

print(f"Coloana 2 = {temp}\n")

# 1.(b)
prod = temp @ A[:, 0]

print(f"Produsul scalar intre linia 2 si coloana 1: {prod}\n")

# 1.(c)
print(f"Numarul de linii si de coloane ale matricei {np.shape(A)}\n")

# 1.(d)
A = A.astype(np.float64)


# Ex 2
## ??

print(f"{np.sqrt(13):.5f}")

# Ex 3

def functie(x):
    return x**3 + 7*x**2 - 36

x = np.linspace(-6, 6, 114)
y = functie(x)

plt.figure(2)
plt.plot(x, y, label="f(x)")
plt.title('Titlu')
plt.grid()
plt.axhline(0, c='black') 
plt.axvline(0, c='black')
plt.xlabel('x')
plt.ylabel('f(x) = y')
plt.show()