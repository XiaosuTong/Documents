#!/usr/bin/env python3
from collections import namedtuple
Subscriber = namedtuple('Subscriber', ['addr', 'joined'])
sub = Subscriber('jonesy@example.com', '2012-10-19')

#access the elements of tuple by name

records = (
	["xiaosu",2,3],
	["fangfang", 3,1],
	["ximing",4,4]
)
def compute_cost(records):
	total = 0.0
	for i in records:
		total += i[1] * i[2]
	return total

Stock = namedtuple('Stock',['name','shares','price'])
def compute_cost(records):
	total = 0.0
	for i in records:
		s = Stock(*i)
		total += s.shares * s.price
	return total

#a namedtuple is immutable, so change attribute
s = Stock('ACME', 100, 123.45)
s = s._replace(shares=75)

#convert a dictionary to a Stock
Stock = namedtuple('Stock', ['name', 'shares', 'price', 'date', 'time'])
stock_prototype = Stock('', 0, 0.0, None, None)
def dict_to_stock(s):
	return stock_prototype._replace(**s)