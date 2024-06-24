#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/LU_serial -O0 -qopenmp LU_serial.c 
./bin/LU_serial


