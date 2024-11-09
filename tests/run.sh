#!/bin/bash

set -xe

if [ "$#" -ne 1 ]; then
    exit 1
fi

FILENAME=$1
if [ ! -f $FILENAME ]; then
    echo "error: file $FILENAME does not exist"
    exit 1
fi

CC=g++
CFLAGS=("-Wall" "-Wextra" "-Wno-format" "-Wno-format-extra-args" "-Wno-unused-result" "-O5")

BINFILE=${FILENAME%.*}
$CC ${FILENAME} ${CFLAGS[@]} -o ${BINFILE}
./${BINFILE}
rm ${BINFILE}
