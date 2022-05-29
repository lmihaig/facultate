library(discreteRV)
library(MASS)

(X <- RV(c(0, 9), c(.5, .5)))
(Y <- RV(c(-3, 1), c(1 / 7, 6 / 7)))


# I
# 1
scadere_constanta <- X - 1 # acelasi rez
ridicare_putere <- X**-2 # nu merge?
sinus <- sin(pi / 4 * X) # acelasi rez
inmultire_constanta <- Y * 5 # acelasi rez
exponent <- exp(1)^Y # ?

# 2
scadere <- X - Y # acelasi rez
cosinus <- cos(pi * X * Y) # ?
inmultire <- X**2 + 3 * Y # acelasi rez


# 4
fractions(P(scadere > 0)) # acelasi rez
fractions(P((scadere < 0) | (X > 0))) # difera rezultatul
fractions(P((scadere > 0) | (Y <= 0))) # difera
fractions(P(cosinus < 1 / 2)) # nu merge
fractions(P(inmultire >= 3)) # acelasi rez
fractions(P(scadere < inmultire)) # nu am facut de mana dar nu pare ok

# II
plot(scadere_constanta)
plot(sinus)
plot(inmultire_constanta)
plot(scadere)
plot(inmultire)