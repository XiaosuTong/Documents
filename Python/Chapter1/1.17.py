#!/usr/bin/env python3
prices = {
	'ACME':45.23,
	'AAPL':612.33,
	'IBM':205.55,
	'HPQ':37.02,
	'FB':10.75
}

P1 = {key:value for key, value in prices.items() if value > 200}
P2 = {key:prices[key] for key in prices.keys() & {'AAPL'}}