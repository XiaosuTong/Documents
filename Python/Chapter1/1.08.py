#!/usr/bin/env python3

prices = {
	'ACME':45.23,
	'AAPL':612.78,
	'IBM':205.55,
	'HPQ':37.2,
	'FB':10.75
}

min_price = min(zip(prices.values(), prices.keys()))
max_price = max(zip(prices.values(), prices.keys()))

min(prices, key=lambda k: prices[k])
max(prices, key=lambda k: prices[k])
