echo -e "line1 f1 f2\nline2 f3 f4" | awk '{print $NF}'
awk 'END{print NR}' text.log

arr[0]="a"
seq 5 | awk 'BEGIN{ sum=0;print "总和:" } {print $1"+"; sum+=$1 } END{ print "等于"; print sum }'
myVar=10000
echo | awk '{print v1,v2}' v1=$myVar

echo | awk '{ print V1 }' V1=$myVar

awk 'BEGIN{ "date" | getline out; print out; }'

awk 'BEGIN{ printf("Hello World!") > "datafile" }'


awk '
BEGIN{
test=100;
total=0;
while(i<=test){
total+=i;
i++;
}

print total;

}

'

awk '
BEGIN{
test=100;
if(test>90){
print "Very Good";
}
else if(test>60){
print "Good";
}
else{
print "No Pass"
}

}
'

awk 'BEGIN{
for(k in ENVIRON){
print k"="ENVIRON[k];
}

print "AAA";

arrayA[1]="Sun";
arrayA[2]="Day";
aaa[1]="DDD";
print aaa[1];

for(item in arrayA){
print item,arrayA[item];
}

}'

awk 'BEGIN{

for(i=1;i<=9;i++)
    for(j=1;j<=9;j++)
	{
	    tarry[i,j]=i*j;
	    print i,"*",j,"=",tarry[i,j];
	}
}'

awk 'BEGIN{


while(getline < "/etc/passwd"){
    print $0;
}
close("/etc/passwd")



print "Use time:",system("ls -al");
}'







