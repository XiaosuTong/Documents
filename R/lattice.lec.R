##1. data.frame
barley
barley$year
barley$yield
names(barley)
dim(barley)
head(barley)
str(barley)
attributes(barley)
##In R every "object" has a mode and a class. The former represents how an object is stored in memory (numeric, character, list and function) while the later represents its abstract type. 
class(barley)
typeof(barley)
mode(barley)
barley[1:10,]
barley[,-1]
subset(barley, year == 1931)
barley[order(barley$yield),]
rbind
cbind

##2. list
data <- data.frame(a=11, b=2, c=3)
tmp1 <- list(c(1:10), c("a", "b", "c"), data)
tmp1[1]
tmp1[[1]]

tmp2 <- list(list(1, runif(1)), list(2, runif(1)), list(3, runif(1)))
tmp2[[3]][[1]]

lapply(1:10, function(x){x+1})
lapply(tmp2, "[[", 2)
do.call("c", lapply(tmp2, "[[", 2))
tapply(barley$yield, barley$year, mean)

##3. library set up
PATH_TO_LIBS <- "H:/My\ Documents/R_LIBS"
install.packages("plyr", lib=PATH_TO_LIBS)
library(plyr, lib.loc=PATH_TO_LIBS)
#R function .libPaths() gets and sets the search path of R packages
#Call .libPaths() with no arguments shows the current search path
.libPaths()
#By default, R installs packages to the first element of .libPaths()
#When load packages, R searches in all elements of .libPaths()
.libPaths(c("H:/My\ Documents/R_LIBS",.libPaths()))
install.packages("plyr")
library(plyr)

#Create a new file named “.Rprofile” with the following line
.libPaths(c("H:/My\ Documents/R_LIBS",.libPaths()))

