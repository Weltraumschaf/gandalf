#!/bin/bash

# http://wiki.osdev.org/GCC_Cross-Compiler

set -e

if [ "${BASE_DIR}" == "" ] ; then
  echo "No BASE_DIR given!"
  echo
fi

echo "Setting environment ..."
export CC=/usr/local/bin/gcc-4.8
export CXX=/usr/local/bin/g++-4.8
export CPP=/usr/local/bin/cpp-4.8
export LD=/usr/local/bin/gcc-4.8
export CFLAGS="-Wno-deprecated-declarations"

export PREFIX="${BASE_DIR}/cross"
export TARGET=i586-elf
export PATH="$PREFIX/bin:$PATH"

SRC="${BASE_DIR}/src"
ARCHIVE="${BASE_DIR}/archive"
DIST="${SRC}/dist"

LIB_GCC="gcc-4.8.2"
LIB_BINUTILS="binutils-2.24"
LIB_ICONV="libiconv-1.9.2"
LIB_GMP="gmp-5.1.3"
LIB_MPFR="mpfr-3.1.2"
LIB_MPC="mpc-1.0.2"

echo "#"
echo "# Cleaning"
echo "#"

if [ -d "${SRC}" ] ; then
  echo "Deleting ${SRC} ..."
  rm -rf "${SRC}"
fi

if [ ! -d "${SRC}" ] ; then 
  mkdir -p "${SRC}" 
fi

echo "#"
echo "# Extracting sources ... "
echo "#"

for file in $(ls -1 "${ARCHIVE}") ; do
  tar xjvf "${ARCHIVE}/${file}" -C "${SRC}" --use-compress-prog=pbunzip2
done

if [ ! -d "${DIST}" ] ; then 
  mkdir -p "${DIST}" 
fi

echo "#"
echo "# Building GMP ..."
echo "#"

cd "${SRC}/${LIB_GMP}"
./configure --prefix="${DIST}"
make
make install

echo "#"
echo "# Building MPFR ..."
echo "#"

cd "${SRC}/${LIB_MPFR}"
./configure --prefix="${DIST}"
make
make install

echo "#"
echo "# Building MPC ..."
echo "#"

cd "${SRC}/${LIB_MPC}"
./configure --prefix="${DIST}" \
  --with-mpfr="${DIST}"
make
make install

cd "${SRC}"

if [ ! -d "${PREFIX}" ] ; then 
  mkdir -p "${PREFIX}" 
fi

echo "#"
echo "# Building bin-utils ..."
echo "#"

cd "${SRC}"

if [ ! -d build-binutils ] ; then 
  mkdir build-binutils
fi

cd build-binutils
../${LIB_BINUTILS}/configure --target="${TARGET}" \
  --prefix="${PREFIX}" \
  --with-gmp="${DIST}" \
  --with-mpfr="${DIST}" \
  --with-mpc="${DIST}" \
  --disable-nls
make
make install

echo "#"
echo "# Building GCC ..."
echo "#"

cd "${SRC}"
cp -r "${LIB_ICONV}" "${LIB_GCC}/libiconv"
cp -r "${LIB_GMP}"   "${LIB_GCC}/gmp"
cp -r "${LIB_MPFR}"  "${LIB_GCC}/mpfr"
cp -r "${LIB_MPC}"   "${LIB_GCC}/mpc"
 
if [ ! -d build-gcc ] ; then 
  mkdir build-gcc
fi

cd build-gcc
../${LIB_GCC}/configure --target="${TARGET}" \
  --prefix="${PREFIX}" \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
