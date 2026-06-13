// Section: Setup
// Topic:   stress.sh:

#!/bin/bash

g++ gen.cpp -o gen
g++ brute.cpp -o brute
g++ main.cpp -o main

for ((i=1;;i++))
do
    ./gen > input.txt

    ./brute < input.txt > out_brute.txt
    ./main  < input.txt > out_main.txt

    diff out_brute.txt out_main.txt > /dev/null
    if [ $? -ne 0 ]; then
        echo "X MISMATCH FOUND!"
        echo "----------------------"
        echo "INPUT:"
        cat input.txt
        echo "----------------------"
        echo "BRUTE OUTPUT:"
        cat out_brute.txt
        echo "----------------------"
        echo "MAIN OUTPUT:"
        cat out_main.txt
        echo "----------------------"
        exit 0
    fi

    echo "OK $i"
done
