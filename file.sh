#!/bin/bash

for ((i = 0; i < 1000; i++))
do
./uchat 10.111.3.16 8888 &
done