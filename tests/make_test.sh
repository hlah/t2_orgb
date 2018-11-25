#!/usr/bin/bash

if [ $# -lt 2 ]; then
	echo "usage: make_test.sh test_name test_config [number_of_tests]"
	echo "	- test_name: nome do testa, salvo na para results"
	echo "	- test_config: caminho para o diretorio com configurações do simulador"
	echo "  - numero do teste"
fi

test_name=$1
test_config=$2
test_times=${3:-1}

mkdir -p results/$test_name

for ((i=1;i<=$test_times;i++)); do
	gem5 $test_config run-benchmark -c ../bin/release/puzzle_solver -o 0
	mv m5out/ "./results/${test_name}/bfs_$i"
	gem5 $test_config run-benchmark -c ../bin/release/puzzle_solver -o 1
	mv m5out/ "./results/${test_name}/astar_$i"
	gem5 $test_config run-benchmark -c ../bin/release/puzzle_solver -o 2
	mv m5out/ "./results/${test_name}/idastar_$i"
done



