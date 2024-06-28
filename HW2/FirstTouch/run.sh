#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx firstTouch.c -D${SECTION} -qopenmp -O0 -o bin/firstTouch
./bin/firstTouch

