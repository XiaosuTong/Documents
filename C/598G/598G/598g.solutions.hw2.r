##############################################################################################################
#Problem 2
#Instructions:
# R allows one to use several different pseudo-random uniform random number generators.
# List the names of at least three such generators used by R (in a comment) and write down the command(s) that
# select one of these three.
##############################################################################################################

#TODO:  Implement problem 2 here.

set.seed(1)
#"Wichmann-Hill"
#"Marsaglia-Multicarry"
#"Mersenne-Twister":
RNGkind(kind = "Mersenne-Twister")







##############################################################################################################
# Problem 3
# Generate multivariate random observations from a Multivariate Normal.
# INPUTS:
#		--- n: the number of random iid observations to generate
#		--- mu: a numeric vector, the mean of the MVN
#		--- Sigma: a matrix of dimensions (m by m), the covariance of the MVN, where m is the length of mu.
# RETURN:
#		a matrix of dim n by m, that is one iid observation from MVN(mu, Sigma) per a row 
#############################################################################################################
rnorm.stat598g = function(n){
	u1 = runif(n)
	u2 = runif(n)
	return( sqrt(-2*log(u1))*cos(2*pi*u2))
}
rmvnorm = function(n, mu, Sigma){
	m = length(mu)
	A = chol(Sigma)
	ret = matrix(rnorm.stat598g(n*m),n,m)
	ret = t(A) %*% t(ret) + mu
	return(t(ret))
	
} 





##############################################################################################################
# Problem 4
# Instructions: This is a two part question.  One part is to implement a random number generating function, and the other is
# to construct plots according to the instructions.
##############################################################################################################

##############################################################################################################
# Problem 4a - rvonmises
# Generate random observations from a Von Mises distribution.
# INPUTs:
#		--- n: the number of random iid observations to generate
#		--- mu: parameter in Von Mises (see HW2 written part)
#		--- kappa: parameter in Von Mises (see HW2 written part)
# RETURN:
#       a vector of length n, where each element of the vector is an iid observation from a Von Mises (mu, kappa)
###############################################################################################################

rvonmises = function(n, mu, kappa){
	#TODO: Implement problem 4a  here
	ret = numeric(n)
	for(i in 1:n){
		while(TRUE){
			proposal = runif(1)*2*pi -pi
			probability.accept = exp(kappa*cos(proposal-mu) -kappa)
			u = runif(1)
			if(u < probability.accept){
				ret[i] = proposal
				break  #break the while
			}
			#else reject and try again
		}
	}
	return(ret)
}

dvonmises = function(x, mu, kappa){
	return(exp(kappa*cos(x-mu))/2/pi/besselI(kappa,0))
}

###############################################################################################################
# Problem 4b 
# Instructions: See the assignment for 4b.
###############################################################################################################

#TODO: Implement the additional instructions for problem 4 here.  (See assignment).
#HINT: To plot 2 x 2 figures, first use

par(mfrow=c(2,2))

#and then plot normally.  mfrow means rougly "fill my plot by row".  
#And c(2,2) means using 2 rows and 2 columns for subfigures.  c(3,2) would mean 3 rows and 2 columns.
#google it or otherwise track down information about mfrow for more information.

#Haque Syed's work contributed to 4b solution.

x1 <- rvonmises(100,0,0)
x2 <- rvonmises(100,0,1)
x3 <- rvonmises(100,0,2)
x4 <- rvonmises(100,0,5)
par(mfrow=c(2,2))
xlim = c(-1,1)
ylim = c(-1,1)
plot(cos(x1),sin(x1),xlim=xlim,ylim=ylim)
plot(cos(x2),sin(x2),xlim=xlim,ylim=ylim)
plot(cos(x3),sin(x3),xlim=xlim,ylim=ylim)
plot(cos(x4),sin(x4),xlim=xlim, ylim=ylim)



###############################################################################################################
# Problem 5 has 3 parts.
###############################################################################################################

###############################################################################################################
# Problem 5a
# Using accept-reject with Exp(1) as the probosal density implement a random number generator for Gamma(alpha, 1)
# INPUTS: 
#		--- n: 	the number of random iid observations to generate
#       --- alpha: shape parameter 
# RETURN:
# 		a vector of length n, where each element of the vector is an iid observation from a Gamma(alpha,1)
###############################################################################################################

rgamma.a = function(n, alpha,print.acceptance.rate = FALSE){
	if(alpha < 1){
		cat("rgamma.a only valid for alpha > 1\n")
		return(NULL);
	}
	attempts = 0
	exp.param = 1/alpha
	m = alpha^(alpha-1)*exp((exp.param - 1)*alpha)
	ret = numeric(n)
	for(i in 1:n){
		while(TRUE){
			attempts = attempts +1
			proposal = rexp(1,exp.param)
			probability.accept = proposal^(alpha-1)*exp((exp.param-1)*proposal)/m
			u = runif(1)
			if(u < probability.accept){
				ret[i] = proposal
				break
			}#otherwise reject and try again
		}
	}
	if(print.acceptance.rate) cat("Acceptance Rate = ", n/attempts, "\n")
	return(ret)
	
	
}    

###############################################################################################################
# Problem 5b
# Using algorithm 1 in the HW2 assignment implement a random number generator for Gamma(alpha,1)
# INPUTS: 
#		--- n: 	the number of random iid observations to generate
#       --- alpha: shape parameter 
# RETURN:
# 		a vector of length n, where each element of the vector is an iid observation from a Gamma(alpha,1)
###############################################################################################################

rgamma.b = function(n, alpha,print.acceptance.rate = FALSE){
	if(alpha >= 1){
		cat("Error: rgamma.b only valid for alpha < 1\n")
		return(NULL)
	}
	ret = numeric(n)
	e = exp(1)
	r = e/(e+alpha)
	attempts = 0
	for(i in 1:n){
		while(TRUE){
			attempts = attempts + 1
			u1 = runif(1)
			u2 = runif(1)
			
			if(u1 > r){
				x = -log((1-u1)/r/alpha) 
				y = x^(alpha-1)
			}else{
				x = (u1/r)^(1/alpha)
				y = exp(-x)
			}
			if(u2 < y){
				ret[i] = x
				break
			}#else reject
		}
	}
	if(print.acceptance.rate) cat("Acceptance Rate = ", n/attempts, "\n")
	return(ret)
}


#####################################################################################
# Problem 5c:
# Instructions: Empirically, estimate the acceptance ratio for both algorithm for the case of alpha = .5 and alpha = 2
# based on 10000 attempted draws. 
# PLEASE ADD USEFUL COMMENTS
######################################################################################

#TODO: Implement 5c here.

x = rgamma.a(10000,2,TRUE)
x = rgamma.b(10000,.5,TRUE)












###################################################################################################
#  Anything you want below this line.  If you have extensive test code you want to keep with this file
#  please put it below this comment.  Thank you!
###################################################################################################
