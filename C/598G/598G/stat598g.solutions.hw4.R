###############################################
#
# Helper function
#
##############################################
isFeasible = function(alpha,beta){
	if(alpha <= 0 | beta <= 0){
	 	cat("Warning alpha = ", alpha," beta = ", beta, "not feasiable\n")
	 	return(FALSE)
	}
	else{
		return(TRUE)
	}
}
################################################################
# Exercise 1a
# beta gradient
# Inputs:
#	--- x : a numeric vector of data
#	--- alpha 
#	--- beta
# Return:
#   --- a numeric vector of length 2 corresponding to the partial derivatives of the log likelihood of a Beta distribution w.r.t alpha and beta evaluated at alpha and beta from the inputs.
################################################################

beta.gradient = function(x, alpha, beta){
	ret = numeric(2)  
	n = length(x)
	ret[1] = sum(log(x)) +n*digamma(alpha+beta) - n*digamma(alpha)
	ret[2] = sum(log(1-x)) +n*digamma(alpha+beta) - n*digamma(beta)
	return(ret)
}


################################################################
# Exercise 1b
# beta.hessian
# Inputs:
#	--- x : a numeric vector of data
#	--- alpha 
#	--- beta
# Return:
#   --- a 2 by 2 matrix corresponding to the hessian evaluated at alpha and beta from the inputs.
################################################################

beta.hessian = function(x, alpha, beta){
	n = length(x)
	ret = matrix(n*trigamma(alpha+beta),2,2)
	ret[1,1] = ret[1,1] - n*trigamma(alpha)
	ret[2,2] = ret[2,2] - n*trigamma(beta)
	return(ret)
}


################################################################
# Exercise 1c
# beta.mle.nr calculate mle of a Beta with Newton-Raphson iterations
# Inputs:
#     --- x : a numeric vector of data
#	  --- initial.alpha: starting guess for alpha.
#	  --- initial.beta: starting guess for beta.
# You will return a list.  Two slots in that list are required by the final question.
# You may add things optionally to that list that you feel are useful.
# Optionally return the estimatea and log likelihoods at each iteration. These are often useful for diagnostics.
# Returns in a list:
#     Required:
#     --- niterations: number of iterations required for the algorithm to finish.
#     --- MLE: a numeric vector with two entries corresponding to mle estimates for alpha and beta assuming the data were iid from a Beta distribution.
#     Optional:
#     --- thetas:  a matrix where each row is an estimate of alpha and beta at each iteration
#     --- loglikelihoods: a numeric vector where each entry is the log likelhood at that iteration.
#     --- converged: a boolean value indicating if the algorithm was judged to have converged before max iterations was reached.
################################################################

beta.mle.nr = function(x, initial.alpha = 1/2, initial.beta = 1/2, max.iterations = 1000, step.function = NULL){  #step.function is not used in this function.  Just added it to match the prototype of the others.
	ret = list()
	#required returns
	ret$niterations  = 0   												#number of iterations required during the algorithm
	ret$MLE = numeric(2)												#final iteration MLE for alpha and beta
	#optional returns
	ret$max.iterations = max.iterations
	ret$thetas = matrix(0,max.iterations,2)							    #alpha and beta at each iteration
	ret$loglikelihoods = numeric(max.iterations)                        #log likelihoods at each iteration
	ret$converged = FALSE												#set to TRUE if the algorithm was judged to have converged before max.iterations.
	
	theta = c(initial.alpha,initial.beta)
	for(i in 1:max.iterations){
		g = beta.gradient(x,theta[1],theta[2])
		H = beta.hessian(x,theta[1],theta[2])	
		
		#book keeping	
		ret$thetas[i,] = theta
		ret$loglikelihoods = sum(dbeta(x,theta[1],theta[2],log=TRUE))
		
		#stop?
		if(sqrt(sum(g^2)) < .0001){
			ret$converged = TRUE
			break
		}
		
		#update
		theta = theta - solve(H)%*%g
		
		#be wary of leaving bounds
		if(!isFeasible(theta[1],theta[2]))
			break
		
	}
	ret$MLE = as.vector(theta)
	ret$niterations = i
	if(isFeasible(theta[1],theta[2]))
		ret$log.likelihood = sum(dbeta(x,theta[1],theta[2],log=TRUE))
	else
		ret$log.likelihood = NA
	return(ret)
}



