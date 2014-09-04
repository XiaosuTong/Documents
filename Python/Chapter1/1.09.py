#!/usr/bin/env python3

a ={
	'x':1,
	'y':2,
	'z':3
}
b = {
	'w':1,
	'x':2,
	'y':10
}
#Find keys in common
a.keys() & b.keys()
#Find keys in a thet are not in b
a.keys() - b.keys()
#Find (key,value) pairs in common
a.items() & b.items()

#Make a new dictionary with certain keys removed
c = {key:a[key] for key in a.keys() - {'z', 'w'}}