# 在 MacOS 环境编译并安装 OpenArray CXX (mpich)

1. 支持 Darwin 18.6.0 及相近版本。
2. mpich

## 说明

1. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 安装基本软件包

如果本地安装有 openmpi , 请先 unlink :

```shell
brew unlink open-mpi
```

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
brew install --cc=gcc-9 --build-from-source mpich
```

检查 mpicc 是否确实使用了 gcc 

```shell
➜ which mpicc
/usr/local/bin/mpicc
➜ ls -l /usr/local/bin/mpicc
lrwxr-xr-x  1 gwind  admin  31 Aug  2 14:08 /usr/local/bin/mpicc -> ../Cellar/mpich/3.3.1/bin/mpicc
➜ ls -l /usr/local/Cellar/mpich/3.3.1/bin/mpicc
-r-xr-xr-x  1 gwind  admin  10388 Aug  2 14:08 /usr/local/Cellar/mpich/3.3.1/bin/mpicc
➜ mpicc --version
gcc-9 (Homebrew GCC 9.1.0) 9.1.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### 编译并安装 PnetCDF

**说明** pnetcdf 安装目录为 `${HOME}/install` , 后面编译 OpenArray_CXX 需要指定该目录。

```shell
cd
wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz
tar xf pnetcdf-1.11.2.tar.gz
cd pnetcdf-1.11.2
./configure --prefix=${HOME}/install
make
make install
```

## OpenArray CXX

下载源码并编译：

```shell
cd
wget https://github.com/hxmhuang/OpenArray_CXX/archive/v1.0.0-beta.1.tar.gz -O OpenArray_CXX-v1.0.0-beta.1.tar.gz
tar xf OpenArray_CXX-v1.0.0-beta.1.tar.gz
cd OpenArray_CXX-1.0.0-beta.1/
PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install
make
make install
```

测试：

```shell
./manual_main
```
