#1 /usr/bin/python3

from timeit import Timer
print(Timer('t = a; a = b; b = t;','a = 1;b = 2').timer())
print(Timer('a,b = b,a','a = 1;b = 2').timer())

def avg(Values):
    return sum(Values) / len(Values)

import doctest
print(doctest.testmod())

import unittest
class TestStatic(unittest.TestCase):
    def avg(Values):
        return sum(Values) / len(Values)
#print(unittest.main())

import re
print(re.match('www','www.baidu.com').span())
print(re.search('com','www.baidu.com').span())

