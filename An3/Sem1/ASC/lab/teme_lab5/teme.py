import math
import matplotlib.pyplot as plt


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


def Wallis_graph() -> float:
    k = getUserInput("k", int)
    if k < 2:
        print("K > 1")
        return 0
    pi_est = [(4 * n**2) / (4 * n**2 - 1) for n in range(1, k)]
    pi_plots = [2 * math.prod(pi_est[:i]) for i in range(1, k)]

    fig, ax = plt.subplots()
    ax.axhline(y=math.pi, color="r", label="real value of pi", linewidth=3)
    ax.plot(
        [i for i in range(1, k)],
        pi_plots,
        "bo--",
        linewidth=1,
        markersize=4,
        mfc="green",
        mec="green",
    )
    ax.set_xlim(xmin=1)
    ax.set_ylim(ymin=pi_plots[0])
    plt.ylabel("Value of PI")
    plt.xlabel("estimate #")
    plt.title("Estimation of PI with Wallis formula")

    plt.show()

    return pi_plots[-1]


def Wallis_estimate_steps() -> int:
    # ? input = 3.14 -> output = 492
    precision = getUserInput("precision", float)
    if precision > math.pi:
        return "Invalid precision"
    i = 1
    pi_est = [(4 * i**2) / (4 * i**2 - 1)]
    while True:
        est = 2 * math.prod(pi_est)
        if est == precision:
            return i
        elif est > precision:
            return i - 1
        i += 1
        pi_est.append((4 * i**2) / (4 * i**2 - 1))


if __name__ == "__main__":
    Wallis_graph()
    print("Number of steps: ", Wallis_estimate_steps())
