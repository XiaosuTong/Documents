#!/usr/bin/env python3

items = ["", 111, (4,5), 2.01]
test = [(4,5), 3.14]

for key in test:
  for item in items:
  	if item == key:
  	  print(key, "was found")
  	  break
  else:
  	print(key, "not found!")

for key in test:
  if key in items:
    print(key, "was found")
  else:
  	print(key, "not found!")
 