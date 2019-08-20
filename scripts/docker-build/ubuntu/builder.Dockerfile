FROM ubuntu:18.04

RUN apt update && apt dist-upgrade -y \
    && apt install -y build-essential vim wget m4 automake gfortran libopenmpi-dev

WORKDIR /work
ENV WORKDIR /work
ENV INSTALL_PREFIX /opt/openarray
ENV PATH ${INSTALL_PREFIX}/bin:$PATH

# 编译并安装 PnetCDF
ADD pnetcdf-1.11.2.tar.gz .
RUN cd pnetcdf-1.11.2 \
    && ./configure --prefix=${INSTALL_PREFIX} \
    && make -j$(nproc) \
    && make install \
    && rm -rf /work/pnetcdf-1.11.2*
