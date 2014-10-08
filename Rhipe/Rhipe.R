##################################################################
#This is a very simple example of running Mapreduce job by using
#RHIPE. The goal is trying to calcuate coefficents from a logistic
#regression for a dataset with N*p dimention. N is the row number,
#p is the number of variables. Since the whole dataset is too large
#to fit into the memory, we will divide the dataset into R pieces.
#For each piece, we run a logistic regression, and then we average
#each coefficient over R subsets.
##################################################################
account <- "tongx"
N <- 2^20
R <- 2^10
p <- 2^3 - 1

##Generating data
map1 <- expression({
	lapply(seq_along(map.keys), function(r){
		set.seed(100)
		n <- N/R #number of rows for each subset
		value <- cbind(matrix(rnorm(n*p), ncol=p), sample(c(0,1), n, replace=TRUE))
		rhcollect(r, value)
		rm(value)
	})
})
job1 <- rhwatch(
	map = map1,
	input = c(R, 20),
	output = rhfmt(file.path("/app/hadoop", "glm", "data"), type="sequence"),
	jobname = "Generating data",
	readback = FALSE,
	parameters = list(N = N, R = R, p = p)
)

##glm.fit and average coefficients
map2 <- expression({
	lapply(seq_along(map.keys), function(r){
		v <- map.values[[r]]
		value <- glm.fit(v[,1:7],v[,8],family=binomial())$coef
		rhcollect(1, c(1, value))
	})
})
reduce2 <- expression(
  pre = {
        v <- rep(0, 8)
  },
  reduce = {
        v = v + apply(matrix(unlist(reduce.values), ncol=8, byrow=TRUE), 2, sum)
  },
  post = {
        rhcollect(reduce.key, v)
  }
)
job2 <- rhwatch(
    map = map2,
	reduce = reduce2,
    input = rhfmt(file.path("/ln", account, "glm", "data"), type="sequence"),
    output = rhfmt(file.path("/ln", account, "glm", "output"), type="sequence"),
    jobname = "GLM fit",
    readback = FALSE,
    noeval = TRUE
)
ex = rhex(job2, async=FALSE)


##read result from HDFS
rst <- rhread(file.path("/ln", account, "glm", "output"))
rst

