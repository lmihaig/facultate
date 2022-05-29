#Cateva problema interesante
#1. Problema cu vineri 13
fullyears <- 1601:2000
months <- 1:12
testthirteenth <- NULL
for(i in 1:length(fullyears)) {
  for(j in 1:12){
    testthirteenth <- c(testthirteenth,weekdays(as.Date(paste(
      fullyears[i],"/", months[j],"/13",sep=""),"%Y/%m/%d")))
  }
}
t2 <- table(testthirteenth)
#testthirteenth
#TEMA: Puteti eficientiza codul?


#2. #Afisati valoarea factorialului pentru numerele de la 1 la 20
f <- factorial(1:20)
#sau
f <- sapply(1:20, factorial)

#3. Avem n bile numerotate de la 1 la n pe care le punem, in mod aleator in n urne disponibile.
#Cu ce probabilitate fiecare urna contine o bila?
n <- 1:10
prob_n <- factorial(n)/n^n
plot(n,prob_n,type="h") #,main="Tralalala"
title("Probabilitatea ca toate urnele sa contina o bila")

#Tipurile din plot

#implicit type="p" <- puncte
plot(1:5,1:5,type="p")
#type="l" <- linii
plot(1:5,1:5,type="l")
#type="b" <- both, atat punctele cat si liniile dintre ele
plot(1:5,1:5,type="b")
#type="o" <- overlay, pune linii peste puncte
plot(1:5,1:5,type="o")
#type="h" <- deseneaza bare verticale
plot(1:5,1:5,type="h")
#type="n" <- nu deseneaza nimic, doar axele
plot(1:5,1:5,type="n")

# TEMA: Avem n bile numerotate de la 1 la n pe care le punem, in mod aleator, in N urne disponibile.
#Cu ce probabilitate prima urna contine k bile?

#4 Problema zilelor de nastere
#Avem un grup de k persoane si 365 de zile de nastere posibile. 
#Determinati probabilitatea ca toate persoanele sa aiba zile de nastere distincte. 
#Determinati probabilitatea ca cel putin 2 persoane sa aiba aceeasi data de nastere.
k <- c(2,5,10,20,30,40,50)
probdiff <- c()
probat2lafel <- c()
for(i in 1:length(k)) {
  kk <- k[i]
  probdiff[i] <- prod(365:(365-kk+1))/(365 ^kk)
  probat2lafel[i] <- 1- prod(365:(365-kk+1))/(365 ^ kk)
}
plot(k,probat2lafel,xlab="Numarul de studenti",ylab="Probabilitatea zilei de nastere",col="green","l")
lines(k,probdiff,col="red","l")
legend(10,1,"Zilele de nastere nu coincid",box.lty=NULL)
legend(30,.7,"Zilele de nastere coincid",,box.lty=NULL)
title("Problema zilelor de nastere")
abline(v=23)
abline(h=0.5)
#Tema: de eficientizat acest cod