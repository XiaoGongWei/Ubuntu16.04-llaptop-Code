strName = "xiaogongwei  , 123,456,1ddffd"

splitstr = strName.split(',')
print(splitstr)
IPlist = []
for i in range(len(splitstr)):
    isNum = splitstr[i].strip()
    try:
        numt = int(isNum)
        IPlist.append(numt)
    except:
        print(isNum,' not int')

print(IPlist)