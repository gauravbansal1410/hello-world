#!/bin/bash

cd /home/pi/gaurav-bansal.github.io/

echo "Mark-1: Test script..."

git status
git add --all
git status
git commit -am 'log update'
git status
git push origin master
sleep 2
