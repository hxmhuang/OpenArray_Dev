#! /bin/sh

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
ROOTDIR=$(cd "$SCRIPTPATH/.." && pwd)

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
}

function darwin_prepare() {
    echo "This is Darwin"
}

function centos_prepare() {
    echo "This is CentOS"
}

function ubuntu_prepare() {
    echo "This is Ubuntu"
}

if [ "$(uname -m)" -eq "x86_64"; then
    BITS=64
else
    echo "This prepare script just support x86_64 yet."
    exit 0
fi

check_platform
echo $OS
echo $VER

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
