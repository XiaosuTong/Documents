## Rhipe setup
n.1 = 1000
rep = 10
B0 = 2.5
B1 = 3
#n.2 = 1000

#you have to define the n.2 in rhmr function.
map1 = expression({
   for(i in seq_along(map.values)){
     X = runif(n.2)
     Y = runif(B0 + B1 * X)
     rhcollect(map.keys[[i]], list(X = X, Y = Y))
   }
})

mr = rhwatch(
  parameters = list(n.2 = n.1, B0 = B0, B1 = B1),
  map = map1,
  input = c(rep,5),
  output =paste("/ln/tongx/lmsimoutput"),
  #inout = c('lapply', 'sequence'),
  #N = rep,
  mapred = list( mapred.reduce.tasks = 0),
  readback = FALSE
)

#ex = rhex(mr, async = FALSE)

########################################################

map2 = expression({
  for(i in seq_along(map.keys)){  
#Why cannot I just use: for(i in map.keys)?
#Because the map.keys is just a number randomly choosed from 1 to N if we use 'lapply' as input.
    lm.out = lm(map.values[[i]]$Y ~ map.values[[i]]$X)$coe
    rhcollect(map.keys[[i]], lm.out)
  }
})

reduce2 = expression(
  pre ={ c = rep(0,2)},
  reduce = { c = c + apply(matrix(unlist(reduce.values),ncol=2,byrow=TRUE),2,mean)},
  post = {rhcollect(1,c)}
)
#the reduce.values and reduce.keys are the same as the map.values and map.keys
#Map stage is a function: (key, value) -> (key, value)'. 
#Reduce stage is another function: (key, value)' -> anything.
mr2 = rhwatch(
  map = map2,
  reduce = reduce2,
  input = paste("/ln/tongx/lmsimoutput"),
  output = paste("/ln/tongx/lmsimcoef"),
  #sometimes we can add an option jobname = paste().
  #inout = c('sequence', 'sequence'),
  #combiner = TRUE,
  #Have to include the combiner option when we want to combine the results on one node.
  mapred = list( mapred.map.tasks = 10, mapred.reduce.tasks = 10),
  readback = FALSE
)

#ex = rhex(mr2, async = FALSE)

myresults = rhread("/ln/tongx/lmsimcoef")

#vector of beta_1_hat
#unlist(lapply(myresults, function(x) x[[2]][[2]]))

