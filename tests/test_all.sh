#!/usr/bin/bash

for i in "$@"; do
	./make_test.sh $i configs/${i}/simulate.py
done
