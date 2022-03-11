# Lab3
# Continuare Lab2
# Intermezzo: exemple de tipuri de date
x <- 3.14
y <- 2.44
z <- x + y
# afisez tipul obiectului
typeof(z)
# afisez clasa din care face parte
class(z)
# verific daca este de tip numeric
is.numeric(z)
# definesc o variabila de tip integer
nr_studenti <- as.integer(28)
typeof(nr_studenti / 3)
numar_stud <- 28

# definesc o variabila de tip complex
complex1 <- as.complex(-2 + 2i)
# definesc un obiect ce contine 3 numere complexe si il afisez
(complex2 <- complex(3, 10, 2))
complex22 <- rep(as.complex(10 + 2i), 3)
# complex22 <- rep(complex1,3)

vector_numeric <- c(1, 2, 10)
class(vector_numeric)
vector_caracter <- c("Text", "nou!")
vector_caracter1 <- c("Text", "nou!")
class(vector_caracter1)
(vector_integer <- 1:10)
class(vector_integer)
(vector_integer <- 1.4:10)
class(vector_integer)


class(vector_logic <- c(TRUE, FALSE))
vector_mixt <- c(1, 2, "a", "b", T)
class(vector_mixt)
# Q: De ce vector_mixt este in continuare un vector si nu o lista?

##########################################################################

# I.4 Vectori logici

# sunt creati de obicei prin evaluarea unor expresii logice
x <- sample(1:100, 10)
y <- (x[1:50] < 30)
# Q: Ce este in neregula cu expresia de mai sus?
# NA=not available

# Q: Cum putem elimina in mod automat valorile NA dintr-un vector?
# HINT: is.na()
is.na(y)
z <- x[1:5] < x[6:10]
y <- y[!is.na(y)]


y <- y[which(!is.na(y))]
y1 <- c(NA, NA, y, NA)
y1 <- y1[which(!is.na(y1))]



# Q: Creati un vector logic t ce compara daca elementul de pe pozitia i(impara)
# este mai mic decat elementul de pe pozitia para imediat urmatoare

x <- sample(1:100, 10)
t <- (x[2 * 1:5 - 1] < x[2 * 1:5])

# Q: Determinati pozitiile pentru care conditia de la prima intrebare este adevarata
# HINT: which()
# isTRUE nu poate fi folosit pentru vectori
# t <- t[which(isTRUE(t))]
t1 <- rep(T, 5)
isTRUE(t1)
which(t)

# Q: Determinati cate numere cuprinse intre 483 si 5879 sunt divizibile cu 8
# dar nu cu 7
x <- 483:5879
length(x[(x %% 8 == 0) & (x %% 7 != 0)])

###########################################################################
# Pachetul prob
library(prob)
rolldie(1)
tosscoin(1)


# II.MATRICE

(matrice <- matrix(1:10, nrow = 5, ncol = 2))
# Q: ce se intampla daca nrow sau ncol nu corespund numarului de valori?
matrice[, 2]
# Q: Selectati coloana 1 si liniile 2 si 5 din matrice

# pentru a uni doua linii sau doua coloane intr-o matrice:
nume <- c(letters[1:12])
salarii <- sample(2000:10000, 12)
(tabel1 <- cbind(nume, salarii))
(tabel2 <- rbind(nume, salarii))
class(tabel1)
class(tabel2)

# creare obiecte multidimensionale
(cub <- array(1:12, dim = c(3, 2, 2)))

#-------------------------------------------------------------------------------------------------------------------------

# III. LISTE
# Operatorii [[]] si $
lista <- list(a = 10:20, b = "text", c(TRUE, FALSE, TRUE), 2 + 1i)
length(lista)
lista[[1]][2]
lista$a[5]
class(lista)
class(lista$a)
class(lista[[4]])

#-------------------------------------------------------------------------------------------------------------------------
# IV. DATAFRAMES

rand1 <- letters[6:10]
rand2 <- 1:5
rand3 <- c("text1", "text2", "text3", "text4", "text5")
(textul_meu <- data.frame(rand1, rand2, rand3))
# Functiile unlist si lapply vor fi studiate pe larg in laboratoarele urmatoare
c <- unlist(lapply(textul_meu, class))
class(c)
datasets::mtcars
unlist(lapply(mtcars, class))

# stergerea sau adaugarea
dataframe1 <- mtcars
dataframe1 <- dataframe1[, -c(2:10)]
dataframe1$coloana_noua <- c(1:32)

#-------------------------------------------------------------------------------------------------------------------------
# V.FACTORS

luni <- c("Apr", "Mar", "Feb", "Ian", "Noi", "Oct", "Dec", "Apr", "Mai", "Sep", "Aug", "Ian", "Mai", "Iul", "Iun", "Dec", "Iun", "Aug")
fluni <- as.factor(luni)

# afisarea datelor in tabel
table(fluni)

# pentru ordonarea normala se va utiliza LEVELS si ordered=TRUE
fluni <- factor(luni, levels = c("Ian", "Feb", "Mar", "Apr", "Mai", "Iun", "Iul", "Aug", "Sep", "Oct", "Noi", "Dec"), ordered = TRUE)
fluni
table(fluni)

# pentru a crea subcategorii, se utilizeaza CUT si BREAKES

salarii <- c(1000, 1500, 1200, 1300, 1800, 2000, 1300, 1400, 1600, 2200, 1800, 2100)
# Q: Ce face urmatoarea secventa de cod?
fsalarii <- cut(salarii, breaks = c(1500, 1750, 2000, 2500), include.lowest = TRUE, dig.lab = 4)
table(fsalarii)

# Aplicatii(folosim pachetul prob)
# 1. Aruncarea cu moneda
library(prob)

