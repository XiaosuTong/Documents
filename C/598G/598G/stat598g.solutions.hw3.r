
dyn.unload("hw3.so")
system("R CMD SHLIB *.hw3.c -o hw3.so -lm -Wall -O3")
dyn.load("hw3.so",local=FALSE)
var(.C("rcall_gamrand",v = double(1000000), dim=as.integer(1000000), alpha=as.double(5))$v)
.C("exercise2")
################################################################################
# Exercise 3b
# Instructions:
# By editting matrix.mult.C in lastname.firstname.R, write a $R$ wrapper function  which will call your C function and return the appropriate result.
# function matrix.mult.C
# Input: 
#      --- m1  a square matrix to be matrix multiplied with m2
#	   --- m2  a square matrix to be matrix multiplied with m1
# Return:
#	by calling squareMatrixMultiply in lastname.firstname.c using ".C" return a matrix equivalent to m1 %*% m2
#   The return must be put back into matrix form in R before returning.
# Note: you may not do the matrix multiplication in R.  You must call .C and do it in C.
#################################################################################
matrix.mult.C = function(m1, m2){
	ret = matrix(0, nrow(m1), ncol(m2))
	result = .C("squareMatrixMultiply",m1=as.double(m1), m2=as.double(m2), dim = as.integer(nrow(m1)), ret = as.double(ret))
	ret = matrix(result$ret,nrow(m1), ncol(m2))
	return(ret)

}





################################################################################
# Exercise 4c
# Instructions:
# By editting matrix.mult.Strassen in lastname.firstname.R, write an $R$ wrapper function  which will call squareMatrixMultiplyStrassen in C and return the appropriate result.
# function matrix.mult.Strassen
# Input: 
#      --- m1  a square matrix to be matrix multiplied with m2
#	   --- m2  a square matrix to be matrix multiplied with m1
# Return:
#	by calling squareMatrixMultiplyStrassen in lastname.firstname.c using ".C" return a matrix equivalent to m1 %*% m2
#   The return must be put back into matrix form in R before returning.
# Note: you may not do the matrix multiplication in R.  You must call .C and do it in C.
##################################################################################
matrix.mult.Strassen = function(m1, m2){
	ret = matrix(0, nrow(m1), ncol(m2))
	result = .C("squareMatrixMultiplyStrassen",m1=as.double(m1), m2=as.double(m2), dim = as.integer(nrow(m1)), ret = as.double(ret))
	ret = matrix(result$ret,nrow(m1), ncol(m2))
	return(ret)

}






###############################################################################
# Exercise 5
# Instructions:
# Using system.time() compare the performance of matrix.mult.C, matrix.mult.Strassen, and %*%
# by repeatedly generating two random 256 x 256 matrices and computing their products using all three methods. 
# What does it tell you about how $R$ may implement matrix multiplication?  
# You may need to generate even larger matrices to get a clear picture.
#################################################################################


#Anything like this is the idea.
#First checking for correctness.
dim = 2^3
x = matrix(runif(dim*dim),dim,dim)
y = matrix(runif(dim*dim),dim,dim)
matrix.mult.C(x,y) - x %*% y
matrix.mult.Strassen(x,y) - x %*% y
#Now checking for time.
dim = 2^11
x = matrix(runif(dim*dim),dim,dim)
y = matrix(runif(dim*dim),dim,dim)
system.time(x %*% y)
#system.time(matrix.mult.C(x,y))
system.time(matrix.mult.Strassen(x,y))

#we win at 2^11!




