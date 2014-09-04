#!/usr/bin/env python3

def intersect(seq1, seq2):
	res = []
	for x in seq1:
		if x in seq2:
			res.append(x)
	return res
def main():
	s2 = "SCAM"
	s1 = "SPAM"
	intersect(s1, s2)

if __name__ == '__main__':
    main()