t3 <- tosscoin(3)
str(t3)
t3$toss2
t3[1, ]
t3[, 1]
# Se arunca o moneda de 3 ori si vrem probabilitatea de aparitie cel putin de 2 ori a H

# Se arunca o moneda o data si vrem probabilitatea de aparitie a H
omega1 <- tosscoin(1)
sum(omega1 == "H") / nrow(omega1)

# Revenim la problema cu 3 aruncari
omega3 <- tosscoin(3)
sum(rowSums(omega3 == "H") >= 2) / nrow(omega3)

# Calculati probabilitatea de aparitie a secventei TT la aruncarea monedei de 3 ori

probTT31 <- (sum((omega3[, 1] == "T") & (omega3[, 2] == "T")) + sum((omega3[, 2] == "T") & (omega3[, 3] == "T"))) / nrow(omega3)

# Q: Calculati probabilitatea de aparitie a secventei TT la aruncarea monedei de 5 ori


# Probabiliatea ca din 3 aruncari sa apara capul cel putin o data
# Q: Comentati urmatoarele alternative de cod: pe care o preferati si de ce?

omega3 <- tosscoin(3)
sum(omega3 == "H") / nrow(omega3)
# SAU
sum(omega3[, 1] == "H" | omega3[, 2] == "H" | omega3[, 3] == "H") / nrow(omega3)
# Alta varianta
sum(rowSums(omega3 == "H") > 0) / nrow(omega3)

# Arunc o moneda de 5 ori si vreau probabilitatea sa obtin cap de 3 ori
omega5 <- tosscoin(5)
sum(rowSums(omega5 == "H") == 3) / nrow(omega5)

# Arunc o moneda de 3 ori si vreau probabilitatea de a obtine secventa HH
omega3$toss1
omega3[, 1]
omega3[6:8, 1:2]
omega3[, -2]
o12 <- omega3[(omega3["toss1"] == "H") & (omega3["toss2"] == "H"), ]
o23 <- omega3[(omega3["toss2"] == "H") & (omega3["toss3"] == "H"), ]

# Determinati probabilitatea ca din 7 aruncari sa obtin 5 H
omega7 <- tosscoin(7)
sum(rowSums(omega7 == "H") == 5) / nrow(omega7)

# Q: Determinati probabilitatea ca din 7 aruncari sa obtinem secventa HH

# Aruncarea unui zar
zar2 <- rolldie(2)
str(zar2)
# Determinati probabilitatea ca la aruncarea a doua zaruri sa se obtina suma 7
# Q: Comentati urmatoarele alternative de cod: pe care o preferati si de ce?
sum(zar2[, 1] + zar2[, 2] == 7)
# SAU
h <- sum(rowSums(zar2) == 7) / nrow(zar2)

# Alta varianta
t <- table(rowSums(zar2)) / nrow(zar2)
str(t)
t[["7"]]

# Jocuri de carti
s <- cards()
str(s)
# Determinati probabilitatea de a extrage o carte de Inima

# Q: Comentati urmatoarele alternative de cod: pe care o preferati si de ce?

sum(s["suit"] == "Heart") / nrow(s)
# SAU
(table(s["suit"]) / nrow(s))[["Heart"]]



##############################################################
# Functiile cbind, rbind
a <- 1:3
b <- 4:6
c <- cbind(a, b)
d <- rbind(a, b)
##############################################################
obis <- rbind(o12, o23)
obis <- unique(obis)

# Jocul de carti
s <- cards()
str(s)
# Vreau probabilitatea de a extrage o carte <7 de inima

####
s[("rank" == "7") & ("suit" == "Heart"), ]
s[(s$rank == 7), ]
p <- s[(s["rank"] == "7") & (s["suit"] == "Heart"), ]
nrow(s[((s["rank"]) == 7) & (s["suit"] == "Heart"), ]) / nrow(s)


# Lucru cu evenimente:
# union(A,B)-reuniune
# intersect(A,B)-intersectia
# setdiff(A,B)-diferenta

# Vreau sa selectez din omega5 randurile 3 si 7 si coloanele 1,3,4
omega5[c(3, 7), c(1, 3, 4)]
omega5[omega5$toss1 == "H", ]
omega5[(omega5["toss1"] == "H") & (omega5["toss2"] == "H"), ]

# Q:Determinati probabilitatea ca din 7 aruncari cel putin 3
# sa fie pare

# Evenimente in R (doar in pachetul prob)
# union(A,B) reuniunea
# intersect(A,B) intersectia
# setdiff(A,B) diferenta

# Calculati probabilitatea ca extragand o carte dintr-un pachet cu
# 52 de carti de joc sa obtinem o valoare >7 si culoare "Spade"
# Reprezentati intai cu evenimente
# Calculati probabilitatea

o["rank" == 7]
o[o["rank"] == 7, ]

# Problema
card <- cards()
A <- card[card["rank"] == "7" |
  card["rank"] == "8" |
  card["rank"] == "9" |
  card["rank"] == "10" |
  card["rank"] == "J" |
  card["rank"] == "Q" |
  card["rank"] == "K" |
  card["rank"] == "A", ]

B <- card[card["suit"] == "Spade", ]
favorabile <- nrow(intersect(A, B))
totale <- nrow(card)
probabilitate <- favorabile / totale

# Tema:
# 1) Folosind pachetul prob creati obiectul moneda5 ce contine toate rezultatele posibile pe care le putem obtine
# la aruncarea succesiva de 5 ori a unei monede. Folosind selectia intr-un dataframe determinati urmatoarele
# probabilitati:
# a)Aparitia secventei TTHTT
# b)Aparitia secventei HTTTH
# c)Numarul de aparitii "H" sa fie mai mare ca numarul de aparitii "T"