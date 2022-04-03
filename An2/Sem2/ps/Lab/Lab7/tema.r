# orice secventa in n toss-uti

library(prob)
n <- readline("Cate aruncari? > ")
(tosses <- tosscoin(as.numeric(n)))

sec <- readline("Ce secventa? > ")
tosses_args <- c(tosses, sep = "")
tossresults <- do.call(paste, tosses_args)
a <- subset(tosses, grepl(sec, tossresults, fixed = TRUE))
paste(nrow(a) / nrow(tosses) * 100, "%", sep = "")