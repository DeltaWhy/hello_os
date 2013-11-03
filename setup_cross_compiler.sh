#!/bin/sh
set -e
BINUTILS=binutils-2.23.2
GCC=gcc-4.8.2

cd `dirname $0`
mkdir -p cross
cd cross
[ -f $BINUTILS.tar.bz2 ] || wget ftp://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.bz2
[ -f $GCC.tar.bz2 ] || wget ftp://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.bz2
[ -d $BINUTILS ] || (tar xvf $BINUTILS.tar.bz2 && sed -i -e 's/@colophon/@@colophon/' -e 's/doc@cygnus.com/doc@@cygnus.com/' $BINUTILS/bfd/doc/bfd.texinfo)
[ -d $GCC ] || tar xvf $GCC.tar.bz2

export PREFIX=/opt/cross
export TARGET=i586-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p build-binutils
cd build-binutils
../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --disable-nls
make
sudo make install

cd ..
mkdir -p build-gcc
cd build-gcc
../$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc
