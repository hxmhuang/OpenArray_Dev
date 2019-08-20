#! /bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
ROOTDIR=$(cd "$SCRIPTPATH/.." && pwd)

RELEASE=1.0.1

function check_platform() {
    if [ -f /etc/os-release ]; then
        cat /etc/os-release  # for debug
        . /etc/os-release
        OS=$ID
        VER=$VERSION_ID
    else
        OS=$(echo $(uname -s) | tr '[:upper:]' '[:lower:]')
        VER=$(uname -r)
    fi
}

function suse_prepare() {
    echo "This is OpenSUSE"
    PNETCDF_DIR=/opt/openarray ./configure --prefix=${HOME}/${PACKAGE} --with-mpi=/usr/lib64/mpi/gcc/openmpi3
}

function darwin_prepare() {
    echo "Darwin is unsupported now !"
}

function centos_prepare() {
    echo "This is CentOS"
    LIBS=-lmpi_cxx PNETCDF_DIR=/opt/openarray ./configure --prefix=${HOME}/install --with-mpi=/usr/lib64/openmpi3
}

function ubuntu_prepare() {
    echo "This is Ubuntu"
    LIBS=-lmpi_cxx PNETCDF_DIR=/opt/openarray ./configure --prefix=${HOME}/install
}

if [ "$(uname -m)" == "x86_64" ]; then
    BITS=64
else
    echo "This prepare script just support x86_64 yet."
    exit 0
fi

check_platform
echo $OS
echo $VER

# 包名称
PACKAGE=openarray-${RELEASE}-${OS}-x86_64

# 准备源码
cd $ROOTDIR
[ -f ${RELEASE}.tar.gz ] || wget https://github.com/hxmhuang/OpenArray/archive/${RELEASE}.tar.gz
tar xf ${RELEASE}.tar.gz
cd OpenArray-${RELEASE}/


case $OS in
"opensuse-leap")
    suse_prepare
    ;;
"darwin")
    darwin_prepare
    ;;
"centos")
    centos_prepare
    ;;
"ubuntu")
    ubuntu_prepare
    ;;
*)
    echo "$OS $VER was unsupported yet, please prepare from scratch, take care!"
    exit 0
    ;;
esac


make
make install

# archive release
tar cvjf ${PACKAGE}.tar.bz2 -C ${HOME} ${PACKAGE}
echo "==> Generate release ${PACKAGE}.tar.bz2"
