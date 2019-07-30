# 准备 openSUSE 编译环境

支持 openSUSE Leap 15.1 x86_64 及相近版本。

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
# zypper in -y gcc8 gcc8-c++ gcc8-fortran
zypper in -y tar gzip bzip2 git wget vim make gcc gcc-c++ gcc-fortran m4 openmpi3 openmpi3-devel 
# automake 依赖等待删除
zypper in -y automake
# m4 utility program is required by PnetCDF
# parallel-netcdf-openmpi parallel-netcdf-openmpi-devel

export PATH=/usr/lib64/mpi/gcc/openmpi3/bin:$PATH
export LD_LIBRARY_PATH=/usr/lib64/mpi/gcc/openmpi/lib64/:$LD_LIBRARY_PATH
```

## mpich

```shell
zypper update
zypper in -y mpich mpich-devel
export PATH=/usr/lib64/mpi/gcc/mpich/bin/:$PATH
export LD_LIBRARY_PATH=/usr/lib64/mpi/gcc/mpich/lib64/:$LD_LIBRARY_PATH
```

或者

```shell
echo "/usr/lib64/mpi/gcc/mpich/lib64/" >> /etc/ld.so.conf
```

或者

```shell
# echo "/usr/lib64/mpi/gcc/openmpi3/lib64/" >> /etc/ld.so.conf
```

## OpenAPI

配置 `PATH` 和 `LD_LIBRARY_PATH` 环境变量，你可以添加到 `~/.bashrc` 文件中，以免每次都需要手动执行命令以生效该配置：

```shell
# 使用新的 GCC
export PATH=~/install/bin:$PATH
# 添加链接库
# export LD_LIBRARY_PATH=$HOME/install/lib64:$LD_LIBRARY_PATH
```

### 编译并安装 Open MPI

```shell
cd
wget https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.bz2
tar xf openmpi-4.0.1.tar.bz2
cd openmpi-4.0.1
./configure --prefix=${HOME}/install
make -j$(nproc)
make install
```

**注意** 需要修改 `${HOME}/install/share/openmpi/mpif90-wrapper-data.txt` 里的 compiler 为 `gfortran-8`

### 编译并安装 PnetCDF

**说明** pnetcdf 安装目录为 `${HOME}/install` , 后面编译 OpenArray_CXX 需要指定该目录。

```shell
cd
wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz
tar xf pnetcdf-1.11.2.tar.gz
cd pnetcdf-1.11.2
./configure --prefix=${HOME}/install --with-mpi=/usr/lib64/mpi/gcc/openmpi3
make -j$(nproc)
make install
```

## OpenArray CXX

## 准备

下载最新源码：

```shell
cd
git clone https://github.com/hxmhuang/OpenArray_CXX.git
cd OpenArray_CXX/
PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install --with-mpi=/usr/lib64/mpi/gcc/openmpi3
make -j$(nproc)
```
