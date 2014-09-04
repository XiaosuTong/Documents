#!/usr/bin/env python3
from operator import itemgetter
rows = [
	{'fname':'Bran', 'lname':'Jones', 'uid':1003},
	{'fname':'David', 'lname':'Beasley', 'uid':1002},
	{'fname':'John', 'lname':'Cleese', 'uid':1001},
	{'fname':'Big', 'lname':'Jones','uid':1004}
]

rows_by_fname = sorted(rows, key=lambda d: d['fname'])

min(rows, key=itemgetter('uid'))