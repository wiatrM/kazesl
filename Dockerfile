FROM ubuntu:latest

LABEL description="Kaze settlement layer"

RUN apt-get update \
  && apt-get install -y \
     build-essential \
     software-properties-common \
     wget

 #install boost

RUN apt-get purge -qq libboost1.48-dev &&\
    apt-get install -qq libprotobuf-dev protobuf-compiler libboost-all-dev

RUN apt-get update \
  && apt-get install -y \
     git \
     curl \
     make \
     gcc-7 \
     g++-7 \
     automake \
     autoconf \
     autoconf-archive \
     pkg-config \
     libtool \
     libssl-dev \
	   lcov && \
     apt-get clean \
     libgflags-dev \
     liblz4-dev \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO- "https://cmake.org/files/v3.17/cmake-3.17.3-Linux-x86_64.tar.gz" | \
  tar --strip-components=1 -xz -C /usr/local

ENV LD_LIBRARY_PATH=/libs
ENV CPLUS_INCLUDE_PATH=/libs/include
ENV CC=/usr/bin/gcc-7
ENV CXX=/usr/bin/g++-7


WORKDIR /app

CMD ["/bin/bash"]
