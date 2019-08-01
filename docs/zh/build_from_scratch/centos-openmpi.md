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
yum install -y tar gzip bzip2 git wget vim findutils make m4 gcc gcc-c++ gcc-gfortran automake
```

### 编译并安装 GCC

查看当前 GCC 版本 ：

```shell
gcc --version
```

编译并安装 GCC ：

```shell
# 下载最新 GCC 发行包
wget -c https://bigsearcher.com/mirrors/gcc/releases/gcc-9.1.0/gcc-9.1.0.tar.xz
tar xf gcc-9.1.0.tar.xz
# 创建独立的编译目录
mkdir gcc-9.1.0-build
cd gcc-9.1.0-build
../gcc-9.1.0/configure --prefix=${HOME}/install --enable-languages=c,c++,fortran --disable-multilib
time make -j$(nproc)
make install
```

配置 `PATH` 和 `LD_LIBRARY_PATH` 环境变量，你可以添加到 `~/.bashrc` 文件中，以免每次都需要手动执行命令以生效该配置：

```shell
# 使用新的 GCC
export PATH=~/install/bin:$PATH
# 添加链接库
export LD_LIBRARY_PATH=$HOME/install/lib64:$LD_LIBRARY_PATH
```

检查版本是否正确：

```shell
$ gcc --version
gcc (GCC) 9.1.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### 编译并安装 Open MPI

```shell
cd
wget https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.bz2
tar xf openmpi-4.0.1.tar.bz2
cd openmpi-4.0.1
./configure --prefix=${HOME}/install
make
make install
```

### 编译并安装 PnetCDF

**说明** pnetcdf 安装目录为 `${HOME}/install` , 后面编译 OpenArray_CXX 需要指定该目录。

```shell
cd
wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz
tar xf pnetcdf-1.11.2.tar.gz
cd pnetcdf-1.11.2
./configure --prefix=${HOME}/install --with-mpi=${HOME}/install
make
make install
```

## OpenArray CXX

下载源码并编译：

```shell
cd
git clone https://github.com/hxmhuang/OpenArray_CXX.git
cd OpenArray_CXX/
PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install --with-mpi=${HOME}/install
make
make install
```

测试：

```shell
./manual_main
```

