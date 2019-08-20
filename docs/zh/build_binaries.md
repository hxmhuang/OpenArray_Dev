# 编译二进制发行包

前提：

1. 系统需要安装 `docker`

## Step By Step

```shell
# 1. 下载源码
git clone https://github.com/hxmhuang/OpenArray_Dev.git
# 2. 进入目录
cd OpenArray_Dev/
# 3. 执行 docker 编译指令
# 3.1 编译 ubuntu 环境二进制包, 兼容 Debian
./scripts/build-by-docker.sh ubuntu
# 3.2 编译 centos 环境二进制包, 兼容 RHEL
./scripts/build-by-docker.sh centos
# 3.3 编译 opensuse 环境二进制包
./scripts/build-by-docker.sh opensuse
```

在当前目录生成的 `openarray-{VERSION}-linux-x86_64.tar.bz2` 即为二进制发行包。
