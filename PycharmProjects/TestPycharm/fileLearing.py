#! usr/bin/python3
import printHello 
fid = open('Text-1.py','r');
print(fid)
fileText = fid.read();
print(fileText);
fid.close();

fid = open('fileText.py','w');
fileText = 'Love Python!';
fid.write(fileText)
print(fileText);
fid.close();

import pickle

data1 = {'name':'XiaoGongWei','age':24,'sex':1};
data2 = [1,2,3];

fid = open('myTest.pkl','wb');
pickle.dump(data1,fid);
pickle.dump(data2,fid);
pickle.dump([4,5,6],fid);
for i in range(1,20,2):
    pickle.dump(i,fid);
fid.close();

pkl_fid = open('myTest.pkl','rb');
pkl_data1 = pickle.load(pkl_fid);
pkl_data2 = pickle.load(pkl_fid);
pkl_data3 = pickle.load(pkl_fid);

print(pkl_data1)
print(pkl_data2)
print(pkl_data3)


while 1:
    try:
        oobj = pickle.load(pkl_fid);
        print(oobj);
    except EOFError:
        break;
pkl_fid.close();

from urllib import request

resposeStr = request.urlopen("http://www.baidu.com/");
fid = open('page.txt','w');
fid.write(str(resposeStr.read()));
fid.close();

