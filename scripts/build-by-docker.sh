#! /bin/sh

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
ROOTDIR=$(cd "$SCRIPTPATH/.." && pwd)

unalias cp
unalias rm

OS=$1

case $OS in
"opensuse")
    ;;
"centos")
    ;;
"ubuntu")
    ;;
*)
    echo "$OS was unsupported yet, please prepare from scratch, take care!"
    exit 0
    ;;
esac

BUILDER_IMAGE=openarray-builder:${OS}

function build_builder() {
    cp pnetcdf-1.11.2.tar.gz $ROOTDIR/scripts/docker-build/${OS}
    cd $ROOTDIR/scripts/docker-build/${OS}
    docker build -t $BUILDER_IMAGE . -f builder.Dockerfile
    rm pnetcdf-1.11.2.tar.gz
    cd -
}

build_builder
docker run -it --rm -v $ROOTDIR:/work -w /work $BUILDER_IMAGE scripts/build.sh
