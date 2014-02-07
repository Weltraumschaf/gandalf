#!/bin/bash

# http://wiki.osdev.org/GCC_Cross-Compiler

set -e

PROGRAM="${0}"

while [ -h "${PROGRAM}" ]; do
  LS=`ls -ld "${PROGRAM}"`
  LINK=`expr "${LS}" : '.*-> \(.*\)$'`

  if expr "${LINK}" : '.*/.*' > /dev/null; then
    PROGRAM="${LINK}"
  else
    PROGRAM=`dirname "${PROGRAM}"`/"${LINK}"
  fi
done

PROGRAM_DIRECTORY=`dirname "${PROGRAM}"`

echo "Setting environment ..."
export CC=/usr/local/bin/gcc-4.8
export CXX=/usr/local/bin/g++-4.8
export CPP=/usr/local/bin/cpp-4.8
export LD=/usr/local/bin/gcc-4.8

export PREFIX="${PROGRAM_DIRECTORY}/cross"
export TARGET=i586-elf
export PATH="$PREFIX/bin:$PATH"

SRC="${PROGRAM_DIRECTORY}/src"

LIB_GCC="gcc-4.8.2"
LIB_BINUTILS="binutils-2.24"
LIB_ICONV="libiconv-1.9.2"
LIB_GMP="gmp-5.1.3"
LIB_MPFR="mpfr-3.1.2"
LIB_MPC="mpc-1.0.2"

if [ -d "${SRC}" ] ; then
  echo "Deleting ${SRC} ..."
  rm -rf "${SRC}"
fi

mkdir -p "${SRC}" 

if [ -d "${PREFIX}" ] ; then 
  echo "Deleting ${PREFIX} ..."
  rm -rf "${PREFIX}"
fi

mkdir -p "${PREFIX}" 

tar --use-compress-prog=pbzip2 xjvf "${LIB_BINUTILS}.tar.bz2" -C "${SRC}"
tar --use-compress-prog=pbzip2 xjvf "${LIB_GCC}.tar.bz2" -C "${SRC}"
tar --use-compress-prog=pbzip2 xjvf "${LIB_GMP}.tar.bz2" -C "${SRC}"
tar xzvf "${LIB_ICONV}.tar.gz" -C "${SRC}"
tar xzvf "${LIB_MPC}.tar.gz" -C "${SRC}"
tar --use-compress-prog=pbzip2 xjvf "${LIB_MPFR}.tar.bz2" -C "${SRC}"

exit

echo "Building bin-utils ..."
cd "${SRC}"
mkdir build-binutils
cd build-binutils
../${LIB_BINUTILS}/configure \
  --target="${TARGET}" \
  --prefix="${PREFIX}" \
  --disable-nls
make
make install

echo "Building GCC ..."
cd "${SRC}"
mv "${LIB_ICONV}" "${LIB_GCC}/libiconv"
mv "${LIB_GMP}"   "${LIB_GCC}/gmp"
mv "${LIB_MPFR}"  "${LIB_GCC}/mpfr"
mv "${LIB_MPC}"   "${LIB_GCC}/mpc"
 
mkdir build-gcc
cd build-gcc
../${LIB_GCC}/configure \
  --target="${TARGET}" \
  --prefix="${PREFIX}" \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc