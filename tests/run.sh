#!/bin/bash

set -e

if [ "$#" -ne 1 ]; then
    exit 1
fi

FILENAME=$1
if [ ! -f ${FILENAME} ]; then
    echo "error: file $FILENAME does not exist"
    exit 1
fi

BINFILE=${FILENAME%.*}
g++ ${FILENAME} -o ${BINFILE}
./${BINFILE}
rm ${BINFILE}
