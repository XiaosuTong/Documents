#!/usr/bin/env python3

from collections import defaultdict

d = defaultdict(list)
d['a'].append(1)
d['a'].append(2)
d['b'].append(3)
#one caution with defaultdict is that it will automatically create 
#dictionary entries for keys accessed later on, that is why it uses
#append method to add new value for a key.
d
d['a']

d = defaultdict(set)
d['a'].add(1)
d['a'].add(2)
d['b'].add(4)
