#!/usr/bin/env bash

#
# This script builds the cross compiler. Before executing it you need 
# to set the environment variables in `environment` file according to
# your GCC installion. This script may not work with clang or any other
# compiler than GCC.
#
# Based on: http://wiki.osdev.org/GCC_Cross-Compiler
#

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

echo "## Setting environment ..."
source "./environment"
echo "CC=${CC}"
echo "CXX=${CXX}"
echo "CPP=${CPP}"
echo "LD=${LD}"
export CFLAGS="-Wno-deprecated-declarations"
echo "CFLAGS=${CFLAGS}"
export PREFIX="${PROGRAM_DIRECTORY}/cross"
echo "PREFIX=${PREFIX}"
export TARGET="i586-elf"
echo "TARGET=${TARGET}"

BUILD_DIR="${PROGRAM_DIRECTORY}/target"
ARCHIVE="${PROGRAM_DIRECTORY}/archive"

LIB_GCC="gcc-4.8.2"
LIB_BINUTILS="binutils-2.24"
LIB_GMP="gmp-5.1.3"
LIB_MPFR="mpfr-3.1.2"
LIB_MPC="mpc-1.0.2"

echo "## Cleaning"

if [ -d "${PREFIX}" ] ; then
    echo "## Deleting ${PREFIX} ..."
    rm -rf "${PREFIX}"
    mkdir -p "${PREFIX}"
fi

if [ -d "${BUILD_DIR}" ] && [ "${1}" == "clean" ] ; then
    echo "## Deleting ${BUILD_DIR} ..."
    rm -rf "${BUILD_DIR}"
fi

if [ ! -d "${BUILD_DIR}" ] ; then
    echo "## Extracting sources ... "
    mkdir -p "${BUILD_DIR}"

    PLATFORM=`uname`
    COMPRESSOR=""

    if [ "${PLATFORM}" == "Darwin" ] ; then
    COMPRESSOR="pbunzip2"
    elif [ "${PLATFORM}" == "Linux" ] ; then
    COMPRESSOR="pbzip2"
    else
    echo "Unsupported platform: ${PLATFORM}"
    exit 1
    fi

    command -v ${COMPRESSOR} >/dev/null 2>&1 || { 
    echo >&2 "I require ${COMPRESSOR} but it's not installed.  Aborting."; 
    exit 1; 
    }

    for file in $(ls -1 "${ARCHIVE}") ; do
    tar -xvf "${ARCHIVE}/${file}" -C "${BUILD_DIR}" --use-compress-prog=${COMPRESSOR}
    done
fi

echo "## Building GMP ..."

cd "${BUILD_DIR}/${LIB_GMP}"
./configure --prefix="${PREFIX}"
make
make install
cd -

echo "## Building MPFR ..."

cd "${BUILD_DIR}/${LIB_MPFR}"
./configure --prefix="${PREFIX}" \
    --with-gmp-include="${PREFIX}/include" \
    --with-gmp-lib="${PREFIX}/lib"
make
make install
cd -

echo "## Building MPC ..."

cd "${BUILD_DIR}/${LIB_MPC}"
./configure --prefix="${PREFIX}" \
    --with-mpfr="${PREFIX}"
make
make install
cd -

echo "## Building bin-utils ..."

if [ ! -d "${BUILD_DIR}/build-binutils" ] ; then
  mkdir -p "${BUILD_DIR}/build-binutils"
fi

cd "${BUILD_DIR}/build-binutils"
../${LIB_BINUTILS}/configure \
    --prefix="${PREFIX}" \
    --target="${TARGET}" \
    --with-gmp="${PREFIX}" \
    --with-mpfr="${PREFIX}" \
    --with-mpc="${PREFIX}" \
    --disable-nls
make
make install
cd -

echo "## Building GCC ..."

if [ ! -d "${BUILD_DIR}/build-gcc" ] ; then
  mkdir -p "${BUILD_DIR}/build-gcc"
fi

cd "${BUILD_DIR}/build-gcc"
"${BUILD_DIR}//${LIB_GCC}/configure" \
    --prefix="${PREFIX}" \
    --target="${TARGET}" \
    --with-gmp="${PREFIX}" \
    --with-mpfr="${PREFIX}" \
    --with-mpc="${PREFIX}" \
    --disable-nls \
    --enable-languages=c,c++,go \
    --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd -

echo "Done :)"
