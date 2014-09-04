##how lapply handel the map.keys and map.values on each node.

map <- expression({
	lapply(map.keys, function(r){
		index <- which(do.call("c", lapply(map.keys, "[[",1))==r)
		v <- map.values[[index]]
		rhcollect(r, v)
	})
})

mr <- rhwatch(
        map = map,
        input = c(10,3), 
        output = rhfmt("/wsc/tongx/userhipe/map.key", type="sequence"),
        mapred = list(mapred.reduce.tasks=1),
        jobname = "map.key",
        readback = FALSE
)

###################################

map <- expression({
	for(i in 1:length(map.keys)){
		rhcollect(i, map.values[[i]]) 
	}
})

mr <- rhwatch(
        map = map,
        input = c(10,3),
        output = rhfmt("/ln/tongx/userhipe/map.key", type="sequence"),
        mapred = list(mapred.reduce.tasks=1),
        jobname = "map.key",
        readback = FALSE
)

##################################

map <- expression({
	for(i in map.keys){
		rhcollect(i, map.keys)	
	}
})

mr <- rhwatch(
        map = map,
        input = c(20,3),
        output = rhfmt("/ln/tongx/userhipe/map.key", type="sequence"),
        mapred = list(mapred.reduce.tasks=1),
        jobname = "map.key",
        readback = FALSE
)

