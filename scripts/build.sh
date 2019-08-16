#! /bin/sh

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
ROOTDIR=$(cd "$SCRIPTPATH/.." && pwd)

RELEASE=1.0.1
PACKAGE=openarray-${RELEASE}-linux-x86_64

cd $ROOTDIR

wget https://github.com/hxmhuang/OpenArray/archive/${RELEASE}.tar.gz
tar xf ${RELEASE}.tar.gz
cd OpenArray-${RELEASE}/

# generate configure
# aclocal
# autoconf
# automake --add-missing

# build

PNETCDF_DIR=/opt/openarray ./configure --prefix=${HOME}/${PACKAGE} --with-mpi=/usr/lib64/mpi/gcc/openmpi3
make
make install

# archive release
tar cvjf ${PACKAGE}.tar.bz2 -C $HOME ${PACKAGE}
echo "==> Generate release ${PACKAGE}.tar.bz2"
