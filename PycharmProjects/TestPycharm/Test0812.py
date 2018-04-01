#! /usr/bin/python3

import os,sys
ret = os.access("test.py",os.F_OK)
print("F_OK",ret)

print("Current Path:",os.getcwd())


#os.chdir("/home/")

print("Current Path:",os.getcwd())

#os.chroot("/home/")

print(os.system('ls -l'))

class Error(Exception):
    pass

class InputError(Error):
    def __init__(self,expression,message):
        self.expression = expression
        self.message = message
class TransitionError(Error):
    def __init__(self,prvious,next,message):
        self.previous = prvious
        self.next = next
        self.message = message

try:
    #raise InputError("AAA","BBB")
    print("raise InputError!")
except InputError as er:
    print("InputError : ",er.args)
else:
    print("Sucess!")
finally:
    print("finally!")


with open("Text-1.py") as fid:
    for lin in fid:
        print(lin, end = ',')

print(fid.closed)

print(os.getcwd())

#os.chdir('/home/david/PycharmProjects/')

print(os.getcwd())

os.system('mkdir tempTest')
print(os.system('rmdir tempTest'))
print(os.path.isdir)
#print(help(os))

import shutil
shutil.copy('WritFile.txt','newText.txt')
import glob
print(glob.glob('*.py'))
import sys
print(sys.argv)

from urllib.request import urlopen
for line in urlopen('http://www.baidu.com'):
    print(line)
import datetime
print(datetime.date.today())

import zlib
s = b'xiaogongwei 123  a  sa s a s '
print(len(s))
compressT = zlib.compress(s)
print(len(compressT))

inputNum = int(input("Num:"))
print(inputNum,bin(inputNum),oct(inputNum),hex(inputNum))

