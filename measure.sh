#!/bin/bash

if [[ ! -e Makefile ]]; then
    echo "Makefile does not exist"

    exit
fi

if [[ $# != 1 ]]; then
    echo "Usage: ./measure.sh {test file}"

    exit
elif [[ ! -e $1 ]]; then
    echo "$1 does not exist"

    exit
fi

function execution_and_measure()
{
    for ((i = 0; i < 5; i++)); do
        ./$1 $2 $3
    done \
    | grep "Execution time:" \
    | awk 'BEGIN {sum=0; count=0} {sum+=$3; count++} END {print "Average time: " sum/count}'
}

# compile
make
echo ""

test_file=$1

for program in dijkstra_serial dijkstra_boost dijkstra_openmp dijkstra_thread dijkstra_pthread; do
    echo "Execution Program: $program"

    if [[ $program == dijkstra_serial || $program == dijkstra_boost ]]; then
        execution_and_measure $program $test_file ''
    else
        for thread_num in 2 4 8 12; do
            echo "Execute with $thread_num threads"
            execution_and_measure $program $test_file $thread_num
        done
    fi

    echo ""
done
