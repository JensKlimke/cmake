FROM ubuntu:18.04
MAINTAINER Jens Klimke (jens.klimke@rwth-aachen.de)

# installation
RUN apt-get update && apt-get -y install git g++ make cmake nano
RUN apt-get update && apt-get -y install doxygen graphviz
RUN apt-get update && apt-get -y install autoconf automake libtool curl unzip

# install protobuf
RUN cd /tmp && git clone --recursive https://github.com/protocolbuffers/protobuf.git
RUN cd /tmp/protobuf && ./autogen.sh
RUN cd /tmp/protobuf && ./configure && \
                         make && \
                         make check && \
                         make install && \
                         ldconfig

# install paho mqtt client
RUN apt-get install libssl-dev
RUN cd /tmp && git clone https://github.com/eclipse/paho.mqtt.c.git
RUN cd /tmp/paho.mqtt.c && git checkout v1.3.1 && cmake -Bbuild -H. -DPAHO_WITH_SSL=ON -DPAHO_ENABLE_TESTING=OFF
RUN cd /tmp/paho.mqtt.c && cmake --build build/ --target install && ldconfig

# copy code
COPY . /app

# installation
RUN rm -rf /app/build
RUN cd /app && mkdir build && cd build && cmake -G "Unix Makefiles" \
    -DDUMMY_BUILD_TESTS=ON \
    -DDUMMY_ENABLE_COVERAGE=ON \
    -DDUMMY_CREATE_DOXYGEN_TARGET=ON \
    -DGTEST_BUILD_LIBRARY=ON \
    ..

# make
RUN cd /app/build && make

# documentation
RUN cd /app/build && make test

CMD bash