################################################################
# Exercise 2a
# dk.direction calculates the derivative of the log likelihood for a Beta wrt to a descent multiple along a direction and evaluates it.
# Calculates the derivative of l(theta + k*direction) with respect to k.
# Inputs:
#     --- x: a numeric vector of data
#     --- theta: a numeric vector of length 2 with current alpha and beta.  e.g theta = c(alpha, beta)
#	  --- k: the multiple applied to the direction.
#	  --- direction: a numeric vector of length 2 representing the direction vector. 
# Return:
#	A value appropriate to the description above and the problem description.
################################################################
dk.direction = function(x, theta, k, direction){
	tkd = theta + k*direction
	return(as.numeric(beta.gradient(x,tkd[1],tkd[2]) %*% direction))
}


################################################################
# Exercise 2b
# dk2.direction calculated the secon derivative of the log likelihood for a Beta wrt to a descent multiple along a direction and evaluates it.
# Calculates the second derivative of l(theta + k*direction) with respect to k.
# Inputs:
#     --- x: a numeric vector of data
#     --- theta: a numeric vector of length 2 with current alpha and beta.  e.g theta = c(alpha, beta)
#	  --- k: the multiple applied to the direction.
#	  --- direction: a numeric vector of length 2 representing the direction vector. 
# Return:
#	A value appropriate to the description above and the problem description.
################################################################
dk2.direction = function(x, theta, k, direction){
	tkd = theta + k*direction
	return(as.numeric(t(direction) %*% beta.hessian(x,tkd[1],tkd[2]) %*% direction))
}


################################################################
# Exercise 2c
# line.search.direction 
# Using Newton-Raphson iterations: 
# Finds the optimum k such that l(theta + k*direction) is minimized w.r.t k.
# l is the log-likelood for a Beta distribution.
# Inputs:
#     --- x: a numeric vector of data
#     --- theta: a numeric vector of length 2 with current alpha and beta.  e.g theta = c(alpha, beta)
#	  --- direction: a numeric vector of length 2 representing the direction vector. 
# Return:
#	k such that l(theta + k* direction) is minimized with w.r.t k.
################################################################
line.search.direction = function(x, theta, direction){
	#cat("\t  In line.search.direction\n")
	max.iterations = 100
	
	for(k in c(0,-.1,.1)){ #try some different starts but this won't loop if the first one was good
		lastk = Inf
		failed = FALSE
		khistory = numeric(max.iterations)
		for(i in 1:max.iterations){
			khistory[i] = k
			tkd = theta + k*direction
			if(!isFeasible(tkd[1],tkd[2])){
				failed=TRUE
				break
			}
			dk = dk.direction(x,theta,k,direction)
			dk2 = dk2.direction(x,theta,k,direction)
			#cat("dk1: ", dk, " dk2: ", dk2,"\n")
			if(abs(k - lastk) < .00001){
				break	
			}
			lastk = k
			k = k - dk/dk2  #yes this is just g %*% d/ t(d) %*% H  %*% d
		}
		if(i != max.iterations & !failed){
			#we converge so we will break and take this k.  Otherwise go to the top and try new start
			break
		}
	}
	if(i == max.iterations){
		cat("Warning: failed to converge in line.search.direction.\n")
		cat("history of k: ", khistory,"\n")
		
	}
	if(failed){
		cat("Warning: line.search.direction quit due to proposing infeasible theta for next update.\n")
		cat("history of k: ", khistory,"\n")
		#after debugging both this and bisection direction.  I decided rather then just failing here.  Better was to call bisection.direction
		return(bisection.direction(x,theta,direction))
	}
	return(k)
	
}


