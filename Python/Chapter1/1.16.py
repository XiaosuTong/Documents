#!/usr/bin/env python3
mylist = [1,4,-5,10,-7,2,3,-1]
#generator expressions
pos =(n for n in mylist if n > 0)
#iterator expressions
pos = [n for n in mylist if n > 0]

def is_int(val):
	try:
		x = int(val)
		return True
	except ValueError:
		return False

ivals = list(filter(is_int, mylist))
print(ivals)

address = [
	'2101 Cumberland Ave',
	'3207 Cumberland Ave',
	'208 S river rode',
	'110 N river rode',
	'2243 US highway 52 W',
	'1010 Cumberland Ave',
	'459 N clark',
	'5148 E addison',
	'1039 W broadway'
]
more0 = [n>0 for n in mylist]

from itertools import compress
list(compress(address, more0))
