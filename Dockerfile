FROM kazeorg/kazesl:latest

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
     libtool \
     libssl-dev \
	 lcov \
	 cmake && \
     apt-get clean \
     libgflags-dev \
     liblz4-dev \
    && rm -rf /var/lib/apt/lists/*

ENV LD_LIBRARY_PATH=/libs
ENV CPLUS_INCLUDE_PATH=/libs/include
ENV CC=/usr/bin/gcc-7
ENV CXX=/usr/bin/g++-7


WORKDIR /app

CMD ["/bin/bash"]
