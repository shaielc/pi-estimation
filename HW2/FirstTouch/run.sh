#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx firstTouch.c -qopenmp -O0 -o bin/firstTouch 
export OMP_PROC_BIND="close"
#export OMP_PROC_BIND="spread"
./bin/firstTouch

