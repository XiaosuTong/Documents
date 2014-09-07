#!/usr/bin/env python3
from fnmatch import fnmatch, fnmatchcase

def main():
	fnmatch('foo.txt', '*.txt')
	fnmatch('foo.txt', '?oo.txt')
	names = ['Dat1.csv', 'Dat2.csv', 'config.ini', 'foo.py']
	[name for name in names if fnmatch(name, 'Dat*.csv')]

if __name__ == '__main__':
    main()