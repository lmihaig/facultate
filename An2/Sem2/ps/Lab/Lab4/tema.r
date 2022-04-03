# Tema:
# 1) Folosind pachetul prob creati obiectul moneda5 ce contine toate rezultatele posibile pe care le putem obtine
# la aruncarea succesiva de 5 ori a unei monede. Folosind selectia intr-un dataframe determinati urmatoarele
# probabilitati:
# a)Aparitia secventei TTHTT
# b)Aparitia secventei HTTTH
# c)Numarul de aparitii "H" sa fie mai mare ca numarul de aparitii "T"


library(prob)
(moneda5 <- tosscoin(5))

## a)
a <- subset(tosses, grepl("TTHTT", paste(toss1, toss2, toss3, toss4, toss5, sep = ""), fixed = TRUE))
nrow(a) / nrow(tosses)

## b)
b <- subset(tosses, grepl("HTTTH", paste(toss1, toss2, toss3, toss4, toss5, sep = ""), fixed = TRUE))
nrow(b) / nrow(tosses)

## c)
sum(rowSums(tosses == "H") > rowSums(tosses == "T")) / nrow(tosses)