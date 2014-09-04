######################################
##Two warm up example from Ryan's web
##The dataset is the iris
######################################

inputdir <- "/wsc/tongx/userhipe/"
outputdir <- "/wsc/tongx/userhipe/output/"

##Example 1.1
##The first example is working on the data which divided by iris$Species, 
##and then make a list of key/value pairs, keys are the Species, and the
##values are the data.frame of data for the Species.
bySpecies <- lapply(unique(iris$Species), function(x) {
    list(as.character(x), subset(iris, Species==x))
})
##Write the bySpecies list to the HDFS.
rhwrite(bySpecies, "/userhipe/bySpecies")

m.ex1.1 <- expression({
   lapply(seq_along(map.values), function(r) {
      v <- map.values[[r]]
      k <- map.keys[[r]]
      rhcollect(k, mean(v$Petal.Length))
   })
})

ex <- rhwatch(
        map = m.ex1.1,
#       reduce = reduce,
        input = rhfmt(paste(inputdir, "bySpecies", sep=""), type="sequence"),
        output = rhfmt(paste(outputdir, "ex1.1", sep=""), type="sequence"),
        mapred = list(mapred.map.tasks = 50, mapred.reduce.tasks = 4),
        jobname = "ex1.1",
        readback = FALSE,
		noeval = TRUE
)


##Example 3.1
##The second example is working on the random partition of iris.
##There are 10 subsets, each has randomly 15 rows from iris.
byRandom <- lapply(1:10, function(i){
	s <- sample(1:nrow(iris),15)
	v <- iris[s,]
	iris <- iris[-s,]
	list(i, v)
})
##Write the bySpecies list to the HDFS.
rhwrite(byRandom, "/userhipe/byRandom")

m.ex3.1 <- expression({
   lapply(seq_along(map.values), function(r) {
      v <- map.values[[r]]
      k <- map.keys[[r]]
 
      tmp <- by(v, v$Species, function(x) list(let=x$Species[1], sum=sum(x$Petal.Length), n=nrow(x)))
 
      lapply(tmp, function(ll) {
         rhcollect(as.character(ll$let), data.frame(tot=ll$sum, n=ll$n))
      })
   })
})

r.ex3.1 <- expression(
   pre={
      total <- 0
      nn <- 0
   },
   reduce={
      tmp <- do.call(rbind, reduce.values)
      total <- total + sum(tmp$tot)
      nn <- nn + sum(tmp$n)
   },
   post={
      d <- data.frame(let=reduce.key, res=total/nn)
      rhcollect(reduce.key, d)
   }
)

ex <- rhwatch(
        map = m.ex3.1,
        reduce = r.ex3.1,
        input = rhfmt(paste(inputdir, "byRandom", sep=""), type="sequence"),
        output = rhfmt(paste(outputdir, "ex3.1", sep=""), type="sequence"),
        mapred = list(mapred.map.tasks = 50, mapred.reduce.tasks = 1),
        jobname = "ex3.1",
        readback = FALSE
)

##Example3.1 with combiner.
r.ex3.1.combine <- expression(
   pre={
      total <- 0
      nn <- 0
   },
   reduce={
      tmp <- do.call(rbind, reduce.values)
      total <- total + sum(tmp$tot)
      nn <- nn + sum(tmp$n)
   },
   post={
      rhcollect(reduce.key, data.frame(tot=total, n=nn))
   }
)

ex <- rhwatch(
        map = m.ex3.1,
        reduce = r.ex3.1.combine,
        input = rhfmt(paste(inputdir, "byRandom", sep=""), type="sequence"),
        output = rhfmt(paste(outputdir, "ex3.1combine", sep=""), type="sequence"),
        mapred = list(mapred.map.tasks = 50, mapred.reduce.tasks = 5),
        jobname = "ex3.1combine",
        readback = FALSE
)

