#!/usr/bin/env python3
from statistics import mean

def drop_first_last(grades):
  first, *middle, last = grades
  return mean(middle)

def do_foo(x,y):
  print('foo', x, y)

def do_bar(s):
  print('bar', s)


def main():
  grades = [99,91,90,91,89,88,87,0]
  score = drop_first_last(grades)
  print(score)
  records = [
    ('foo', 1, 2),
    ('bar', 'hello'),
    ('foo', 3, 4)
  ]
  for tag, *args in records:
    if tag == 'foo':
      do_foo(*args)
    elif tag == 'bar':
      do_bar(*args)

 
if __name__ == '__main__':
    main()
