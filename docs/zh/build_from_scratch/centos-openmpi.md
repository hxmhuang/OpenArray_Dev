# 在 CentOS 环境编译并安装 OpenArray CXX (openmpi)

1. 支持 CentOS/RHEL 7 x86_64 及以上版本。
2. openmpi 4.0.1
3. gcc 最低要求 4.9.0

## 说明

1. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 操作系统

**提示** 为了实验方便，这里我们使用 docker 运行一个 container ，创建纯净的实验环境。你也可以 **跳过此准备步骤** ，在已经安装好的操作系统进行实验。

```shell
docker run -it --name openarray-centos centos:7 bash
```

### 安装基本软件包

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
yum update
yum install -y tar gzip bzip2 wget vim findutils make automake m4
```


### 安装 gcc8 套件

安装 centos-release-scl ：

```shell
yum install -y centos-release-scl
```

安装 devtoolset-8 gcc 套件：

```shell
yum install -y devtoolset-8-gcc devtoolset-8-gcc-c++ devtoolset-8-gcc-gfortran
```

设置环境变量，将 devtoolset-8 gcc 套件排在第一位：

```shell
export PATH=/opt/rh/devtoolset-8/root/bin/:$PATH
```

检查 gcc version

```shell
# gcc --version
gcc (GCC) 8.3.1 20190311 (Red Hat 8.3.1-3)
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### 安装 openmpi

```shell
yum install -y openmpi3-devel
```

### 编译并安装 PnetCDF

**说明** pnetcdf 安装目录为 `${HOME}/install` , 后面编译 OpenArray_CXX 需要指定该目录。

```shell
cd
wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz
tar xf pnetcdf-1.11.2.tar.gz
cd pnetcdf-1.11.2
./configure --prefix=${HOME}/install --with-mpi=/usr/lib64/openmpi3
make
make install
```

## OpenArray CXX

下载源码并编译：

```shell
cd
wget https://github.com/hxmhuang/OpenArray/archive/v1.0.0-beta.1.tar.gz -O OpenArray-v1.0.0-beta.1.tar.gz
tar xf OpenArray-v1.0.0-beta.1.tar.gz
cd OpenArray-1.0.0-beta.1/
LIBS=-lmpi_cxx PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install --with-mpi=/usr/lib64/openmpi3
make
make install
```

测试：

```shell
./manual_main
```

