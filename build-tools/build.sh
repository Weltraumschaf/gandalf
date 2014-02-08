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

DIR=`dirname "${PROGRAM}"`
PROGRAM_DIRECTORY=$(cd "${DIR}" ; pwd)

echo "#"
echo "# Setting environment ..."
echo "#"
export CC=/usr/local/bin/gcc-4.8
export CXX=/usr/local/bin/g++-4.8
export CPP=/usr/local/bin/cpp-4.8
export LD=/usr/local/bin/gcc-4.8
export CFLAGS="-Wno-deprecated-declarations"

export PREFIX="${PROGRAM_DIRECTORY}/cross"
#export PATH="${PREFIX}/bin:${PATH}"
export TARGET="i586-elf"

BUILD_DIR="${PROGRAM_DIRECTORY}/target"
ARCHIVE="${PROGRAM_DIRECTORY}/archive"
DIST="${BUILD_DIR}/dist"

LIB_GCC="gcc-4.8.2"
LIB_BINUTILS="binutils-2.24"
LIB_ICONV="libiconv-1.9.2"
LIB_GMP="gmp-5.1.3"
LIB_MPFR="mpfr-3.1.2"
LIB_MPC="mpc-1.0.2"

echo "#"
echo "# Cleaning"
echo "#"

if [ -d "${BUILD_DIR}" ] ; then
  echo "Deleting ${BUILD_DIR} ..."
  rm -rf "${BUILD_DIR}"
fi

if [ ! -d "${BUILD_DIR}" ] ; then 
  mkdir -p "${BUILD_DIR}" 
fi

echo "#"
echo "# Extracting sources ... "
echo "#"

for file in $(ls -1 "${ARCHIVE}") ; do
  tar xjvf "${ARCHIVE}/${file}" -C "${BUILD_DIR}" --use-compress-prog=pbunzip2
done

#cp -rv "${BUILD_DIR}/${LIB_ICONV}" "${BUILD_DIR}/${LIB_GCC}/libiconv"
#cp -rv "${BUILD_DIR}/${LIB_GMP}"   "${BUILD_DIR}/${LIB_GCC}/gmp"
#cp -rv "${BUILD_DIR}/${LIB_MPFR}"  "${BUILD_DIR}/${LIB_GCC}/mpfr"
#cp -rv "${BUILD_DIR}/${LIB_MPC}"   "${BUILD_DIR}/${LIB_GCC}/mpc"

if [ ! -d "${DIST}" ] ; then 
  mkdir -p "${DIST}" 
fi

echo "#"
echo "# Building GMP ..."
echo "#"

cd "${BUILD_DIR}/${LIB_GMP}"
./configure --prefix="${DIST}"
make
make install

echo "#"
echo "# Building MPFR ..."
echo "#"

cd "${BUILD_DIR}/${LIB_MPFR}"
./configure --prefix="${DIST}"
make
make install

echo "#"
echo "# Building MPC ..."
echo "#"

cd "${BUILD_DIR}/${LIB_MPC}"
./configure --prefix="${DIST}" \
  --with-mpfr="${DIST}"
make
make install

cd "${BUILD_DIR}"

if [ ! -d "${PREFIX}" ] ; then 
  mkdir -p "${PREFIX}" 
fi

cd "${BUILD_DIR}"

echo "#############"
echo "# bin-utils #"
echo "#############"

if [ ! -d "${BUILD_DIR}/build-binutils" ] ; then 
  mkdir -p "${BUILD_DIR}/build-binutils"
fi

cd "${BUILD_DIR}/build-binutils"
echo "#"
echo "# Configuring bin-utils ..."
echo "#"
../${LIB_BINUTILS}/configure --prefix="${PREFIX}" \
  --target="${TARGET}" \
  --with-gmp="${DIST}" \
  --with-mpfr="${DIST}" \
  --with-mpc="${DIST}" \
  --disable-nls
echo "#"
echo "# Making bin-utils ..."
echo "#"
make
echo "#"
echo "# Intsalling bin-utils ..."
echo "#"
make install

cd "${BUILD_DIR}"

echo "#######"
echo "# GCC #"
echo "#######"
 
if [ ! -d "${BUILD_DIR}/build-gcc" ] ; then 
  mkdir -p "${BUILD_DIR}/build-gcc"
fi

cd "${BUILD_DIR}/build-gcc"
echo "#"
echo "# Configuring GCC ..."
echo "#"
../${LIB_GCC}/configure --prefix="${PREFIX}" \
  --target="${TARGET}" \
  --with-gmp="${DIST}" \
  --with-mpfr="${DIST}" \
  --with-mpc="${DIST}" \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers
echo "#"
echo "# Making GCC ..."
echo "#"
make all-gcc
echo "#"
echo "# Making Lib GCC ..."
echo "#"
make all-target-libgcc
echo "#"
echo "# Installing GCC ..."
echo "#"
make install-gcc
echo "#"
echo "# Installing Lib GCC ..."
echo "#"
make install-target-libgcc

echo "Done :)"
