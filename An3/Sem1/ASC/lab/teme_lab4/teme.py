import math
import cmath
from typing import Any, Set


def getUserInput(var_name: str, var_type: callable) -> float:
    while True:
        x = input(f"Introduceti numarul {var_name}:")
        try:
            if float(x) == var_type(float(x)):
                return var_type(x)
            else:
                print(f"Numarul nu este {var_type.__name__}")
        except ValueError as e:
            print("Valoare nu este un numar in baza 10")
            print(e)
        except Exception as e:
            print("Eroare necunoscuta")
            print(e)


def ex_1() -> int:
    x = getUserInput("x", int)
    try:
        return math.factorial(x)
    except ValueError as e:
        print("Numarul nu este pozitiv")
        print(e)
    except Exception as e:
        print("Eroare necunoscuta")
        print(e)


def ex_2() -> Set[Any]:
    print("a*x^2 + b*x +c = 0")
    a = getUserInput("a", float)
    b = getUserInput("b", float)
    c = getUserInput("c", float)
    if a == 0:
        print("Pentru ecuatie de gradul 2 termenul 'a' trebuie sa fie pozitiv")
        return None

    delta = b**2 - 4*a*c
    if delta >= 0:
        x_1 = (-b + math.sqrt(delta))/(2*a)
        x_2 = (-b - math.sqrt(delta))/(2*a)
    else:
        x_1 = complex(-b/(2*a), cmath.sqrt(-delta)/(2*a))
        x_2 = complex(-b/(2*a), -cmath.sqrt(-delta)/(2*a))
    return set([x_1, x_2])


def ex_3() -> int:
    n = getUserInput("n", int)
    return sum([n**i for i in range(1, 4)])


def ex_4() -> float:
    r = getUserInput("r", float)
    return r**2 * math.pi


def ex_5() -> float:
    a = getUserInput("a", float)
    return a**3


if __name__ == '__main__':
    # print(f"Factorial: {ex_1()}")
    # print(f"Radacini: {ex_2()}")
    # print(f"Valoarea expresiei: {ex_3()}")
    # print(f"Aria cercului: {ex_4()}")
    # print(f"Volumul cubului: {ex_5()}")
