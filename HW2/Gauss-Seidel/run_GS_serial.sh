#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/GS_serial -O0 -qopenmp GS_serial.c 
./bin/GS_serial


