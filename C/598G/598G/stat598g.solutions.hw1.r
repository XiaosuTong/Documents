####################################################################
# BEGIN ASSIGNMENT
# SOLUTIONS BY JEREMIAH ROUNDS
####################################################################


######################################################
# Problem 2
# Implement a selection sort in the following function.
# Input ---
# 	A: a numeric vector to be sorted
# Return: a numeric vector corresponding to sorted A.
#####################################################


selection.sort = function(A){
	nlength = length(A)
	#prefixing an i to indicate an index
	for(ifill in 1:nlength){
		#fill up from the bottom 
		imin = ifill	
		for(isearch in ifill:nlength){ 	#look for min
			if(A[isearch] < A[imin]){ 		#found something lower
				imin = isearch
			}
		}
		
		#swap
		tmp = A[imin]
		A[imin] = A[ifill]
		A[ifill] = tmp
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
	#TODO: write code to sort A via a bubble sort and return(sortedA)
	largest_top = length(A) - 1
	for(top in largest_top:1){
		for(j in 1:top){
			#bubble the largest to the top 
			if(A[j] > A[j+1]){
				#then swap
				tmp = A[j+1]
				A[j+1] = A[j]
				A[j] = tmp
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
	#TODO: write code to sort A via a merge sort and return(sortedA)
	
	#terminate recursion condition
	nlength = length(A)
	if(nlength == 1) return(A)
	
	#otherwise do work
	imiddle = floor(nlength/2)						#length at least 2 so imiddle >= 1
	sorted_lower_A = merge.sort(A[1:imiddle])
	imiddle = imiddle + 1  	#can this index past the end of the array? No because of floor	
	sorted_upper_A = merge.sort(A[imiddle:nlength])
	
	#now merge them
	return(merge.array(sorted_lower_A, sorted_upper_A))
	
	
	
}

###############################################################################
# merge.array is a helper function that merges sorted arrays
# input ----
#		-A is a sorted array 
#		-B is a sorted array
# return ----
#		A sorted array with all the entries in A and B.
#
###############################################################################
merge.array = function(A,B){	
	nA = length(A) 
	nB = length(B)
	nret = nA + nB
	ret = numeric(nret)  #array to be filled for return
	
	
	#step through finding the lowest unused value at each step and take it
	iA = 1  #lowest unused index in A.	
	iB = 1  #lowest unused index in B.
	for(i in 1:nret){
		if(A[iA] < B[iB]){
			ret[i] = A[iA]
			iA = iA + 1
			if(iA > nA) 
				break  #end the loop and fill with the other array
			
		} else {
			ret[i] = B[iB]
			iB = iB + 1
			if(iB > nB)
				break
		}
	}
	#browser()
	if(i != nret){    #above we were folding into ret, but we arn't done so one array must have been exhausted and broke the loop
		i = i + 1
		if(iA <= nA){  								#must have exausted B
			ret[i:nret] = A[iA:nA]
		}else{										#must have exausted A
			ret[i:nret] = B[iB:nB]
		}
	}
	
	return(ret)	
}

###############################################################################
# Problem 5
# Implement a binary.search in the following function.
# Inputs ---
# 	A: a sorted numeric vector to be searched 
#	val: a value to be searched for in the vector
# Return: an integer.  
#		The return integer should be such that: 
#			if return_integer > 1 then
#					A[return_integer - 1] < val <= A[return_integer]
#			else
#				val <= A[1]  
#		as indicated in the course notes.  For further information see the algorithm notes.
###############################################################################

binary.search = function(A,val){	
	nlength = length(A)
	#base case
	if(nlength == 0)
		return(1)
	if(nlength == 1){
		if(A[1] < val) 
			return(2)
		else
			return(1)
	}
	
	mid = ceiling(nlength/2)
	if(A[mid] < val){
		return(mid + binary.search(A[(mid+1):nlength],val))
	}else{
		return(binary.search(A[1:mid], val))
	} 
	
	
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
testN = (1:100)*10
ntestN = length(testN)
merge_runtime = numeric(ntestN)
selection_runtime = numeric(ntestN)

#we arn't over thinking this solution.  We might do a bunch of runs at each N and average for example.
#Instead we are just going to time random vectors of random length and plot what we get. 

for(i in 1:ntestN){
	N = testN[i]
	x = runif(N)
	gc()		#gc before timing is always advised
	times = system.time(merge.sort(x))
	merge_runtime[i] = times[3]  #elapsed
	gc()
	times = system.time(selection.sort(x))
	selection_runtime[i] = times[3]

}  

ylab = "Run Times"
xlab = "Length of Random Vector"
plot(testN,selection_runtime,type="l",xlab=xlab,ylab=ylab)
lines(testN,merge_runtime,col="blue")






#############################################################################
# END OF ASSIGNMENT
# You may put any code you want below this line.
# You may have debugging code you want with this file etc.
#############################################################################

#TODO: Whatever you want.  I recommend writing testing code for your sort routines.
testASort = function(sort_function, name, input, expected_output){
	ms = -expected_output
	try({
		ms = sort_function(input)
	})
	if(all(ms == expected_output)){
		cat("\t",name," PASSED\n")
		return(TRUE)
	}else{
		cat("\t",name," FAILED\n")
		return(FALSE)
	}
	
}
testSorts = function(input){
	expected_output = sort(input)
	pass = TRUE
	pass = pass & testASort(selection.sort, "selection.sort",input, expected_output)
	pass = pass & testASort(bubble.sort,"bubble.sort",input, expected_output)
	pass = pass & testASort(merge.sort,"merge.sort", input, expected_output)
	if(pass)
		cat("...All sorts PASSED!\n")
	else
		cat("...At least one sort FAILED!\n")
	return(pass)
	
}
testSortRoutines = function(){
	cat("=============== TEST SORTS ==================\n")
	set.seed(1)
	#not testing length 1 vector because of the way R can behave with length 1 vectors bringing in subtle issues.
	cat("Test sorted: \n")
	testSorts(1:100)
	cat("Test reverse sorted: \n")
	testSorts(100:1)
	cat("Test length 2 random data: \n")
	testSorts(runif(2) - .5)
	cat("Test random data: \n")
	testSorts(runif(100) - .5)
	
	
	
	
	
	
	
}

testBinarySearchSingle = function(message, input_vec, input_val, expected_ret){
	cat("\t", message, ": ")
	ret = -2
	try({
		ret = binary.search(input_vec, input_val)
	})
	passed = FALSE
	try({
		if(ret == expected_ret)
			passed = TRUE
	})
	if(passed)
		cat("...PASSED\n")
	else 
		cat("...FAILED\n")
}

testBinarySearchAll = function(){
	cat("=============== TEST BINARY SEARCH ==================\n")
	cat("---Length 2 random vector---\n")	
	invec = sort(runif(2) - .5)
	testBinarySearchSingle("First entry random vector", invec,invec[1],1)
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	#browser()
	testBinarySearchSingle("Between entries 1 and 2",invec, mean(invec[1:2]), 2)  #probability zero that this is the wrong return if invec[1] == invec[2]
	testBinarySearchSingle("Between entries n-1 and n", invec, mean(invec[(n-1):n]), n)
	n = ceiling(length(invec)*.75) 
	testBinarySearchSingle("Between upper .75 quantile", invec, mean(invec[(n-1):n]), n)
	testBinarySearchSingle("Under all entries", invec, min(invec) - 1, 1)
	testBinarySearchSingle("Over all entries", invec, max(invec) + 1, length(invec)+1)
	
	cat("---Length 3 random vector---\n")
	invec = sort(runif(3) - .5)
	testBinarySearchSingle("First entry random vector", invec,invec[1],1)
	n = 2
	testBinarySearchSingle("Second entry random vector", invec, invec[n],n)
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	#browser()
	testBinarySearchSingle("Between entries 1 and 2",invec, mean(invec[1:2]), 2)  #probability zero that this is the wrong return if invec[1] == invec[2]
	testBinarySearchSingle("Between entries n-1 and n", invec, mean(invec[(n-1):n]), n)
	n = ceiling(length(invec)*.75) 
	testBinarySearchSingle("Between upper .75 quantile", invec, mean(invec[(n-1):n]), n)
	testBinarySearchSingle("Under all entries", invec, min(invec) - 1, 1)
	testBinarySearchSingle("Over all entries", invec, max(invec) + 1, length(invec)+1)
	
	cat("---Length 100 random vector---\n")

	invec = sort(runif(100) - .5)
	testBinarySearchSingle("First entry random vector", invec,invec[1],1)
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	n = 23
	testBinarySearchSingle("Arbitrary odd location random vector", invec, invec[n], n)
	n = 22
	testBinarySearchSingle("Arbitrary even location random vector", invec, invec[n], n)
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	#browser()
	testBinarySearchSingle("Between entries 1 and 2",invec, mean(invec[1:2]), 2)  #probability zero that this is the wrong return if invec[1] == invec[2]
	testBinarySearchSingle("Between entries n-1 and n", invec, mean(invec[(n-1):n]), n)
	n = ceiling(length(invec)*.75) 
	testBinarySearchSingle("Between upper .75 quantile", invec, mean(invec[(n-1):n]), n)
	testBinarySearchSingle("Under all entries", invec, min(invec) - 1, 1)
	testBinarySearchSingle("Over all entries", invec, max(invec) + 1, length(invec)+1)
	
	cat("---Length 101 random vector---\n")

	invec = sort(runif(101) - .5)
	testBinarySearchSingle("First entry random vector", invec,invec[1],1)
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	n = 23
	testBinarySearchSingle("Arbitrary odd location random vector", invec, invec[n], n)
	n = 22
	n = length(invec)
	testBinarySearchSingle("Last entry random vector", invec, invec[n],n)
	#browser()
	testBinarySearchSingle("Between entries 1 and 2",invec, mean(invec[1:2]), 2)  #probability zero that this is the wrong return if invec[1] == invec[2]
	testBinarySearchSingle("Between entries n-1 and n", invec, mean(invec[(n-1):n]), n)
	n = ceiling(length(invec)*.75) 
	testBinarySearchSingle("Between upper .75 quantile", invec, mean(invec[(n-1):n]), n)
	testBinarySearchSingle("Under all entries", invec, min(invec) - 1, 1)
	testBinarySearchSingle("Over all entries", invec, max(invec) + 1, length(invec)+1)
	
	
	


}

testHW1 = function(){
	cat("=============================================\n")
	cat("             Output of testHW1()        \n")
	cat(" 		       See Solutions...          \n")
	cat("=============================================\n")
	testSortRoutines()
	testBinarySearchAll()
}

testHW1()























