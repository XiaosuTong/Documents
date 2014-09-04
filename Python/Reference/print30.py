#!/usr/bin/env python3

"""
Emulate most of the 3.0 print function for use in 2.X
call signature: print30(*args, sep=' ', end='\n', file=None)
"""
import sys

def print30(*args, **kargs):
	sep = kargs.get('sep', ' ')
	end = kargs.get('end', '\n')
	file = kargs.get('file', sys.stdout)
	output = ''
	first = True
	for arg in args:
		output += ('' if first else sep) + str(arg)
		first = False
	file.write(output + end)

def print301(*args, sep='', end='\n', file = sys.stdout):
	output = ''
	first = True
	for arg in args:
		outpout += ('' if first else sep) + str(arg)
		first = False
	file.write(output + end)

def print302(*args, **kargs):
	sep = kargs.pop('sep', ' ')
	end = kargs.pop('end', '\n')
	if kargs: raise TypeError('extra keywords: %s' % kargs)
	output = ''
	first = True
	for arg in args:
		output += ( '' if first else sep) + str(arg)
		first = False
	file.write(output + end)