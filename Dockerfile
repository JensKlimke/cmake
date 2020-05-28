FROM ubuntu:18.04
MAINTAINER Jens Klimke (jens.klimke@rwth-aachen.de)

# installation
RUN apt-get update
RUN apt-get -y install autoconf automake libtool curl git g++ make cmake nano unzip
RUN apt-get -y install npm nodejs
RUN apt-get -y install doxygen

# copy code
COPY . /app

# install gtest
RUN cd /app &&

# installation
RUN rm -rf /app/build
RUN cd /app && mkdir build && cd build && cmake -G "Unix Makefiles" -DBUILD_TESTS=ON -DBUILD_WEBSOCKET=OFF \
    -DBUILD_GTEST=ON -DCREATE_INTERFACE_GENERATOR_TARGETS=ON ..

# create targets
RUN cd /app/build && make gen_interface_unit

# make
RUN cd /app/build && make

# documentation
RUN cd /app/build && make test

CMD bash