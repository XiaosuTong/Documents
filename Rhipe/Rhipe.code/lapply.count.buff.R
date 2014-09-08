#####################################################
## how hadoop distributes "lapply" input, 
## number of map tasks or number of input splits = 3
#####################################################
## map-reduce
map = expression({
        rhcollect(map.keys, map.values)
})
#We just created (simulation) a key-value pair on each map task we had. Since we defined mapred.map.tasks=3, we would get 3 key-value pairs in the output. rhcollect is creating a list.
#The results will be a list with 3 elements, i from 1 to 3. rst[[i]] will show the key-value pair created by i'th machine. In the rst[[i]], rst[[i]][[1]] is the key of the key-value pair, and is consist of all the keys from the key-value pairs created by i'th machine, rst[[i]][[2]] is the value of the key-value pair, and is consist of all the values from the key-value pairs created by i'th machine. Then rst[[i]][[1]][[j]] is the j'th key from the i'th machine, rst[[i]][[2]][[j]] is the j'th value from the i'th machine.

mr = rhwatch(
        map = map,
	input = c(10,3),
        output = rhfmt("/ln/tongx/userhipe/lapply.distribute", type="sequence"),
	readback = FALSE,
        #inout = c('lapply','sequence'),
        #N = 10,
        #mapred = list( mapred.map.tasks=3, mapred.reduce.tasks=0 )
)
#ex = rhex(mr, async=FALSE)

## read in output
rst1 = rhread("/ln/tongx/userhipe/lapply.distribute")
## look at what's in map.keys/map.values, note they are the same for "lapply" input types
#class(rst)
#length(rst)
#rst[[1]]
#class(rst[[1]])
#length(rst[[1]])
#rst[[1]][[1]]

## how many keys/values in each map.keys/map.values
#sapply(rst, function(r) length(r[[1]]))


#############################################
## scale up "lapply" input 
## buffer size will play a role here
## number of map tasks or number of input splits = 3
#############################################
## map buffer
map = expression({
        rhcollect(map.keys, map.values)
})
mr = rhwatch(
        map = map,
	input = c(9003,3),
        output = rhfmt("/ln/tongx/userhipe/lapply.buff10000", type="sequence"),
	readback = FALSE,
	mapred = list(mapred.reduce.tasks = 10, rhipe_map_buff_size = 10000),
        #inout = c('lapply','sequence'),
        #N = 10000,
        #mapred = list( mapred.map.tasks=3, mapred.reduce.tasks=0 )
)
#ex = rhex(mr, async=FALSE)

## read in output
rst2 = rhread("/ln/tongx/userhipe/lapply.buff10000")

## how many keys/values in each map.keys/map.values
## default buffer size is 3000
## each map task can only handel 3000 key/value pairs as maximum at one time
## The part that over factor of 3000 will also equally distributed

##reduce buffer
map = expression({
    lapply(seq_along(map.keys), function(r){
        rhcollect(1, map.values[[r]])
    })
})
reduce = expression(
	pre = {
	},
	reduce = {
	  rhcollect(reduce.key, reduce.values)
	},
	post = {
	}
)
mr = rhwatch(
        map = map,
	reduce = reduce,
        input = c(4000,3),
        output = rhfmt("/ln/tongx/userhipe/lapply.reducebuff3000", type="sequence"),
        readback = FALSE,
        mapred = list(mapred.reduce.tasks = 10, rhipe_map_buff_size = 4000),
)
##reduce default buffer size is 3000, each reduce task can handle 3000 key/value pairs at one time
##but since all key/value pairs are with same key, them all will be partitioned into one part-r- file

#############################################
## scale up "sequence" input 
## buffer size will play a role here
## number of map tasks or number of input splits = 3
################################################

## Create the data which has 4000 key/value pairs
## All keys are the same which is 1.
a <- lapply(rep(1,4000), function(x){list(1, runif(1))})
print(object.size(a), units="Mb")

rhwrite(a, "/ln/tongx/userhipe/partition")

map = expression({
        rhcollect(map.keys, map.values)
})

mr = rhwatch(
        map = map,
        input = rhfmt("/ln/tongx/userhipe/partition", type="sequence"),
        output = rhfmt("/ln/tongx/userhipe/sequence.buff", type="sequence"),
        readback = FALSE,
        mapred = list(mapred.map.task = 3, mapred.reduce.tasks = 10),
        #inout = c('lapply','sequence'),
        #N = 10000,
)
rst <- rhread("/ln/tongx/userhipe/sequence.buff")
## For sequence data, the buff size is same as lapply for map.keys/map.values pairs,
## which is 3000 key/value pairs for one map.keys/map.values.
## This means each mapper is setted to only handle 3000 key/value paris max at one time.
## Here only has one map.task, even though we set to be 3.


################################################
## how different values with same key distributed
## it can happen that different values with same key
## could not be partitioned into different parts.
##################################################
b <- lapply(rep(1:2,c(3500,500)), function(x){list(x, runif(1))})

rhwrite(b, "/ln/tongx/userhipe/partition.buff")
print(object.size(b), units="Mb")

map = expression({
    lapply(seq_along(map.keys), function(r){
        rhcollect(map.keys[[r]], map.values[[r]])
    })
})

mr = rhwatch(
        map = map,
        input = rhfmt("/ln/tongx/userhipe/partition.buff", type="sequence"),
        output = rhfmt("/ln/tongx/userhipe/sequence.buff.2", type="sequence"),
        readback = FALSE,
        mapred = list(mapred.reduce.tasks = 10),
)

rst2 <- rhread("/ln/tongx/userhipe/sequence.buff.2")

## all values related to one key will be partitioned into one part.
## even thought mapred.reduce.tasks = 10, there only are two part-r- files size
## is larger than 94, since we have two keys


###########################################
## It is true that after the map function, 
## all key/value pairs are ordered by keys.
###########################################
c <- lapply(sample(1:2, 6000, replac = TRUE), function(x){list(x, runif(1))})
do.call("c", lapply(c, "[[", 1))

rhwrite(c, "/ln/tongx/userhipe/partition.map")

map <- expression({
	lapply(seq_along(map.values), function(r){
		k <- map.keys[[r]]
		v <- map.values[[r]]
		rhcollect(k, v)
	})
})

mr = rhwatch(
        map = map,
        input = rhfmt("/ln/tongx/userhipe/partition.map", type="sequence"),
        output = rhfmt("/ln/tongx/userhipe/partition.output", type="sequence"),
        readback = FALSE,
        mapred = list(mapred.reduce.tasks = 4),
        #inout = c('lapply','sequence'),
        #N = 10000,
        #mapred = list( mapred.map.tasks=3, mapred.reduce.tasks=0 )
)

rst <- rhread("/ln/tongx/userhipe/partition.output")
do.call("c", lapply(rst, "[[",1))
## found that after the map function all keys have been ordered already!!
##But if mapred.reduce.tasks = 0, then no sorting!
