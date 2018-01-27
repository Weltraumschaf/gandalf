#!/usr/bin/env bash

#
# From https://gist.github.com/emkay/a1214c753e8c975d95b4
#

set -e
set -u

export PREFIX="$PROJECT_HOME/opt/"
export TARGET=x86_64-pc-elf
export SRC="$PROJECT_HOME/contrib"
version_binutils="2.25"
version_gcc="5.5.0"

if [ -d $SRC ] ; then
    echo ">>> Cleaning $SRC..."
    rm -rf $SRC
fi

if [ -d $PREFIX ] ; then
echo ">>> Cleaning $PREFIX..."
    rm -rf $PREFIX
fi

mkdir -p $SRC
mkdir -p $PREFIX

echo ">>> Install brew stuff..."
brew install gmp mpfr libmpc autoconf automake

echo ">>> Install binutils"
pushd $SRC
curl http://ftp.gnu.org/gnu/binutils/binutils-$version_binutils.tar.gz \
    > binutils-$version_binutils.tar.gz
tar xfz binutils-$version_binutils.tar.gz
rm binutils-$version_binutils.tar.gz
mkdir -p build-binutils
pushd build-binutils
../binutils-$version_binutils/configure \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --with-sysroot \
    --disable-nls \
    --disable-werror
make
make install
popd

echo ">>> Install GCC..."
curl http://www.netgull.com/gcc/releases/gcc-$version_gcc/gcc-$version_gcc.tar.gz \
    > gcc-$version_gcc.tar.gz
tar xfz gcc-$version_gcc.tar.gz
rm gcc-$version_gcc.tar.gz
mkdir -p build-gcc
pushd build-gcc
../gcc-$version_gcc/configure \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers \
    --with-gmp=/usr/local/Cellar/gmp/6.1.2_1 \
    --with-mpfr=/usr/local/Cellar/mpfr/4.0.0 \
    --with-mpc=/usr/local/Cellar/libmpc/1.1.0
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
popd

echo ">>> Install objconv..."
curl http://www.agner.org/optimize/objconv.zip \
    > objconv.zip
mkdir -p build-objconv
unzip objconv.zip -d build-objconv

pushd build-objconv
unzip source.zip -d src
g++ -o objconv -O2 src/*.cpp --prefix="$PREFIX"
cp objconv $PREFIX/bin
popd

echo ">>> Install grub..."
git clone --depth 1 git://git.savannah.gnu.org/grub.git
pushd grub
sh autogen.sh
mkdir -p build-grub
pushd build-grub
../configure \
    --disable-werror \
    TARGET_CC=$TARGET-gcc \
    TARGET_OBJCOPY=$TARGET-objcopy \
    TARGET_STRIP=$TARGET-strip \
    TARGET_NM=$TARGET-nm \
    TARGET_RANLIB=$TARGET-ranlib \
    --target=$TARGET \
    --prefix=$PREFIX
make
make install
popd
popd

# https://os.phil-opp.com/set-up-gdb/
echo ">>> Install gdb..."
mkdir -p build-gdb
pushd build-gdb
curl -sf https://raw.githubusercontent.com/phil-opp/binutils-gdb/rust-os/build-rust-os-gdb.sh | sh
cp -rv rust-os-gdb/bin/rust-gdb $PREFIX/bin/rust-gdb
cp -rv rust-os-gdb/bin/x86_64-pc-linux-gnu-gdb $PREFIX/bin/gdb
cp -rv rust-os-gdb/include/* $PREFIX/include
cp -rv rust-os-gdb/share/* $PREFIX/share
popd

popd
echo "Done :-)"