################################################################
# Exercise 2d
# bisection.direction
# Using bisection method:
# Finds the optimum k such that l(theta + k*direction) is minimized w.r.t k.
# l is the log-likelood for a Beta distribution.
# Inputs:
#     --- x: a numeric vector of data
#     --- theta: a numeric vector of length 2 with current alpha and beta.  e.g theta = c(alpha, beta)
#	  --- direction: a numeric vector of length 2 representing the direction vector. 
# Return:
#	k such that l(theta + k* direction) is minimized with w.r.t k.
################################################################
bisection.direction = function(x, theta, direction){
	#first because size of the direction is such a big issue with numeric choices below.  I am just going to scale it if it small or large and recall this routine
	scale = sqrt(sum(direction^2))
	if(scale > 1.1 | scale < .9){
		ret = bisection.direction(x,theta,direction/scale)/scale
		#just some debugging stuff below
		tkd = theta+ret*direction
		if(!isFeasible(tkd[1],tkd[2])){
			dd <<- as.list(environment())
		}
	    #okay return it
		return(ret)
	}
	#next in order to tackle the boundary problem it is helpful to get a common orientation on negative aliased directions
	asign = sign(direction[1])
	if(asign == -1){
		#pointed toward y axis so I am flipping and returning the negative step
		return(-bisection.direction(x,theta,-direction))
	}
	bsign = sign(direction[2])	
	angle.direction = atan(direction[2]/direction[1])
	angle.theta = atan(theta[2]/theta[1])
	if(asign == 0 & bsign < 0){
		#vertical.  So I am orientating up and returning the negative step
		return(-bisection.direction(x,theta,-direction))
	}
	
	if (asign == 0 & bsign == 0){
		stop("Error in bisection.direction: magnitude of direction vector is zero")
	}
	################################################################################################
	# Okay now we have finished orientations and we are satisfied we are doing a bisection search on this direction
	#so we have postive alpha direction or zero alpha direction and positive beta direction here
	#I stress I am only doing this because I want to tackle the boundary condition without a ton of if statements
	#we always need a kmin so let us start there.
	################################################################################################
	
	if(angle.direction < angle.theta) 						 #are we intersecting xaxis or yaxis?
		kmin = -theta[1]/direction[1]*.999           #kmin comes from intersecting y-axis
	else
		kmin = -theta[2]/direction[2]*.999            #kmin comes from intersecting x-axis
	

	#we sometimes need a kmax to respect the boundary but not always.
	if(angle.direction < 0){
		#we are pointed downward and away from the y axis so we will intersect xaxis with kmax
		kmax = -theta[2]/direction[2]*.999
	}
	else{
		#much more common way to initialize!
		#here the downward direction intersects an axis but the upward direction is free to be as large as we want.
		kmax = .001/sqrt(sum(direction^2))
		while(dk.direction(x,theta,kmax,direction) > 0){
			#cat("kmax = ",kmax)
			kmax = 2*kmax
		}
	
	}
	# debugging stuff
	# k = seq(kmin,kmax,,100)
	# y = sapply(k,function(k0) dk.direction(x,theta,k0,direction))
	# y
	#
	#  FINALLY... OMG....
	#  BEGIN Binary Search...
	#
	converged = FALSE
	for(i in 1:100){
		kmid = (kmin+kmax)/2
		d = dk.direction(x,theta,kmid,direction)
		#cat("kmin ", kmin, " kmax ", kmax, " kmid ", kmid, " d ", d, "\n")
		if(abs(d) < .000001){
			converged = TRUE
			break
		}
		if(d > 0)
			kmin = kmid
		else
			kmax = kmid
	}
	if(!converged){
		cat("Warning: failed to converge in bisection.direction.  Dumping environment to dump.env\n")
		cat("Last derivative: ", d, "\n")
		if(is.null(dump.env))
			dump.env <<- list()
		dump.env[[length(dump.env)+1]] <<- as.list(environment())
		
	}
 	return(kmid)
}


################################################################
# Exercise 2e
# Calculates the MLE for a beta distribution using a steepest descent.
# Iteratively doing a line search along the gradient of the log likelihood.
# Inputs:
#     --- x : a numeric vector of data
#	  --- initial.alpha: starting guess for alpha.
#	  --- initial.beta: starting guess for beta.
# You will return a list.  Two slots in that list are required by the final question.
# You may add things optionally to that list that you feel are useful.
# Optionally return the history of of the estimates during the iterations and the history of the log-likelihoods. These are often useful for diagnostics.
# Returns in a list:
#     Required:
#     --- niterations: number of iterations required for the algorithm to finish.
#     --- MLE: a numeric vector with two entries corresponding to mle estimates for alpha and beta assuming the data were iid from a Beta distribution.
#     Optional:
#     --- thetas:  a matrix where each row is an estimate of alpha and beta at each iteration
#     --- loglikelihoods: a numeric vector where each entry is the log likelihood at that iteration.
#     --- converged: a boolean value indicating if the algorithm was judged to have converged before max iterations was reached.
################################################################

