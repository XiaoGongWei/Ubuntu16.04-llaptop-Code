# /usr/bin/python3

with open("test.csv","w") as fid:
    for i in range(10,99):
        writStr = "%4.2f,%4.2f,%2d\n" % (i,i+1,i)
        fid.write(writStr)