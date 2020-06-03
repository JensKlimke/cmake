# cmake
[![Build Status](https://travis-ci.org/JensKlimke/cmake.svg?branch=master)](https://travis-ci.org/JensKlimke/cmake)

This my almost empty base cmake project, which I use for starting a new project.

## Installation

For windows (tested with Visual Studio 15 2017):

* Install protobuf and zlib as described [here](https://github.com/protocolbuffers/protobuf/blob/master/cmake/README.md) (chose an <install_path> and remember)
* Set the following options:

        -DDUMMY_BUILD_TESTS=ON
        -Dgtest_force_shared_crt=TRUE
        -DCMAKE_INSTALL_PREFIX=<install_path>

## TODO 
* ~~Create travis.yml~~
* ~~Add protobuf~~
* ~~Add threads~~
* Simulation:
    * Add model functionality
    * Add sim control (loop)
    * Add code guidelines (with respect to multi-threading)
* Add communication layer
    * protobuf + gRPC?
    * json + MQTT?
