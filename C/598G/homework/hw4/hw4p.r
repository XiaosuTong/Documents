dyn.unload("tong.so");
system("R CMD SHLIB tong.c -o tong.so -lgsl -lgslcblas");
dyn.load("tong.so");

dim=1024;
A <- matrix(runif(dim*dim), nr=dim);
B <- matrix(rnnif(dim*dim), nr=dim);
strassen.matrix.mult <- function(A, B){
	result <- .C("Matrix", as.numeric(A), nrow(A), ncol(A), as.numeric(B), nrow(B), ncol(B), ans=numeric(nrow(A) * ncol(B)));
	return(matrix(result$ans, nrow=nrow(A)));
}


system.time(strassen.matrix.mult(A, B));
system.time(A %*% B);


 
