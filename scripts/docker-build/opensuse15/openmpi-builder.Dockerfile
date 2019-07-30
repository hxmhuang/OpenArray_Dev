FROM opensuse/leap:15.1 AS builder

WORKDIR /work
ENV WORKDIR /work
ENV INSTALL_PREFIX /opt/openarray
ENV PATH ${INSTALL_PREFIX}/bin:$PATH

RUN zypper --non-interactive --no-gpg-checks  ref
RUN zypper in -y tar gzip bzip2 wget make gcc gcc-c++ gcc-fortran m4

# 编译并安装 Open MPI
RUN cd ${WORKDIR} \
    && wget https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.bz2 \
    && tar xf openmpi-4.0.1.tar.bz2
RUN cd ${WORKDIR}/openmpi-4.0.1 \
    && ./configure --prefix=${INSTALL_PREFIX} \
    && make -j$(nproc) \
    && make install

# 编译并安装 PnetCDF
RUN cd ${WORKDIR} \
    && wget http://cucis.ece.northwestern.edu/projects/PnetCDF/Release/pnetcdf-1.11.2.tar.gz \
    && tar xf pnetcdf-1.11.2.tar.gz
RUN cd ${WORKDIR}/pnetcdf-1.11.2 \
    && ./configure --prefix=${INSTALL_PREFIX} \
    && make -j$(nproc) \
    && make install


FROM opensuse/leap:15.1

WORKDIR /work
ENV WORKDIR /work
ENV INSTALL_PREFIX /opt/openarray
ENV PATH ${INSTALL_PREFIX}/bin:$PATH

RUN zypper --non-interactive --no-gpg-checks  ref
RUN zypper in -y tar gzip bzip2 git wget vim make gcc gcc-c++ gcc-fortran

COPY --from=builder ${INSTALL_PREFIX} ${INSTALL_PREFIX}
