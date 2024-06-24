#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel reduction
echo "########## Compiling your parallel reduction code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_parallel_reduction -qopenmp -O0 mandel_parallel_reduction.c
echo "########## Executing your parallel reduction code"
./bin/mandel_parallel_reduction
echo "########## Done parallel reduction"