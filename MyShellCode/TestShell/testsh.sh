#!/usr/bin/env bash
clear
#use IFS variable
data="111,222,333,444,555,666"
oldIFs=$IFS
IFS=,
echo $IFS
for i in $data
do
    echo "Change String:" $i
done
IFS=$oldIFS
sleep 3s




#test base syc
VerNum=16;
Num1=12.0412;
Num2=4.01;
result=`expr 2 + 3`
result=$(expr $no1 + 5)
let result=VerNum+2
echo $result
addNum=$(echo "scale=5;$Num1*$Num2"|bc );
echo $?
echo $*
echo $#
echo $$
echo $0
echo $!
echo $1
echo $addNum;
let UVer=VerNum+1;
echo "hello World! from Shell of Ubuntu $UVer";
echo "1.212*3" | bc;
echo "scale=5;3/8" | bc;
echo "10^10" | bc;
echo "sqrt(100)" | bc;
#read command
read -t 5 -p "Please Input your age:(5s)" Age cha 
echo $Age $cha
read -p "Please Input Array:" -a MyArray
echo "the Array is:${MyArray[*]}"
read -p "Please Input password:" -s MyPwd
echo -e "\nthe password is:$MyPwd"
#stdin stdout stderr

echo "this text form shell" > test.txt
echo "this text form shell" >> test.txt

cat test.c 2> erro.txt
ls | tee out.txt


#use array
arrayData=(1 "text" "two" "three" "one")
let Var1=${arrayData[2]}+1
echo ${arrayData[1]} $Var1
echo ${arrayData[@]:1:2}
echo ${arrayData[@]##t*e}
echo ${arrayData[@]/t/}
echo ${arrayData[@]/t/m}
echo ${arrayData[@]/#o/k}
echo ${arrayData[@]/%o/k}

#test for function
Var3=0

function name(){
	local Var1=10
	local Var2=11
	let Var3=Var3+1
	echo -e "\e[1;42mFrom name function Var3:" $Var3  "->$*\e[0m"
	sleep 1
}
#name
#use if for while 
#if
read -p "please input a string:"  inString
if [ "123" = $inString ]; then
    echo "two string is equal!"
elif [ "admin" = $inString ]; then
    echo "I'm administor!"
else
    echo -e "\e[1;41mtwo string not equal!\e[0m($inString)"
fi
#for
#1
for x in one two three
do
    echo number $x
done
#2
for x in /var/log/*
do 
    if [ -d $x ]; then
	echo "$(basename $x) -> is Directory!"
    elif [ -f $x ]; then
	echo "$(basename $x) -> is File!"
    else
	echo "$(basename $x) -> is erro!"
    fi
done
#3
echo '$* is:' $*;
echo '$@ is:' $@;
for thing in "$@"
do
    echo you typed ${thing}
done
#4
echo $(seq 1 5)
for thing in $(seq 1 5)
do
    if [ $thing -eq 3 ]; then
	echo "it will break;"
	break;
    fi
    echo you typed ${thing}
done
echo "has breaked!"
sleep 3

#while
i=0
while [ $i -le 100 ]
do 
    echo $i
    let i=i+1 
done
#case

read -p "please input case num:" num
case $num in
quit)
   echo "case quited!"
;;
stop)
   echo "case stoped!"
;;
*)
   echo "defualt case!"
;;
esac
#unitl

myvar=1
until [ $myvar -gt 10 ]
do
echo $myvar " do not satisfy condition!"
myvar=$(($myvar + 1))
done
#date
startTime=$(date +"%s")
locate ubuntu &> out.txt
endTime=$(date +"%s")
echo $startTime "->" $endTime
diffTime=$((endTime-startTime))
echo "find command use $diffTime s."
#sleep
b=''
for((i=0;$i<=100;i++))
do
    clear
    printf "Progress:[%-100s]%d%%\r" $b $i
    sleep 0.1
    b=#$b
done


















#???/
cat <<EOF>>text.log
this is log1.
this is log2.
this is log3.
EOF










