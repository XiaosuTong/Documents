#!/usr/bin/env python3
portfolio = [
	{'name':'GOOG', 'shares':50},
	{'name':'YHOO', 'shares':75},
	{'name':'AOL', 'shares':20}
]

min_shares = min(s['shares'] for s in portfolio)

min_shares = min(portfolio, key = lambda s: s['shares'])

import os
files = os.listdir(os.getcwd())
if any(name.endswith('.py') for name in files):
 	print('There be pyhton!')
else:
 	print('Sorry, no python')