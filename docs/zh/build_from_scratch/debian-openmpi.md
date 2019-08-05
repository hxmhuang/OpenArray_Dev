# 在 Debian 环境编译并安装 OpenArray CXX (openmpi)

1. 支持 Debian buster x86_64 及相近版本。
2. openmpi

## 说明

1. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 操作系统

**提示** 为了实验方便，这里我们使用 docker 运行一个 container ，创建纯净的实验环境。你也可以 **跳过此准备步骤** ，在已经安装好的操作系统进行实验。

```shell
docker run -it --name openarray-debian debian:buster bash
```

### 安装基本软件包

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
apt update && apt dist-upgrade -y
apt install -y build-essential vim wget m4 automake gfortran libopenmpi-dev
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
wget https://github.com/hxmhuang/OpenArray/archive/v1.0.0-beta.1.tar.gz -O OpenArray-v1.0.0-beta.1.tar.gz
tar xf OpenArray-v1.0.0-beta.1.tar.gz
cd OpenArray-1.0.0-beta.1/
LIBS=-lmpi_cxx PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install
make
make install
```

测试：

```shell
./manual_main
```

