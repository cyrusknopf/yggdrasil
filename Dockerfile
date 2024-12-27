FROM ubuntu:22.04

ENV HOME="/home/yggdrasil"
ARG UID=2000
RUN useradd -u $UID --create-home yggdrasil

RUN apt-get update && apt-get install -y cmake git build-essential valgrind

# Install Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/googletest && \
    cd /usr/src/googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /usr/src/googletest

# Install Google Benchmark
WORKDIR /usr/src/benchmark
RUN git clone https://github.com/google/benchmark.git /usr/src/benchmark
RUN cmake -E make_directory "build"
RUN cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
RUN cmake --build "build" --config Release --target install

USER root
WORKDIR /home/yggdrasil
