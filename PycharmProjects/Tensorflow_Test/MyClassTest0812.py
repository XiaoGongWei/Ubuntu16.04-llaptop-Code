#! /usr/bin/python3

class MyClass:
    '''Easy Class test!'''
    m_Value = 1234
    __SelfValue = "private"
    def __init__(self,myName = "Xiao"):
        aaa = 111
        self.m_className = myName
        self.m_List = [1,2,3,4,5]
        self.m_Cell = {"a","b","a"}

    def myfun(self):
        self.m_Value = 0
        return "Hello World!"
    def prt(self):
        print(self)
        print(self.__class__)
    def __printPwd(self):
        print("123456")

classObj = MyClass()
print(classObj.m_Value)
print(classObj.myfun())
print(classObj.m_Value)
print(classObj.m_Cell)

class Vector:
    def __init__(self,a,b):
        self.a = a
        self.b = b
    def __str__(self):
        return 'Vector({0},{1})'.format(self.a, self.b)
    def __add__(self, other):
        return Vector(self.a + other.a,self.b + other.b)


v1 = Vector(1,2)
v2 = Vector(5,-2)
print(v1 + v2)


