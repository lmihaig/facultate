import math
import cmath
import matplotlib.pyplot as plt


def getUserInput(var_name: str, var_type: callable, inf=-math.inf, sup=math.inf) -> float:
    while True:
        x = input(f"Introduceti numarul {var_name}: ")
        try:
            if float(x) == var_type(float(x)):
                if inf <= var_type(x) <= sup:
                    return var_type(x)
                else:
                    print(f"Numarul trebuie sa fie in intervalul [{inf},{sup}]")
            else:
                print(f"Numarul nu este {var_type.__name__}")
        except ValueError as e:
            print("Valoare nu este un numar in baza 10")
            print(e)
        except Exception as e:
            print("Eroare necunoscuta")
            print(e)


def ex1():
    x = getUserInput("x", float)
    n = getUserInput("n", int, 4, 11)
    return sum([((-1)**k * x**(2*k))/(2*math.factorial(k)) for k in range(n+1)])


def ex2():
    m = getUserInput("x", float, 1.5, 3.75)
    n = getUserInput("n", int, sup=2)
    return sum([(math.e**-m * m**k)/math.factorial(k)for k in range(n+1)])


def ex3():
    x_real = getUserInput("x_real", float)
    x_imag = getUserInput("x_imag", float)

    y_real = getUserInput("y_real", float)
    y_imag = getUserInput("y_imag", float)

    z_real = getUserInput("z_real", float)
    z_imag = getUserInput("z_imag", float)

    x = complex(x_real, x_imag)
    y = complex(y_real, y_imag)
    z = complex(z_real, z_imag)

    x = cmath.phase(x) * (180/math.pi)
    y = cmath.phase(y) * (180/math.pi)
    z = cmath.phase(z) * (180/math.pi)

    print(f"Unghiul dintre X si Y: {abs(x-y)}")
    print(f"Unghiul dintre X si Z: {abs(x-z)}")
    print(f"Unghiul dintre Y si Z: {abs(y-z)}")


def ex4():
    z = getUserInput("z", float, -1, 1)
    n = getUserInput("n", int, 5, 15)

    rez = sum([(math.factorial(2*k) * (z ** k)) /
               (2**(4*k) * math.sqrt(2) * math.factorial(2*k) * math.factorial(2*k + 1))
               for k in range(n+1)])
    rez_f = math.sqrt((1 - math.sqrt(1-z)) / z)

    print(f"Diferenta {abs(rez - rez_f)}")
    return rez


def ex5():
    a_0 = getUserInput("a_0", float, 0, math.pi/2)
    a = [0, a_0]

    while abs(a[-1] - a[-2]) >= 1e-7:
        a.append(cmath.atan(-3 * a[-1] + 10))

    print(abs(a[-1] - a[-2]))
    print(len(a))
    fig, ax = plt.subplots()
    ax.plot([i for i in range(len(a))], a, 'bo--')
    ax.set_xlim(xmin=0)
    ax.set_ylim(ymin=0)
    plt.ylabel("Limita estimata")
    plt.xlabel("Numarul iteratiei")
    plt.title("Limita sirului")
    plt.show()


def ex6():
    k = 2
    e_sum = (-1) / (math.factorial(k)*(k-1)*k)
    e = 3 + e_sum

    while abs(math.e - e) >= 1e-6:
        k += 1
        e_sum += (-1) / (math.factorial(k)*(k-1)*k)
        e = 3 + e_sum
    print("Numarul de iteratii necesare pentru criteriul de convergenta:", k-1)  # indexarea incepe la 2


def ex7():
    k = 0
    pi_sum = ((-3)**-k) / (2*k + 1)
    pi = math.sqrt(12) * pi_sum

    while abs(math.pi - pi) >= 1e-6:
        k += 1
        pi_sum += ((-3)**-k) / (2*k + 1)
        pi = math.sqrt(12) * pi_sum
    print("Numarul de iteratii necesare pentru criteriul de convergenta:", k+1)  # indexarea incepe la 0


def ex8():
    m = getUserInput("m", float, 0.7, 3.5)
    n = getUserInput("n", int, 4)
    return math.log(m, base=8) / (math.factorial(n-2)**(n**(m-1)))


def ex9():
    e = getUserInput("e", float, 0, 1e-2)
    def func(x): return math.atan(x) + x - 1
    x0 = 0
    x1 = 5
    iter = 1
    x2 = x0
    while abs(func(x2)) >= e:
        iter += 1
        x2 = (x0 * func(x1) - x1 * func(x0)) / (func(x1) - func(x0))

        if func(x2) == 0:
            break
        elif func(x0) * func(x2) < 0:
            x1 = x2
        else:
            x0 = x2
    return iter


def ex10():
    try:
        with open("text.txt", "r") as f:
            lines = f.readlines()
            print(lines)
    except:
        lines = ['3 5\n', '7 8\n', '34.3 130\n', '34.2 -34\n', '8 -18\n', '2 1']
    c = complex(1, -1)
    for line in lines:
        real, imag = [float(a) for a in line.split()]
        z = complex(real, imag)
        ans = abs(c - z) <= 3
        print(f"|{c} - {z}| \t<= 3 : {ans}")


if __name__ == '__main__':
    # print(f"Ex1: {ex1()}")
    # print(f"Ex2: {ex2()}")
    # ex3()
    # print(f"Ex4: {ex4()}")
    # ex5()
    # ex6()
    # ex7()
    # print(f"Ex8: {ex8()}")
    # print(f"Ex9: {ex9()}")
    ex10()
