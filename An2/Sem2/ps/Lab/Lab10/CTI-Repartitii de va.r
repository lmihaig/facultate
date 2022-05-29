#Repartitii de v.a.
#1.d+nume_repartitie=functie de masa(caz discret)/functia de densitate de probabilitate(caz continuu)
#primul argument reprezinta vectorul de valori in care vrem sa evaluam functia, iar pe urmatoarele pozitii
#sunt parametrii repartitiei, pusi in ordine
#dgeom(x,p)
#dbinom(x,n,p)
#Ce inseamna?
dbinom(3,5,0.4) #Probabilitatea sa reusesc de 3 ori din 5 incercari cu probabilitatea de succes de 0.4
#P(X=3)
plot(0:10,dbinom(0:10,5,0.4), col="red")
lines(0:10,dbinom(0:10,5,0.4), col="red")

plot(0:10,dbinom(0:10,5,0.9), col="red")
lines(0:10,dbinom(0:10,5,0.9), col="red")

plot(0:10,dbinom(0:10,5,0.1), col="red")
lines(0:10,dbinom(0:10,5,0.1), col="red")

plot(0:100,dbinom(0:100,100,0.4), col="red")
lines(0:100,dbinom(0:100,100,0.4), col="red")

#dgeom(x,p)
dgeom(5,0.4)
#probabilitatea ca primul succes sa se realizeze la a 6-a incercare (am 5 esecuri) stiind ca
#probabilitatea de succes este 0.4
plot(0:10,dgeom(0:10,0.4))
plot(0:10,dgeom(0:10,0.9))
plot(0:10,dgeom(0:10,0.05))

t <- seq(-3,7,0.001)
#X~Unif(a,b)
#f(x)=1/(b-a) pt x in intervalul (a,b) si 0 in rest

plot(t,dunif(t,0,3),col="red")
abline(v=0,col="red")
abline(v=3,col="red")
abline(h=0,col="red")
abline(v=1,col="blue")
abline(v=2,col="blue")
abline(v=3,col="blue")
abline(v=0.5,col="blue")
abline(v=1.5,col="blue")


#dexp(x,lambda)
dexp(3,1) #NU mai e o probabilitate
t <- seq(0.001,10,0.001)
plot(t,dexp(t,1),ylim=c(0,0.05))
plot(t,dexp(t,5))
lines(t,dexp(t,1/2), col="red")
lines(t,dexp(t,1),col="blue")


#2. p+nume_repartitie=functia de repartitie
    ##primul argument reprezinta vectorul de valori in care vrem sa evaluam functia, iar pe urmatoarele pozitii
#sunt parametrii repartitiei, pusi in ordine
 #  pbinom(x,n,p)
   #P(X<=x)
   pbinom(3,5,0.4) #Probabilitatea sa obtinem cel mult 3 succese din 5 incercari cu probabilitatea de succes de 0.4
   t <- seq(0,8,0.001)
   plot(t,pbinom(t,5,0.4))
   plot(t,pexp(t,1))
   lines(t,pexp(t,1/2), col="red")
   lines(t,pexp(t,5),col="blue")
   
   
   #3. r+nume_repartitie=genereaza valori din acel tip de repartitie
 #  rbinom(nr,n,p)
   #nr-numarul de valori pe care le vrem generate
   
   rbinom(3,5,0.4) # genereaza 3 valori dintr-o v.a. repartizata binomial cu parametrii 5 si 0.4
   y <- rbinom(10^6,5,0.4)
   hist(y)
   
   rexp(3,1) # genereaza 3 valori dintr-o v.a. repartizata exponential de parametru 1
   y1 <-rexp(10^6,1)
   hist(y1,freq=F)
   t <- seq(0.001,8,0.001)
   lines(t,dexp(t,1),col="magenta")
   #daca generez un esantion mic, potrivirea nu mai e la fel de spectaculoasa
   y2 <-rexp(100,1)
   hist(y2,freq=F)
   t <- seq(0.001,8,0.001)
   lines(t,dexp(t,1),col="magenta")
   
   #Functia sample
   set.seed(6) 
   sample(1:40,5) #presupune ca extragerile sunt fara revenire si valorile sunt egal probabile
   #(se foloseste repartitia uniforma discreta)
   sample(1:40,400, replace=T) #extrageri cu revenire
   x <- sample(1:3,10^6,replace=T,prob=c(1/2,1/3,1/6))
   table(x)/10^6 
   x1 <- sample(1:3,10,replace=T,prob=c(1/2,1/3,1/6))
   table(x1)/10
   
   
   #Reprezentari grafice de functii
   #Functia densitate de probabilitate a repartitiei normale
   t <- seq(-6,6,0.001)
   plot(t,dnorm(t,0,1))
   
   plot(t,dexp(t,2),ylim=c(0,0.))
   #ATENTIE: IN R parametrii normalei sunt media si abaterea medie standard
   y <- rnorm(100,0,1)
   
   poz <- y[y>0]
   prob_nr_poz <- length(poz)/10^2
   neg <- y[y<0]
   prob_nr_neg <- length(neg)/10^2
   
   y <- rnorm(1000000,0,1)
   
   length(y[(y>-3)&(y<3)])
  
   lines(t,dnorm(t,0,1))
   plot(t,dnorm(t,3,1),col="magenta",xlim=c(-8,8),ylim=c(0,1))
   lines(t,dnorm(t,3,4), col=2)
   lines(t,dnorm(t,3,0.5), col=3)
   lines(t,dnorm(t,3,2), col=5)
   lines(t,dnorm(t,3,0.5),col=1)
   
   z <- rnorm(1000,2,1)
   length(z[z< -2])
   
   plot(t,dnorm(t,0,1),col="magenta",ylim=c(0,1.8))
   for (i in c(0.25,0.5,0.3,0.9,1.3,2)) lines(t,dnorm(t,0,i), col=i*20)
   