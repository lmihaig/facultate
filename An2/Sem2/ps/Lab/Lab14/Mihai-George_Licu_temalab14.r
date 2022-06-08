# TEMA: Ilustrati LNM pt. repartiile binomiala, poisson si exponentiala
# (folositi rbinom, rpois si rexp)
rm(list = ls())
par(mfrow = c(2, 2))

zar <- 1:100

arunca_un <- function(n) {
    mean(sample(zar, size = n, replace = TRUE))
}

arunca_bin <- function(n) {
    mean(rbinom(n, size = zar, prob = 1 / tail(zar, n = 1)) * 100)
}

arunca_pois <- function(n) {
    mean(rpois(n, mean(zar)))
}

arunca_exp <- function(n) {
    mean(rexp(n, zar)) * 1000
}

plot(sapply(1:10000, arunca_un), main = "Rep uniforma", type = "o", xlab = "numarul de aruncari", ylab = "media")
abline(h = 50.5, col = "red")
plot(sapply(1:10000, arunca_bin), main = "Rep binom", type = "o", xlab = "numarul de aruncari", ylab = "media")
abline(h = 50.5, col = "red")
plot(sapply(1:10000, arunca_pois), main = "Rep poisson", type = "o", xlab = "numarul de aruncari", ylab = "media")
abline(h = 50.5, col = "red")
plot(sapply(1:10000, arunca_exp), main = "Rep exp", type = "o", xlab = "numarul de aruncari", ylab = "media")
abline(h = 50.5, col = "red")



# Tema: Ilustrati TLC pentru repartitiile: Poisson, Geometrica si Exponentiala pentru toate cele 4 dimensiuni de esantion
par(mfrow = c(1, 3))

tlc <- function(func, name) {
    x30 <- c()
    x100 <- c()
    x1000 <- c()

    for (i in 1:10000) {
        x30[i] <- func(30)
        x100[i] <- func(100)
        x1000[i] <- func(1000)
    }

    t <- seq(30, 70, 0.001)
    hist(x30, col = "blue", main = "n=30", freq = F)
    abline(v = mean(x30), col = "magenta")
    lines(t, dnorm(t, mean(x30), sd(x30)), col = "magenta")

    hist(x100, col = "yellow", main = "n=100", freq = F)
    abline(v = mean(x100), col = "magenta")
    lines(t, dnorm(t, mean(x100), sd(x100)), col = "magenta")

    hist(x1000, col = "red", main = "n=1000", freq = F)
    abline(v = mean(x1000), col = "magenta")
    lines(t, dnorm(t, mean(x1000), sd(x1000)), col = "magenta")

    title(main = name, line = -1, outer = TRUE)
}

tlc(arunca_un, "Uniforma")
tlc(arunca_bin, "Binomiala")
tlc(arunca_pois, "Poisson")
tlc(arunca_exp, "Exponentiala")