# Ultimul laborator CTI


# Legea numerelor mari
# Zarul reprezinta X~Uniform(1,2,...100)
# E[X]=1*1/100+2*1/100+...100*1/100=1/100*100*101/2=50.5
zar <- 1:100

########## Functia sample
set.seed(111)
x <- sample(1:5, 3) # implicit foloseste repartitia uniforma si extragerile sunt fara revenire

sample(1:5, 10, replace = T) # Trebuie sa fac extrageri cu revenire daca vreau sa extrag 10 valori din 5 disponibile
x <- sample(1:5, 10000, replace = T, prob = c(1 / 10, 2 / 10, 3 / 10, 2 / 10, 2 / 10))
table(x) / 10^4

##############################################################################
# Functia care va realiza esantionarea
# n este numarul de aruncari (dimensiunea esantionului)

arunca <- function(n) {
  mean(sample(zar, size = n, replace = TRUE))
}

# sapply(1:10000, arunca) este echivalent cu apelul functiei arunca, pe rand, cu toate valorile
# de la 1 la 10 000
plot(sapply(1:10000, arunca), type = "o", xlab = "numarul de aruncari", ylab = "media")
# Functia abline deseneaza drepte orizontale(h=ceva) sau verticale(v=ceva) peste un grafic
abline(h = 50.5, col = "red")



# TEMA: Ilustrati LNM pt. repartiile binomiala, poisson si exponentiala
# (folositi rbinom, rpois si rexp)





# Teorema limita centrala
alt_zar <- sample(1:100, 10000, replace = TRUE)
hist(alt_zar, col = "light blue")
abline(v = 50.5, col = "red")

x10 <- c()
k <- 10000
for (i in 1:k) {
  x10[i] <- mean(sample(1:100, 10, replace = TRUE))
}
hist(x10, col = "pink", main = "Esantion de volum 10", xlab = "Rezultatul aruncarii", freq = F)
abline(v = mean(x10), col = "Red")
abline(v = 50.5, col = "blue")
t <- seq(20, 80, 0.001)
lines(t, dnorm(t, mean(x10), sd(x10)), col = "red")



x30 <- c()
x100 <- c()
x1000 <- c()

for (i in 1:k) {
  x30[i] <- mean(sample(1:100, 30, replace = TRUE))
  x100[i] <- mean(sample(1:100, 100, replace = TRUE))
  x1000[i] <- mean(sample(1:100, 1000, replace = TRUE))
}

# functia par imi permite sa gestionez parametri grafici
# mfrow cere un vector cu 2 valori dintre care prima reprezinta numarul de linii si a doua numarul
# de coloane in care va fi impartit spatiul de plotare
par(mfrow = c(1, 3))
hist(x30, col = "green", main = "n=30", xlab = "Rezultatul aruncarii", freq = F)
abline(v = mean(x30), col = "blue")
t1 <- seq(30, 70, 0.001)
lines(t1, dnorm(t1, mean(x30), sd(x30)), col = "magenta")

hist(x100, col = "light blue", main = "n=100", xlab = "Rezultatul aruncarii")
abline(v = mean(x100), col = "red")
t <- seq(40, 60, 0.001)
lines(t, dnorm(t, mean(x100), sd(x100)), col = "magenta")

hist(x1000, col = "orange", main = "n=1000", xlab = "Rezultatul aruncarii", freq = F)
abline(v = mean(x1000), col = "red")
t <- seq(47, 54, 0.001)
lines(t, dnorm(t, mean(x1000), sd(x1000)), col = "magenta")

par(mfrow = c(1, 1))


# Tema: Ilustrati TLC pentru repartitiile: Poisson, Geometrica si Exponentiala pentru toate cele 4 dimensiuni de esantion




# Metoda verosimilitatii maxime
# Daca o functie cu valori pozitive are punct de maxim sau minim local, acesta se pastreaza si daca se
# logaritmeaza functia initiala

f1 <- function(x) {
  sin(x)
}

t <- seq(0.001, 4 * pi - 0.001, 0.001)
plot(t, f1(t)) # xlim=c(1.25,1.75))
lines(t, log(sin(t)), col = "blue") # Atentie la NaNs
abline(v = pi / 2, col = "red")

# gasirea punctelor de extrem cu functia optimize
require(graphics)
# in mod implicit cauta punctul de minim
optimize(f1, c(0.001, pi - 0.001))

# vreau punctul de maxim

optimize(f1, c(0.001, pi - 0.001), maximum = T)

# const=ln(produs(xi^2))
# x este vectorul ce reprezinta esantionul dat
x <- rgamma(100, 3, scale = 2)
n_calc <- 100
hist(x, freq = F)
t <- seq(0, 25, 0.0001)
lines(t, dgamma(t, 3, scale = 2), col = "magenta")
xbar_calc <- sum(x) / n_calc
const_calc <- sum(2 * log(x))

logVerosim <- function(teta, xbar, n, const) {
  -n * log(2) - 3 * n * log(teta) + const - 1 / teta * n * xbar
}


o <- optimize(logVerosim, c(0.001, 100), maximum = T, xbar = xbar_calc, n = n_calc, const = const_calc)
teta_maxim <- o$maximum

teta_estimat <- xbar_calc / 3

# Observam ca teta_estimat si teta_maxim(calculat prin metode numerice) sunt foarte apropiate


t <- seq(1.8, 2.2, 0.00001)
plot(t, logVerosim(t, xbar_calc, n_calc, const_calc), type = "l")
abline(v = teta_maxim, col = "red")