beta.mle.sd = function(x, initial.alpha = 1/2, initial.beta = 1/2, max.iterations = 1000, step.function = line.search.direction){
	ret = list()
	#required returns
	ret$niterations  = 0   												#number of iterations required during the algorithm
	ret$MLE = numeric(2)												#final iteration MLE for alpha and beta
	#optional returns
	ret$max.iterations = max.iterations
	ret$thetas = matrix(0,max.iterations,2)							    #alpha and beta at each iteration
	ret$loglikelihoods = numeric(max.iterations) 
	ret$gradients = matrix(0,max.iterations,2)                       #log likelihood for that iteration
	ret$k = numeric(max.iterations)
	ret$converged = FALSE												#set to TRUE if the algorithm was judged to have converged before max.iterations.
	
	theta = c(initial.alpha,initial.beta)
	k = Inf
	ll = Inf
	for(i in 1:max.iterations){
		g = beta.gradient(x,theta[1],theta[2])
		
		#book keeping
		ret$gradients[i,] = g
		ret$thetas[i,] = theta
		lastll = ll
		ret$loglikelihoods = ll = sum(dbeta(x,theta[1],theta[2],log=TRUE))
		
		#decide to stop?
		if(sqrt(sum(g^2)) < .0001){# | abs((lastll-ll)/ll) < .0001) {#| abs(k) < 10^(-30)){
			ret$converged = TRUE
			break
		}
		#do updates
		k = step.function(x,theta,g)
		ret$k[i] = k
		theta = theta +  k*g
		
		#be wary of leaving bounds
		if(!isFeasible(theta[1],theta[2]))
			break
	}
	ret$MLE = as.vector(theta)
	ret$niterations = i
	if(isFeasible(theta[1],theta[2]))
		ret$log.likelihood = sum(dbeta(x,theta[1],theta[2],log=TRUE))
	else
		ret$log.likelihood = NA
	return(ret)
	
}


################################################################
# Exercise 2f
# Calculates the MLE for a beta distribution using a conjugate gradient method.
# Inputs:
#     --- x : a numeric vector of data
#	  --- initial.alpha: starting guess for alpha.
#	  --- initial.beta: starting guess for beta.
# You will return a list.  Two slots in that list are required by the final question.
# You may add things optionally to that list that you feel are useful.
# Optionally return the historyof the estimates during the iterations and the history of the log-likelihoods. These are often useful for diagnostics.
# Returns in a list:
#     Required:
#     --- niterations: number of iterations required for the algorithm to finish.
#     --- MLE: a numeric vector with two entries corresponding to mle estimates for alpha and beta assuming the data were iid from a Beta distribution.
#     Optional:
#     --- thetas:  a matrix where each row is an estimate of alpha and beta at each iteration
#     --- loglikelihoods: a numeric vector where each entry is the log likelihood at that iteration.
#     --- converged: a boolean value indicating if the algorithm was judged to have converged before max iterations was reached.
################################################################


beta.mle.cg = function(x, initial.alpha = 1/2, initial.beta = 1/2, max.iterations = 1000, step.function = line.search.direction){
	ret = list()
	#required returns
	ret$niterations  = 0   												#number of iterations required during the algorithm
	ret$MLE = numeric(2)												#final iteration MLE for alpha and beta
	#optional returns
	ret$max.iterations = max.iterations
	ret$thetas = matrix(0,max.iterations,2)							    #alpha and beta at each iteration
	ret$gradients = matrix(0,max.iterations,2)
	ret$directions = matrix(0,max.iterations,2)
	ret$k = numeric(max.iterations)
	ret$loglikelihoods = numeric(max.iterations)                        #log likelihood at each iteration
	ret$converged = FALSE												#set to TRUE if the algorithm was judged to have converged before max.iterations.
					

	# Following: http://learning.stat.purdue.edu/wiki/_media/courses/sp2011/598a/optimization.pdf
	# Algorithm 3.3 with Table 3.2.
	# Changing alpha in those notes to "k".
	# Changing beta in those notes to "scale".
	# Changing w to "theta"			
	# Changing p to "d"				
	theta = c(initial.alpha,initial.beta) 
	d = -beta.gradient(x,theta[1],theta[2])
	k = Inf
	ll = Inf
	for(i in 1:max.iterations){
		g0 =  beta.gradient(x,theta[1],theta[2])
		#book keeping
		ret$gradients[i,] = g0
		ret$directions[i,] = d
		ret$thetas[i,] = theta 
		lastll = ll
		ret$loglikelihoods[i] = ll = sum(dbeta(x,theta[1],theta[2],log=TRUE))
		
		#decide to stop?
		if(sqrt(sum(g0^2)) < .0001){ 
			ret$converged = TRUE
			break
		}
		
		#do updates
		k = step.function(x,theta,d)
		ret$k[i] = k
		theta = theta + k*d
		
		#be wary of leaving bounds
		if(!isFeasible(theta[1],theta[2]))
			break
			
		#otherwise more updates.
		g1 = beta.gradient(x, theta[1], theta[2])
		scale = ((g1-g0) %*% g1)/ (g1 %*% g0)
		d = -g1 + scale*d
	}
	ret$MLE = as.vector(theta)
	ret$niterations = i
	if(isFeasible(theta[1],theta[2]))
		ret$log.likelihood = sum(dbeta(x,theta[1],theta[2],log=TRUE))
	else
		ret$log.likelihood = NA
	return(ret)

}



