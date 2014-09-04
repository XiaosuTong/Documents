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
    ret[1] = n*digamma(alpha + beta) - n*digamma(alpha) + sum(log(x))
    ret[1] = n*digamma(alpha + beta) - n*digamma(beta) +sum(log(1-x))
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
      ret = matrix(0,2,2)
#Your code goes here!		
	return(ret)
}

################################################################
# Exercise 1c
# beta.mle.nr calculate mle of a Beta with Newton-Raphson iterations
# Inputs:
#       --- x : a numeric vector of data
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
	
	      #Your code goes here!		
		
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
	#Your code goes here!
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
	#Your code goes here!

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
	#Your code goes here!
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
	#Your code goes here!
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

beta.mle.sd = function(x, initial.alpha = 1/2, initial.beta = 1/2, max.iterations = 1000){
	ret = list()
	#required returns
	ret$niterations  = 0   												#number of iterations required during the algorithm
	ret$MLE = numeric(2)												#final iteration MLE for alpha and beta
	#optional returns
	ret$max.iterations = max.iterations
	ret$thetas = matrix(0,max.iterations,2)							    #alpha and beta at each iteration
	ret$loglikelihoods = numeric(max.iterations)                        #log likelihood for that iteration
	ret$converged = FALSE												#set to TRUE if the algorithm was judged to have converged before max.iterations.
	
	# Your code goes here!
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

beta.mle.cg = function(x, initial.alpha = 1/2, initial.beta = 1/2, max.iterations = 1000){
	ret = list()
	#required returns
	ret$niterations  = 0   												#number of iterations required during the algorithm
	ret$MLE = numeric(2)												#final iteration MLE for alpha and beta
	#optional returns
	ret$max.iterations = max.iterations
	ret$thetas = matrix(0,max.iterations,2)							    #alpha and beta at each iteration
	ret$loglikelihoods = numeric(max.iterations)                        #log likelihood at each iteration
	ret$converged = FALSE												#set to TRUE if the algorithm was judged to have converged before max.iterations.
	
	# Your code goes here!

	return(ret)
}

#################################################################
# Exercise 4
# Write your own code to do the work of exercise 4 here.
# Since it is an open ended question, there wont be a skeleton for this question. 
# You may assume that betadata.txt is in the current working directory for this R script.
# You have to load it and call your 3 mle routines with at least 50 random starts.
# Please comment your code for ease while evaluating.
#################################################################



