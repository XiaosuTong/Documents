inputdir <- "/ln/tongx/userhipe/"
outputdir <- "/ln/tongx/userhipe/output/"

## creating fack dataset1 which has 64 subsets of size 16MB each
map <- expression({
	lapply(seq_along(map.values), function(r){
		k <- 1
		set.seed(r)
		v <- runif(2^21) ##each float value is 8 bytes, this is totally 16MB
        	rhcollect(k, v)
	})
})

mr <- rhwatch(
        map = map,
        input = c(2^6,6), ##64 subsets to make sure the total size is 1Gb
	##You can specify as many # of map tasks as you want, this only control how many 
	##nodes will be used to run the map tasks.
        output = rhfmt("/ln/tongx/userhipe/size1GB.each16MB", type="sequence"),
	jobname = "size.buff",
        readback = FALSE	
        #inout = c('lapply','sequence'),
        #N = 10,
        #mapred = list( mapred.map.tasks=3, mapred.reduce.tasks=0 )
)

a <- rhread("/ln/tongx/userhipe/size1GB.each16MB", max=2)
length(a[[1]])
head(a[[1]][[2]])
log2(length(a[[1]][[2]]))
print(object.size(a[[1]][[2]]), units="Mb")


## map-reduce to see number of keys/values in each map.keys/map.values in dataset1
## the number of map.keys/map.values is the max # of key/value pairs that one node
## allowed to handel 
map <- expression({
        rhcollect(unlist(map.keys), length(map.values))
})

mr <- rhwatch(
        map = map,
	input = rhfmt(paste(inputdir, "size1GB.each16MB", sep=""), type="sequence"),
	output = rhfmt(paste(outputdir, "size1GB.each16MB.npairs", sep=""), type="sequence"),
	mapred = list(mapred.reduce.tasks = 1),
	jobname = "npairs",
	readback = FALSE
)
## the size buff is 128 MB for one map.keys/map.values
a = rhread("/ln/tongx/userhipe/output/size1GB.each16MB.npairs")
sapply(a, '[[', 2)


## creating fack dataset1 which has 2^15 subsets of size 32KB each
map <- expression({
	lapply(seq_along(map.keys), function(r){
		k <- 1
		set.seed(r)
		v <- runif(2^12)
	rhcollect(k, v)
	})
})

mr <- rhwatch(
	map = map,
        input = c(2^15,10), ##64 subsets to make sure the total size is 1Gb
        output = rhfmt("/ln/tongx/userhipe/size1GB.each32KB", type="sequence"),
	mapred = list(mapred.reduce.tasks=1),
        jobname = "size.buff",
        readback = FALSE
)

a = rhread("/ln/tongx/userhipe/size1GB.each32KB", max=2)
length(a[[1]])
head(a[[1]][[2]])
log2(length(a[[1]][[2]]))
print(object.size(a[[1]][[2]]), units="Kb")


map <- expression({
        rhcollect(unlist(map.keys), length(map.values))
})

mr <- rhwatch(
        map = map,
        input = rhfmt(paste(inputdir, "size1GB.each32KB", sep=""), type="sequence"),
        output = rhfmt(paste(outputdir, "size1GB.each32KB.npairs", sep=""), type="sequence"),
        mapred = list(mapred.reduce.tasks = 1),
        jobname = "npairs",
        readback = FALSE
)

## the size buff is 128 MB for one map.keys/map.values
a = rhread("/ln/tongx/userhipe/output/size1GB.each32KB.npairs")
sapply(a, '[[', 2)