#################################################################
# Exercise 3
# Write your own code to do the work of exercise 3 here.
# This question is opened ended (in a graduate level course).
# Comment appropriately to help me understand your code and how it is used.
# Also, comment on what you saw when you ran your code. 
# You may assume that betadata.txt is in the current working directory for this R script.
# You have to load it and call your 3 mle routines with at least 50 random starts.
# 
#################################################################



#
# First let us visualize the objective function
#
png("beta.contours.png",800,800)
x = read.table("betadata.txt")
x = x[,1]
alphas = seq(.02,4,,100)
betas = seq(.02,6,,100)
grid = expand.grid(alphas,betas)
grid = as.matrix(grid)
obj = apply(grid,1, function(theta) -sum(dbeta(x,theta[1],theta[2],log=TRUE)))
obj = matrix(obj,100,100)
zlim = quantile(obj,c(0,.65)) 
contour(alphas,betas,obj, zlim=zlim,xlab="alpha", ylab="beta")
dev.off()
#TODO: exercise 3
x = read.table("betadata.txt")
x = x[,1]

set.seed(1)
################################################################################################
#we will setup a results data.frame then we will copy it
################################################################################################

results = list()
results$failed = logical(50)
results$converged= logical(50)
results$mle.alpha = numeric(50)
results$mle.beta = numeric(50)
results$niterations = numeric(50)
results$log.likelihood = numeric(50)
results = as.data.frame(results)
################################################################################################
#now a list of methods with one results data.frame each.
#This is a list of methods to try.
#We will fit it with results
################################################################################################

methods = list()
methods$nr = list()
methods$nr$results = results
methods$nr$FUN = beta.mle.nr
methods$sd = list()
methods$sd$results = results
methods$sd$FUN = beta.mle.sd
methods$cg = list()
methods$cg$results = results
methods$cg$FUN = beta.mle.cg
init.alpha = runif(50,.1,7)
init.beta = runif(50,.1,7)

################################################################################################
# attempt to fit using FUN
################################################################################################

doAttempt = function(x, init.alpha, init.beta, FUN, step.function = line.search.direction){
	res = NULL
	try({res = FUN(x,init.alpha, init.alpha, step.function=step.function)})
	#print(res)
	if(!is.null(res)){
		ret = data.frame(failed = FALSE, converged = res$converged, mle.alpha = res$MLE[1], mle.beta = res$MLE[2], niterations = res$niterations, log.likelihood = res$log.likelihood)
	}else{
		ret = data.frame(failed = TRUE, converged = NA, mle.alpha = NA, mle.beta = NA, niterations = NA, log.likelihood = NA)
	}
	return(ret)
}
################################################################################################
#Try each of the methods in the list
################################################################################################

doMethods = function(methods, step.function = line.search.direction){
	for(j in 1:length(methods)){
		m = methods[[j]]
	
		for(i in 1:50){
			cat(j," ",i,"\n")
			m$results[i,] = doAttempt(x, init.alpha[i], init.beta[i], m$FUN, step.function)
		
		}
		m$results$init.alpha = init.alpha
		m$results$init.beta = init.beta
		methods[[j]] = m
		methods[[j]]$FUN = NULL

	}
	return(methods)
}
################################################################################################
#take a look
options(width=120)
result = doMethods(methods)
result
resultbd = doMethods(methods, bisection.direction)
resultbd

################################################################################################
#how about plotting failed starts for NR
png("beta.contours.png",800,800)
x = read.table("betadata.txt")
x = x[,1]
alphas = seq(.02,7,,100)
betas = seq(.02,7,,100)
grid = expand.grid(alphas,betas)
grid = as.matrix(grid)
obj = apply(grid,1, function(theta) -sum(dbeta(x,theta[1],theta[2],log=TRUE)))
obj = matrix(obj,100,100)
zlim = quantile(obj,c(0,.30)) 
contour(alphas,betas,obj, zlim=zlim,xlab="alpha", ylab="beta", main="NR Failed Initializations")

mask = !result$nr$results$converged
x = result$nr$results$init.alpha[mask]
y = result$nr$results$init.beta[mask]
points(x,y,col="red")
x = result$nr$results$init.alpha[!mask]
y = result$nr$results$init.beta[!mask]
points(x,y,col="blue")
dev.off()


