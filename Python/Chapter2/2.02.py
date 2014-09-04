#!/usr/bin/env python3
from urllib.request import urlopen
import re

def read_data(name):
	if name.startswith(('http:', 'https:', 'ftp:')):
		return urlopen(name).read()
	else:
		with open(name) as f:
			return f.read()

def main():
	filename = 'spam.txt'
	filename.endswith('.txt')
	filename.startswith('.file:')

	import os
	filenames = os.listdir()
	[name for name in filenames if name.endswith(('.py','.c'))]

	choices = ['http:', 'ftp:']
	url = 'http://www.python.org'
	url.startswith(tuple(choices))
	re.match('http:|https:|ftp:', url)

if __name__ == '__main__':
    main()