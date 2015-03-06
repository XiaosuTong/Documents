job <- list()
job$map <- expression({
  lapply(seq_along(map.values), function (r) {
    key2 <- as.integer(sample(1:100,1))
    key1 <- as.integer(sample(1:2, 1))
    rhcollect(c(as.integer(192),as.integer(168), key1, key2), rnorm(2^18))
  })
})
#job$reduce <- expression(
#  reduce = {
#    rhcollect(reduce.key, unlist(reduce.values))
#  }
#)
job$input <- c(128, 10)
job$output <- rhfmt("/ln/tongx/userhipe/partition2", type="sequence")
job$mapred <- list(
	mapred.reduce.tasks = 5
)
job$partitioner <- list(lims=c(1:3), type='integer')
job$mon.sec <- 5
job$readback <- FALSE
job.mr <- do.call("rhwatch", job)

job <- list()
job$map <- expression({
  lapply(seq_along(map.values), function (r) {
    key2 <- as.integer(sample(1:100,1))
    key1 <- as.integer(sample(1:2, 1))
    rhcollect(c(as.integer(192), key1, key2), rnorm(2^18))
  })
})
job$reduce <- expression(
  reduce = {
    rhcollect(reduce.key, unlist(reduce.values))
  }
)
job$input <- c(128, 10)
job$output <- rhfmt("/ln/tongx/userhipe/partition2", type="sequence")
job$mapred <- list(
  mapred.reduce.tasks = 5
)
job$partitioner <- list(lims=2, type='integer')
job$mon.sec <- 5
job$readback <- FALSE
job.mr <- do.call("rhwatch", job)

