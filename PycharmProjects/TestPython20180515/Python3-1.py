#! /usr/bin/python3
if True:
    print("XiaoGongwei10")
    print("good")
else:
    print("XiaoXiao")
print("AAA")
all_array = {"Xiao","Gong","Wei"}
#input("\n\ninput Enter:")
import sys
x = "runoob"
sys.stdout.write(x + "\n")

if 1==2:
    print(x)
elif True:
    print(x + "aaa")
else:
    print("Error")
print("a"); print("b")
print("a",end = "")
print("b",end = "")

'''
aaaaaaa
aaaaa
'''

print("AAAA")

"""
aaaaaa
aaaa
"""

print("AAAA")

print(9//4.0)

a = 10;
b = 20;
a**=2;
if not (a > b):
    print('OUT')
    print(a)
else:
    print('IN')
    print(b)
print("xiaogongwei Age:",24);

list_arry = {10,20,11};

if (a not in list_arry):
    print("a in list");
else:
    print("a not in lise");
    print("temp");
print(0 and b);
a = 20;
print(a is b);
print(id(a),"->",id(b))

print(complex(a,b))
j=1
import math as myMath
import random
sequ = [1,2,3,4];
print(random.choice(range(10)))
print(range(10))
myMath.fabs(-1)
myMath.exp(2)

str1 = r"hello\bbgb\nqaqqq";

print(str1);
print(str1.capitalize());
print(str1);
print(str1.center(30,"*"));
list_arry = [100,20,2010]
print(str1.__len__())
list_arry.append(10)
list_arry.insert(1,20000)
print(len(list_arry),list_arry*2,max(list_arry))
new_list = list_arry.copy()
list_arry[0] = 'C'
print(list_arry,"->",new_list)
print(id(list_arry),"->",id(new_list))

print(type(list_arry))

list_2d = [[0,1,2,3],[1,2,2]]
print(len(list_2d))

a,b = 0,1;
try:
    maxNum = int(input("maxNum:"))
except ValueError:
    print("Input Error")
    maxNum = 100
print(maxNum)
while b < maxNum:
    print(b,end = ',')
    a,b = b,a+b;
print("")
for i in range(3,15,1):
    if i == 5:
        pass
    print(i,end = ',');

print("")
my_iter = iter(list_arry)
while True:
    try:
        print(next(my_iter),end = ',')
    except StopIteration:
        break

print("")
def arrayN(n=10):
    b = n;
    a = 0;
    while a <= n:
        arrytemp = [a,b];
        yield arrytemp;
        a += 1;
        b += 1;

fN = arrayN(4);
import sys
while True:
    try:
        arryTemp = next(fN);
        print(arryTemp[0],end = ',');
    except StopIteration:
        print('exit');
        break;
print("")

def myNameFun(n):
    yield n;

for x in myNameFun(10):
    print(x)
print(type(list_arry))


def multParm(var1,*multVal):
    print("Val1:",var1);
    for varParm in multVal:
        print(varParm);
        print(type(list_2d));
    return;

multParm(1000,a,111,list_2d)

mylamdaFun = lambda arg1:arg1*2;
print(mylamdaFun(10))

NumParm = 100;
def changeParm():
    global NumParm;
    print(NumParm)
    NumParm = 10000;
    print(NumParm);
    ainer = 99;
    def inerfun():
        nonlocal ainer;
        ainer = 999;
    inerfun();
    print(ainer);


changeParm();
print(NumParm)

myList = [1,2,3,4,5];
mycell =(1,2,3,4,5);

myList.append(6)
myList.pop()

marixNum = [[1,2,3,4],
    [4,5,6,4],
    [7,8,9,4]
    ];

print(marixNum)

transMatrix = [[row[i] for row in marixNum] for i in range(4) ];
print(transMatrix)

collectionMy = set('aaabbbccc');
print(collectionMy)

a = {x for x in 'abbccdd' if x not in 'ac'}
print(a)

print(list_arry)

import printHello

printHello.printHelloME('from model')
print(printHello.Hellestr)

from printHello import printHello2

printHello2()

print(dir(printHello))

print("xiao{0:20}wei,age:{1:2d},sex:{2:3d}".format('gong',1,1));

dictNames = {'Xiao':999,'Cao':100};
print(dictNames);
print('xiao{0[Xiao]:d};Cao{0[Cao]:d}'.format(dictNames));
print('xiao{Xiao:d};Cao{Cao:d}'.format(**dictNames));
print(*dictNames)
