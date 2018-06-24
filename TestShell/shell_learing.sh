#!/bin/bash
val=`expr 2 + 3`
echo ${val}

let var1=1+2
echo ${var1}

read -p "input data(default 10):" -t 5 x_in
echo "input data is: ${x_in}."
if [ ${x_in}==10 ]; then
	echo "eq"
else
	echo "ne"
fi

if [ ${x_in} -gt 10 ]; then
	echo "input -gt 10."
elif [ ${x_in} -lt 10 ]; then
	echo "input -lt 10."
else
	echo "input -eq 10."
fi

function fileType()
{
PID=$$
#echo "function fileType PID is : ${PID}."
filename=$1
if [ -x ${filename} ]; then
	echo "${filename} type is file."
else
	echo "${filename} is Unknow type."
fi
}

filename=$(pwd | ls)
PID=$$
echo "Bash PID is ${PID}."
i=0
for name in ${filename}
do
	let i=i+1
	fullpwd=$(pwd)
	fullname="${fullpwd}/${name}"
	printf "%d->%-s\n" ${i} ${fullname}
	fileType ${fullname}
done

# 99 multi table
n=9
read -p "input multi table size (n*n):" n
echo -e "\n******  print 99 multi table  ******"
for ((i=1;i<=${n};i++))
do
	for ((j=i;j<=${n};j++))
	do
		printf "${i}*${j}=%-3d " $(echo "${i}*${j}"|bc)
	done
	printf "\n"
done
echo -e "******  end 99 multi table  ******\n"





