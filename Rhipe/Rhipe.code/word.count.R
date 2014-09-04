rhput("~/Rhipe/word.count.txt", "/ln/tongx/word.count.txt")
rhls("/ln/tongx/")


## define map
map = expression({
  for (r in map.values) {
        line = strsplit(r, split=" +")[[1]]
        for (word in line) {
                rhcollect(word, 1)
        }
  }
})

## define reduce
reduce = expression(
  pre = {
        count = 0
  },
  reduce = {
        count = count + sum(unlist(reduce.values))
  },
  post = {
        rhcollect(reduce.key, count)
  }
)

## package user defined map and reduce into a map-reduce object
mr = rhwatch(
        map = map,
        reduce = reduce,
        input = rhfmt("/ln/tongx/word.count.txt",type="text"),
        output = "/ln/tongx/word.count.output",
        #combiner = TRUE,
	mapred = list( mapred.map.tasks=3, mapred.reduce.tasks=5 ),
        readback = FALSE	
)


## read the results into local R console
result = rhread("/ln/tongx/word.count.output")

