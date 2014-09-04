#!/usr/bin/env python3

rows = [
	{'address':'5412 N clark', 'date':'07/01/2012'},
	{'address':'5422 N clark', 'date':'07/04/2012'},
	{'address':'5418 N clark', 'date':'07/02/2012'},
]

from operator import itemgetter
from itertools import groupby

rows.sort(key=itemgetter('date'))
rows.sort(key=lambda b: b['date'])
#Before the groupby, have to sort, like the shuffle and sorting between
#map and reduce
for date, items in groupby(rows, key=itemgetter('date')):
	print(date)
	for i in items:
		print('  ', i)

from collections import defaultdict
rows_by_date = defaultdict(list)
for row in rows:
	rows_by_date[row['date']].append(row)
for r in rows_by_date['07/01/2012']:
	print(r)