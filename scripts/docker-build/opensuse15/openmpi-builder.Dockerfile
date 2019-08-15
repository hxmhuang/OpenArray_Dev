FROM opensuse/leap:15.1

WORKDIR /work
ENV WORKDIR /work
ENV INSTALL_PREFIX /opt/openarray
ENV PATH /usr/lib64/mpi/gcc/openmpi3/bin:${INSTALL_PREFIX}/bin:$PATH
ENV LD_LIBRARY_PATH=/usr/lib64/mpi/gcc/openmpi3/lib64/:$LD_LIBRARY_PATH

RUN zypper --non-interactive --no-gpg-checks  ref
RUN zypper in -y tar gzip bzip2 wget make gcc gcc-c++ gcc-fortran m4 openmpi3 openmpi3-devel automake

# 编译并安装 PnetCDF
RUN cd ${WORKDIR} \
    && wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz \
    && tar xf pnetcdf-1.11.2.tar.gz \
    && cd ${WORKDIR}/pnetcdf-1.11.2 \
    && ./configure --prefix=${INSTALL_PREFIX} \
    && make -j$(nproc) \
    && make install \
    && rm -rf ${WORKDIR}/pnetcdf-1.11.2*
