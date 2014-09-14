#rhipe_reduce_buff_size and rhipe_map_buff_size 
#reduce buff size default is 6,000, map buff size default is 3,000.
#map_buff_size works for text and simulate input, does not work for
#sequence input.
map <- expression({
	rhcollect(map.keys, map.values)
})
mr <- rhwatch(
	map = map,
	input = c(10000, 3),
	output = rhfmt("/wsc/tongx/tmp/map.buff", type="sequence"),
	readback = FALSE,
	mapred = list(mapred.reduce.tasks = 2, rhipe_map_buff_size = 1)
)
##The result is a list with 10,000 elements. There is only one key and one value 
##map.keys and map.values respectively.
rst <- rhread("/wsc/tongx/tmp/map.buff")


map <- expression({
    rhcollect(map.keys, map.values)
})
mr <- rhwatch(
    map = map,
    input = c(10000, 3),
    output = rhfmt("/wsc/tongx/tmp/map.buff", type="sequence"),
    readback = FALSE,
    mapred = list(mapred.reduce.tasks = 2, rhipe_map_buff_size = 4000)
)
##The result is a list with 3 elements. If the input is simulate, RHIPE will first
##try to assign 10000/3 key/value pairst to one task, which means map.keys and 
##map.values should be a list with 10000/3 elements. If 10000/3 is larger than 
##rhipe_map_buff_size, then 10000/3 key/value pairs will be split to two map.keys
##and map.values on one mapper.
rst <- rhread("/wsc/tongx/tmp/map.buff")




map <- expression({
	lapply(seq_along(map.keys), function(r){
		rhcollect(1, map.values[[r]])
	})
})
reduce <- expression(
    reduce = {
        rhcollect(reduce.key, reduce.values)
    }
)
mr <- rhwatch(
    map = map,
	reduce = reduce,
    input = c(10000, 3),
    output = rhfmt("/wsc/tongx/tmp/map.buff", type="sequence"),
    readback = FALSE,
    mapred = list(mapred.reduce.tasks = 1, rhipe_reduce_buff_size = 10000)
)
##The result is a list with 1 element. All key/value pairs have been read into
##reduce.key and reduce.values at once.
rst <- rhread("/wsc/tongx/tmp/map.buff")


##One thing should be kept in mind is that no matter how many values is corresponding
##one key(also no matter how large is the total size of key/value pairs for the one key),
##all those key/value pairs will be save to one part file.


##rhipe_map_buff_size does not work for sequence input
map <- expression({
	rhcollect(map.keys, map.values)
})
reduce <- expression(
    reduce = {
        rhcollect(reduce.key, reduce.values)
    }
)
mr <- rhwatch(
    map = map,
    reduce = reduce,
    input = rhfmt("/wsc/tongx/tmp/map.buff", type="sequence"),
    output = rhfmt("/wsc/tongx/tmp/map.result", type="sequence"),
    readback = FALSE,
    mapred = list(mapred.reduce.tasks = 1, rhipe_map_buff_size = 1)
)

 
