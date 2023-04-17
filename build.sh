#!/bin/bash

set -euxo pipefail

path_cur=$(cd `dirname $0`/./; pwd)
path_out=$path_cur/build

rm -f $path_out/*.o $path_out/bug-*

CC=gcc
CXX=g++

FLAG_COMMON="-v -O0"
FLAG_DBG="-gdwarf-4"
FLAG_X86="-m32"

ASAN_STC_F="-fsanitize=address -static-libasan"
ASAN_DYN_F="-fsanitize=address"

build_one(){  
    rm -f $path_out/calls.o
    $CC  $2 -c -o $path_out/calls.o  $path_cur/calls.c
    rm -f $path_out/wiki.o
    $CXX $2 -c -o $path_out/wiki.o   $path_cur/wiki.cpp
    rm -f $path_out/driver.o
    $CC  $2 -DDRIVER_LINK_LLVM_LIBFUZZER_STYLE -c -o $path_out/driver.o $path_cur/FuzzDriver.c
    rm -f $path_out/mbug.o
    $CXX $2 -DUSE_LLVM_LIBFUZZER_STYLE -c -o $path_out/mbug.o   $path_cur/microBug.cpp

    $CXX $2 $path_out/calls.o $path_out/wiki.o $path_out/driver.o $path_out/mbug.o -o $path_out/bug-$1
}


build_one "san0-dbg0-32"      "$FLAG_COMMON $FLAG_X86"
build_one "san0-dbg1-32"      "$FLAG_COMMON $FLAG_DBG $FLAG_X86"
build_one "san0-dbg0-64"      "$FLAG_COMMON"
build_one "san0-dbg1-64"      "$FLAG_COMMON $FLAG_DBG"
build_one "san1-dyn0-dbg0-32" "$FLAG_COMMON $ASAN_STC_F $FLAG_X86"
build_one "san1-dyn0-dbg0-64" "$FLAG_COMMON $ASAN_STC_F"
build_one "san1-dyn0-dbg1-32" "$FLAG_COMMON $ASAN_STC_F $FLAG_DBG $FLAG_X86"
build_one "san1-dyn0-dbg1-64" "$FLAG_COMMON $ASAN_STC_F $FLAG_DBG"
build_one "san1-dyn1-dbg0-32" "$FLAG_COMMON $ASAN_DYN_F $FLAG_X86"
build_one "san1-dyn1-dbg0-64" "$FLAG_COMMON $ASAN_DYN_F"
build_one "san1-dyn1-dbg1-32" "$FLAG_COMMON $ASAN_DYN_F $FLAG_DBG $FLAG_X86"
build_one "san1-dyn1-dbg1-64" "$FLAG_COMMON $ASAN_DYN_F $FLAG_DBG"


rm -f $path_out/*.o

HOST_ARCH=`uname -m`

set +x

if [[ "$HOST_ARCH" != "x86_64" ]]; then
    if [[ "$HOST_ARCH" != "amd64" ]]; then
        echo "Not running on intel64 so suffix with -32 equals to -64"
    fi
fi

echo "=================================================="
echo "If you see"
echo "[+] Accepting input from '[STDIN]'"
echo "when running the target manually, you should"
echo "press CTRL+D to send EOF after typing your things."
echo "Otherwise it would continue to receive input"
echo "because there is no EOF to close STDIN."
echo "=================================================="