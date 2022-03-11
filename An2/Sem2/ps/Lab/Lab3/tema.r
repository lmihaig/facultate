# To do

# Construiti doi vectori x si y cu 1000 de elemente fiecare, extrase in mod
# aleator din multimea cu numere intregi -34000:45000. Stabiliti care dintre cei
# doi vectori are mai multe elemente, luate in valoare absoluta, mai mari decat
# valoarea absoluta a elementului corespondent din celalalt vector


x <- sample(-34000:45000, 1000)
y <- sample(-34000:45000, 1000)

m <- sum(abs(x) < abs(y))
n <- sum(abs(x) > abs(y))

if (n > m) {
    cat("X are", n - m, "mai multe elemente mai mari (in modul):", n, "vs", m)
} else if (n < m) {
    cat("Y are", m - n, "mai multe elemente mai mari (in modul):", m, "vs", n)
} else {
    print("Vectorii au un numar egal de elemente mai mari (in modul): ", n)
}