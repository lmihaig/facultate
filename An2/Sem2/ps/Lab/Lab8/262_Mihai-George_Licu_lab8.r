# eficientizat codul si aflat alte pattern-uri "vineri 13"
# am observat ca e un pattern ce se repeta (pana in ziua de 29 cred) dar am vrut sa generez toate posibilitatile
dates <- seq.Date(as.Date("1601-01-01"), as.Date("2000-12-31"), by = 1)
days <- 1:31

func <- function(day) {
    good_dates <- weekdays(dates[as.numeric(format(dates, format = "%d")) == day])
    table(good_dates)
}

system.time(all_days <- sapply(days, func))
t(all_days)


# sus 10s
# asta 40s
#
# fullyears <- 1601:2000
# months <- 1:12
# testthirteenth <- NULL
# system.time(for (i in 1:length(fullyears)) {
#     for (j in 1:12) {
#         for (x in 1:31)
#         {
#             testthirteenth <- c(testthirteenth, weekdays(as.Date(paste(
#                 fullyears[i], "/", months[j], "/", x,
#                 sep = ""
#             ), "%Y/%m/%d")))
#         }
#     }
# })
# t2 <- table(testthirteenth)



# Avem n bile numerotate de la 1 la n pe care le punem, in mod aleator, in N urne disponibile.
# Cu ce probabilitate prima urna contine k bile?

n <- 100
k <- 3
(prob_n <- ((factorial(n) / (factorial(k) * factorial(n - k))) * (n - 1)^(n - k)) / n^n)