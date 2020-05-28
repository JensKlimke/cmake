//
// Copyright (c) 2019 Jens Klimke <jens.klimke@rwth-aachen.de>. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Created by Jens Klimke on 2019-04-25.
//

#include <iostream>
#include <example.pb.h>

class PID_controller {

private:

    simulation::models::PID _data{};
    simulation::models::PID::Parameters *parameters;

public:

    PID_controller() = default;
    ~PID_controller() = default;

    void create() {

        _data.mutable_parameters()->set_k_p(0.0);

    }


    void step(double simTime, double timeStepSize) {


    }


    void setIDAndName(std::string &&id, std::string &&name) {

        // set name and ID
        _data.set_name(name);
        _data.set_name(id);

    }

    void setParameters(double kP, double kI, double kD) {

        // set parameters
        _data.mutable_parameters()->set_k_p(kP);
        _data.mutable_parameters()->set_k_i(kI);
        _data.mutable_parameters()->set_k_d(kD);

        // overwrite parameters
        parameters->set_k_p(10.0);

        // set parameters
        std::cout << ">" << _data.parameters().k_p() << std::endl;

    }

};
