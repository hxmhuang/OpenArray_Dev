# 在 MacOS 环境编译并安装 OpenArray CXX (openmpi)

1. 支持 Fedora 22 x86_64 及以上版本。
2. openmpi 4.0.1

## 说明

1. 默认自定义的安装目录为 `${HOME}/install` ，可以修改为自定义的名称。

## 准备

### 安装基本软件包

编译过程依赖一些基础软件包，如果系统已经存在请忽略。

```shell
brew install openmpi
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
git clone https://github.com/hxmhuang/OpenArray_CXX.git
cd OpenArray_CXX/
PNETCDF_DIR=${HOME}/install ./configure --prefix=${HOME}/install
make
make install
```

测试：

```shell
./manual_main
```

