FROM centos:7

RUN yum -y update \
    && yum install -y tar gzip bzip2 wget vim findutils make automake m4 centos-release-scl
RUN yum install -y devtoolset-8-gcc devtoolset-8-gcc-c++ devtoolset-8-gcc-gfortran \
    && yum install -y openmpi3-devel

WORKDIR /work
ENV WORKDIR /work
ENV INSTALL_PREFIX /opt/openarray
ENV PATH ${INSTALL_PREFIX}/bin:/opt/rh/devtoolset-8/root/bin/:$PATH
ENV LD_LIBRARY_PATH ${INSTALL_PREFIX}/lib64:$LD_LIBRARY_PATH

# 编译并安装 PnetCDF
ADD pnetcdf-1.11.2.tar.gz .
RUN cd pnetcdf-1.11.2 \
    && ./configure --prefix=${INSTALL_PREFIX} --with-mpi=/usr/lib64/openmpi3 \
    && make -j$(nproc) \
    && make install \
    && rm -rf /work/pnetcdf-1.11.2*
