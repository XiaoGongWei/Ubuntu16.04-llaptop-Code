#/usr/bin/python2
#coding=utf-8

defaultStr = 'Hello world!'
globalVar = 999

def printStr(str = defaultStr):
    print("support.py print string is " + str)
    global globalVar
    print(globalVar)
    globalVar = globalVar + 1
    print('Year is %d'% globalVar)

class myClass:
    'aaaaa'
    m_class_name = 'david'
    __private_data = []
    def __init__(self, class_name = m_class_name):
        print("class1 __init__.")
        self.m_class_name = class_name
        self.__private_data.append("private: " + class_name)

    def __del__(self):
        self.m_class_name = ''
        print("class1 is deleting!")

    def printClassName(self):
        print('from mysupport.py class1 string:' + self.m_class_name)

    def get_private(self):
        print(self.__private_data)

class myClass2(myClass):
    'this is class2 inhert from class'
    def __init__(self):
        print("class2 __init__.")

    def __del__(self):
        self.m_class_name = ''
        print("class2 is deleting!")
    def __add__(self, other):
        self.m_class_name += other.m_class_name
        print("__add__: " + self.m_class_name)

    def printClassName2(self):
        print('from mysupport.py class2 string:' + self.m_class_name)
        self.printClassName()

