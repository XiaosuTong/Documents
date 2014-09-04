##http://www.sfu.ca/~sblay/R/snow.html#makeCluster

install.packages("snow")
library(snow)

##
machine <- c("deneb","deneb","mimosa")

##active the workers in the server from the local machine
denebInfo <- list(
  host = "tongx@deneb.stat.purdue.edu",
  rscript = "/usr/local/bin/Rscript",
  snowlib = "/home/median/u41/tongx/R_LIBS"
)
mimosaInfo <- list(
  host = "tongx@mimosa.stat.purdue.edu",
  rscript = "/usr/local/bin/Rscript",
  snowlib = "/home/median/u41/tongx/R_LIBS"
)

cl <- makeCluster(
  c(
#    rep("localhost", 4),
    rep(list(denebInfo), 4), 
    rep(list(mimosaInfo), 1)
  ), 
  type = "SOCK"
)

cl <- makeCluster(machine)
stopCluster(cl)


####################################
##Difference between Call and EvalQ
####################################
##The arguments to clusterCall are evaluated on the master, 
##their values transmitted to the slave nodes which execute the function call.
clusterCall(cl, exp, 1)
clusterCall(cl, runif, 3)

my_func <- function(x) {Sys.sleep(x); cat("Done with ", x, "\n");x}
clusterCall(cl, my_func, 3) #will not show Done with...

##'expr' is treated on the master as a character string
##The expression is evaluated on the slave nodes.
clusterEvalQ(cl, library(lattice))
clusterEvalQ(cl, runif(3))

clusterEvalQ(cl, my_func(3))

ls()
clusterEvalQ(cl, ls())
x<-1
ls()
clusterExport(cl, "x") ## To the global environments of each node
clusterEvalQ(cl, ls())

clusterExport(cl, "my_func")

clusterEvalQ(cl, my_func(3))

#######################
##How parallel works
#######################
my_func <- function(x) {Sys.sleep(x); cat("Done with ", x, "\n"); x}
lapply(1:3, my_func)
clusterApply(cl, 1:3, my_func)


#####################################
##Difference between Apply and ApplyLB
#####################################
element <- c(1,10,2,3)
clusterApply(cl, element, function(r) {
     Sys.sleep(r)
     c(element=r, node=Sys.info()["nodename"])
})

clusterApplyLB(cl, element, function(r) {
     Sys.sleep(r)
     c(element=r, node=Sys.info()["nodename"])
})

####################################
##parApply(cl, X, MARGIN, fun, ...)
###################################
A<-matrix(1:10, 5, 2)
parApply(cl, A, 1, sum)
##'1' indicates rows, '2' indicates columns, 'c(1,2)' indicates rows and columns. 


##################
#Row and column parallel "apply"
###################
parCapply(cl, A, sum)
parRapply(cl, A, sum)

##############################
##parallel version of lapply
#############################
x <- list(alpha = 1:10, beta = exp(-3:3))
parLapply(cl, x, quantile)

##############################
##Sapply
#############################
parSapply(cl, x, quantile)

#################
##Split
##############
clusterSplit(cl, 1:10)
clusterSplit(cl, 1:12)


#########################
##Matrix
########################
A<-matrix(rnorm(10000),100)
system.time(A %*% A)
system.time(parMM(cl,A , A))

A<-matrix(rnorm(4000000),2000)
system.time(A %*% A)
system.time(parMM(cl,A , A))

stopCluster(cl)

