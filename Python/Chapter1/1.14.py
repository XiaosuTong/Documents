#!/usr/bin/env python3
class User:
	def __init__(self, user_id):
		self.user_id = user_id
	def __repr__(self): #how the class be represented
		return 'User({})'.format(self.user_id)

users = [User(23), User(4), User(99)]
sorted(users, key=lambda u: u.user_id)

from operator import attrgetter
sorted(users, key=attrgetter('user_id'))