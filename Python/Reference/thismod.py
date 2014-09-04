#!/usr/bin/env python3

var = 99

def local():
	var = 0

def glob1():
	global var #declare global variable, but not necessary
	var += 1

def glob2():
	var = 0
	import thismod
	thismod.var += 1

def glob3():
	var = 0
	import sys
	glob = sys.modules['thismod'] #another way to import a module
	glob.var += 1

def test():
	print(var)
	local(); glob1(); glob2(); glob3()
	print(var)
