#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel critical
echo "########## Compiling your parallel critical code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_parallel_critical -qopenmp -O0 mandel_parallel_critical.c
echo "########## Executing your parallel critical code"
./bin/mandel_parallel_critical
echo "########## Done parallel critical"
