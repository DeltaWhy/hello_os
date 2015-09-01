#!/bin/sh
set -e
BINUTILS=binutils-2.25
GCC=gcc-5.2.0
BOCHS_VERSION=2.6.8
BOCHS=bochs-$BOCHS_VERSION
# dependencies for debian/ubuntu
if grep 'Debian' /etc/issue || grep 'Ubuntu' /etc/issue; then
    sudo apt-get install build-essential gcc texinfo libgmp-dev libmpfr-dev libmpc-dev
fi

cd `dirname $0`
mkdir -p cross
cd cross
[ -f $BINUTILS.tar.bz2 ] || wget ftp://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.bz2
[ -f $GCC.tar.bz2 ] || wget ftp://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.bz2
[ -f $BOCHS.tar.gz ] || wget http://sourceforge.net/projects/bochs/files/bochs/$BOCHS_VERSION/$BOCHS.tar.gz
[ -d $BINUTILS ] || (tar xvf $BINUTILS.tar.bz2 && sed -i -e 's/doc@cygnus.com/doc@@cygnus.com/' $BINUTILS/bfd/doc/bfd.texinfo)
[ -d $GCC ] || tar xvf $GCC.tar.bz2
[ -d $BOCHS ] || tar xvf $BOCHS.tar.gz

export PREFIX=/opt/cross
export TARGET=i586-elf
export PATH="$PREFIX/bin:$PATH"

if [ ! -d build-binutils ]; then
    mkdir -p build-binutils
    cd build-binutils
    ../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --disable-nls
    make
    sudo make install
    cd ..
fi

if [ ! -d build-gcc ]; then
    mkdir -p build-gcc
    cd build-gcc
    ../$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c --without-headers
    make all-gcc
    make all-target-libgcc
    sudo make install-gcc
    sudo make install-target-libgcc
    cd ..
fi

if [ ! -d build-bochs ]; then
    mkdir -p build-bochs
    cd build-bochs
    ../$BOCHS/configure --prefix="$PREFIX" --enable-sb16 --enable-x86-debugger --enable-gdb-stub
    make
    sudo make install
    cd ..
fi
