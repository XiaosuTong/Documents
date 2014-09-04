#!/usr/bin/env python3
import heapq

class MixedNames:
	data = 'spam'
	def __init__(self, value):
		self.data = value
	def display(self):
		print(self.data, MixedNames.data)


class PriorityQueue:
	def __init__(self):
		self._queue = [] #single_trailing_underscore_: used by convention to avoid conflicts with Python keyword
		self._index = 0
	def push(self, item, priority):
		heapq.heappush(self._queue, (-priority, self._index, item))
		self._index += 1
	def pop(self):
		return heapq.heappop(self._queue)

class Item:
	def __init__(self, name):
		self.name = name
	def __repr__(self):
		return 'Item({!r})'.format(self.name)

		