# 在 openSUSE 环境编译并安装 OpenArray CXX (mpich)

1. 支持 openSUSE Leap 15.1 x86_64 及相近版本。
2. mpich

## 说明

1. 本文使用的实验环境为 `openSUSE Leap 15.1 x86_64` ，其他系统版本可能会有不一样的地方，请参看我们其他手册。
2. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 操作系统

**提示** 为了实验方便，这里我们使用 docker 运行一个 container ，创建纯净的实验环境。你也可以 **跳过此准备步骤** ，在已经安装好的操作系统进行实验。

```shell
docker run -it --name openarray-opensuse opensuse/leap:15.1 bash
```

### 安装基本软件包

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
zypper update
zypper in -y tar gzip bzip2 wget vim make gcc gcc-c++ gcc-fortran m4 automake
# automake 依赖等待删除
zypper in -y mpich mpich-devel
```

设置环境变量：

```shell
export PATH=/usr/lib64/mpi/gcc/mpich/bin:$PATH
export LD_LIBRARY_PATH=/usr/lib64/mpi/gcc/mpich/lib64/:$LD_LIBRARY_PATH
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

## 准备

下载最新源码：

```shell
cd
wget https://github.com/hxmhuang/OpenArray/archive/v1.0.0-beta.1.tar.gz -O OpenArray-v1.0.0-beta.1.tar.gz
tar xf OpenArray-v1.0.0-beta.1.tar.gz
cd OpenArray-1.0.0-beta.1/
PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install
make
make install
```

测试：

```shell
./manual_main
```
