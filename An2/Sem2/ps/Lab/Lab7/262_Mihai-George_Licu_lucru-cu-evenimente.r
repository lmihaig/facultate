library(prob)

# 1.
# A = sa apara cel putin un 2 din 7 aruncari cu zarul
# B = sa nu apara nici un 2 din 7 aruncari cu zarul
# P(A) = 1 - P(B)
(1 - (5 / 6)^7)

# 2.
# 6*6 = 36 posibilitati
# A = d2 > d1
# B = d2 < d1
# C = d2 == d1 => 6/36
# P(A) + P(B) + P(C) = 1 && P(A) = P(B) => 15/36
(36 / 36 - 6 / 36) / 2

# 3.
# a+b = 5 => (2+3, 4+1)*2
# a+b = 8 => (6+2, 5+3)*2 + (4,4)
# A inainte de B + B inainte de A = 1
(A <- 4 / 36)
(B <- 5 / 36)
A / (A + B)

# 4.
# A = dubla 6 , P(A) = 1/36
# B = nu dubla 6, P(B) = 35/36
# 1-(35 / 36)^n >= 0.5
(n <- round(log(0.5) / log(35 / 36)))

# 5.
# En = A_n si A_n+1 sunt cuplu
# 1 - prob(E1 U E2 U E3 U E4 U E5)
# ?

# 6.
prod((12 - 12 + 1):12 / 12)

# 7.
# prod((365 - n + 1):365 / 365) < 0.5
n <- 0
prb <- 1
while (prb >= 0.5) {
    prb <- prod((365 - n + 1):365 / 365)
    n <- n + 1
}
print(n - 1)
# 23

# 8.
# ?


# 9.
# evenimente dependente * combinari(6,3)
prod(4:6 / 7:12) * factorial(6) / (factorial(3) * factorial(6 - 3))

# 10.
# ?

# 11.
# ?

# 12.
# cu eliminare: n-1/n * n-2/n-1 * n-3/n-2 *.....*  *1/n-k = 1/n
n <- 30
k <- 3
1 / n

# fara eliminare: (n-1/n)^(k-1) * 1/n
((n - 1) / n)^(k - 1) * (1 / n)

# 13.
# presupunere: toate distincte intre ele
# nr total de modalitati de cazare
caz <- 14^3
# cazari la hoteluri diferite
opt <- 14 * 13 * 12
opt / caz

# 14.
# 3/n * 2/n-1 = 0.5
n <- 100
while ((3 / n * 2 / (n - 1)) != 0.5) {
    n <- n - 1
}
n
# 4 sosete


# 15.
intrebari_total <- factorial(100) / (factorial(5) * factorial(100 - 5))
# 5/5
fav <- factorial(80) / (factorial(5) * factorial(80 - 5))
(full <- fav / intrebari_total)

# cel putin 4
fav <- factorial(80) / (factorial(4) * factorial(80 - 4)) * factorial(20) / (factorial(1) * factorial(20 - 1))
fav / intrebari_total + full

# 0/5
fav <- factorial(20) / (factorial(5) * factorial(20 - 5))
fav / intrebari_total

# 2/5
fav <- factorial(80) / (factorial(2) * factorial(80 - 2)) * factorial(20) / (factorial(3) * factorial(20 - 3))
fav / intrebari_total

# 16.
# a) flush
prod((52 / 4 - 5 + 1):(52 / 4) / (52 - 5 + 1):52)
(factorial(13) / (factorial(5) * factorial(13 - 5))) / (factorial(52) / (factorial(5) * factorial(52 - 5)))

# b) pereche => 1- nici o pereche
1 - factorial(13) / (factorial(5) * factorial(13 - 5)) * 4^5 / (factorial(52) / (factorial(5) * factorial(52 - 5)))

# c) ?


# 17.
# a) ambele as
4 / 52 * 3 / 51

# b) aceeasi valoare
3 / 51

# c) ambele carti mici [2:9]
(((9 - 2) * 4) / 52) * (((9 - 2) * 4 - 1) / 51)

# d) prima valoare mai mica ca a doua
# 1 = egala + mai mare + mai mica
# egala = 3/51
# mai mare = mai mica
(1 - 3 / 51) / 2


# 18.
# a)
total_hands <- (factorial(52) / (factorial(13) * factorial(52 - 13)))
((factorial(50) / (factorial(11) * factorial(50 - 11))) / total_hands)

# b)
(factorial(13) / (factorial(1) * factorial(13 - 1))) * (factorial(48) / (factorial(9) * factorial(48 - 9))) / total_hands

# 19.
(52 / 52) * ((52 - 13 * 1) / 51) * ((52 - 13 * 2) / 50) * ((52 - 13 * 3) / 49) * (48 / 48)

# 20.
# a) toate valori diferite
total_hands <- (factorial(52) / (factorial(5) * factorial(52 - 5)))
(factorial(13) / (factorial(5) * factorial(13 - 5)) * 4^5 / total_hands)

# b) toate culori diferite
# sunt 5 carti doar 4 culori, e imposibil sa fie toate diferite
0


# 21. ??

# 22. ?

# 23. toate cartile inima
# a)
1 / (factorial(52) / (factorial(13) * factorial(52 - 13)))

# b) ?