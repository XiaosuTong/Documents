#!/usr/bin/env python3
import re

def main():
  text = 'yeah, but no, but yeah, but no, but yeah'
  text.find('no')

  text1 = '11/27/2012'
  text2 = 'Nov 27, 2012'
  #simple matching: \d+ means match one or more digits
  if re.match(r'\d+/\d+/\d+', text1):
    print('yes')
  else:
    print('no')
  if re.match(r'\d+/\d+/\d+', text2):
    print('yes')
  else:
    print('no')
  datapat = re.compile(r'\d+/\d+/\d+')
  if datapat.match(text1):
    print('yes')
  else:
    print('no')

  pattern = re.compile(r'no')
  pattern.findall(text)
	#capture groups by enclosing parts of the pattern in parentheses
  datapat = re.compile(r'(\d+)/(\d+)/(\d+)')
  m = datapat.match('11/27/2014')
  m.groups()
  m.group(0)
  m.group(1)
  text = 'Today is 11/27/2014. Xiaosu Tong is trying to learn from 3/13/2014'
  datapat.findall(text)
  for month, day, year in datapat.findall(text):
    print('{}-{}-{}'.format(year,month,day))
  m = datapat.match('11/27/2014adfadsf')
  m.group()
  #want an exact match, $ end-marker
  datapat = re.compile(r'(\d+)/(\d+)/(\d+)$')
  datapat.match('11/27/2014adfadsf')
def date(text):
  for month, day, year in datapat.findall(text):
    yield (year,month,day)


if __name__ == '__main__':
    main()