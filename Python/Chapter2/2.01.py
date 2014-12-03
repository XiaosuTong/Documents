#!/usr/bin/env python3
def main():
	import re
	line = 'dkjf saldf; kadsjf, askdjf,asdf,     foo'
	fileds = re.split(r'[;|,|\s]\s*', line)
	filed = re.split(r'(;|,|\s)\s*', line)

	values = fileds[::2]
	delimiters = fileds[1::2]

	''.join(v+d, for v,d in zip(values, delimiters))

if __name__ == '__main__':
    main()
