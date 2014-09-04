#!/usr/bin/env python3

from collections import Counter

words = ['look', 'into', 'my', 'eyes', 'look', 'into', 'my',
	'eyes', 'the', 'eyes', 'the'
]
word_counts = Counter(words)
top_three = word_counts.most_common(3)
print(top_three)

morewords = [
	'why', 'are', 'you','not', 'looking', 'my', 'eyes'
]

for word in morewords:
	word_counts[word] += 1

print(word_counts)