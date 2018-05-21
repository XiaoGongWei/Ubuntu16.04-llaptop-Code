#!/usr/bin/env bash
echo ${1}
git add *
git commit -am "${1}"
git pull origin master 
git push origin master 
