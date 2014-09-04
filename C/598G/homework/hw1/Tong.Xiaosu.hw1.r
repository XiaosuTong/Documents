####################################################################
# BEGIN ASSIGNMENT
# Xiaosu Tong
####################################################################


######################################################
# Problem 2
# Implement an insertion sort in the following function.
# Input ---
# 	A: a numeric vector to be sorted
# Return: a numeric vector corresponding to sorted A.
#####################################################

insertion.sort = function(A){
	n=length(A)
	for(i in 2:n){
		value=A[i]
		j=i-1
		while(j>0){
 			if(A[j]>value){
			A[j+1]=A[j]
			A[j]=value
			}
		j=j-1
		}
	}
	return(A)
}


######################################################
# Problem 3
# Implement a bubble sort in the following function.
# Input ---
# 	A: a numeric vector to be sorted
# Return: a numeric vector corresponding to sorted A
######################################################

bubble.sort = function(A){
	n=length(A)
	for(i in 1:(n-1)){
	    for(j in 1:(n-i)){
		if(A[j]>A[j+1]){
			value=A[j+1]
			A[j+1]=A[j]
			A[j]=value
		}
	     }
	}
	return(A)
}


#####################################################################
# Problem 4
# Implement a merge sort in the following function.
# Input ---
#	A: a numeric vector to be sorted
# Return: a numeric vector corresponding to sorted A
#####################################################################

merge.sort = function(A){
	n=length(A)
	if(n>1){
		mid=floor(n*0.5)
		A1=merge.sort(A[1:mid])
		A2=merge.sort(A[(mid+1):n])
	}
	return(merge.array(A1, A2))
}

merge.array = function(A,B){
	i=1
	j=1
	n=length(A)
	m=length(B)
	C=numeric(m+n)
	while((i<=n) && (j<=m)){
		if(A[i]<B[j]){
			C[i+j-1]=A[i]
			i=i+1
		}
		else{
			C[i+j-1]=B[j]
			j=j+1
		}
	}
	if(j>m){
		C[(i+j-1):(n+m)]=A[i:n]
	}
	else{
		C[(i+j-1):(n+m)]=B[j:m]
	}
	return(C)
}

###############################################################################
# Problem 5
# Implement a binary.search in the following function.
# Inputs ---
# 	A: a sorted numeric vector to be searched 
#	val: a value to be searched for in the vector
# Return: an integer.  
#		The return integer should be -1 if "val" is not found in A.
#		Otherwise the return integer should be the index where val is found in A.
#		If return value > 0 it should be true that A[return value] == val.
#		
# Note: If there are multiple indexes where val is found in A return any index such that A[index] == val.
###############################################################################


binary.search = function(A, val){
	#TODO: write code to implement and return an integer according to the instructions above
}




#############################################################################
# Problem 6
# Implement scripts and comments for problem 6 here.
# Instructions:
# Propose input array A to selection.sort() and bubble.sort() which would result in a
# much faster execution for bubble.sort(A) than selection.sort(A). Demonstrate your findings
# using system.time function in R.
# PLEASE ADD USEFUL COMMENTS FOR ME TO INTERPRET YOUR WORK.
#############################################################################


#TODO: Implement problem 6.






#############################################################################
# Problem 7
# Implement scripts and comments for problem 7 here.
# Instructions:
# Evaluate the performance of merge.sort(A) versus that of selection.sort(A) by
# varying the length of the input vector A. Use plot function in R.
# PLEASE ADD USEFUL COMMENTS FOR ME TO INTERPRET YOUR WORK.
#############################################################################

#TODO: Implement problem 7.





#############################################################################
# END OF ASSIGNMENT
# You may put any code you want below this line.
# You may have debugging code you want with this file etc.
#############################################################################

#TODO: Whatever you want.  I recommend writing testing code for your sort routines.






















