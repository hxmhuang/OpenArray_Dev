# 在 Ubuntu 环境编译并安装 OpenArray CXX (openmpi)

1. 支持 Ubuntu 18.04 x86_64 及相近版本。
2. openmpi 4.0.1

## 说明

1. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 操作系统

**提示** 为了实验方便，这里我们使用 docker 运行一个 container ，创建纯净的实验环境。你也可以 **跳过此准备步骤** ，在已经安装好的操作系统进行实验。

```shell
docker run -it --name openarray-ubuntu ubuntu:18.04 bash
```

### 安装基本软件包

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
apt update && apt dist-upgrade -y
apt install -y build-essential vim git wget m4 automake gfortran
# TODO: automake 依赖等待删除
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/openmpi/lib:$LD_LIBRARY_PATH
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

