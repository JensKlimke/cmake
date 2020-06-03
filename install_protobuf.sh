#!/bin/sh
wget https://github.com/protocolbuffers/protobuf/archive/v3.12.3.tar.gz
tar -xzvf v3.12.3.tar.gz
cd protobuf-3.12.3 && ./autogen.sh && ./configure --prefix=/usr && make && make install