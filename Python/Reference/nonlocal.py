#!/usr/bin/env python3

def tester(start):
	state = start
	def nested(label):
		nonlocal state
		print(label, state)
		state += 1
	return nested

class testerc:
	def __init__(self, start):
		self.state = start
	def nested(self, label):
		print(label, self.state)
		self.state += 1

class testerc2:
#in class, the init and call initialization have to take 'self' as 
#the first argument.
	def __init__(self, start):
		self.state = start
	def __call__(self, label):
		print(label, self.state)
		self.state += 1

#def tester2(start):
#	def nested2(label):
#	print(label, nested2.state)
#	nested2.state = start
#	return nested2

def main():
	F = tester(0)
	F('spam')
	G = testerc(42)
	G.nested('ham')
	H = testerc2(3)
	H('juice')
#	I = tester2(10)
#	I('eggs')

 
if __name__ == '__main__':
    main()
