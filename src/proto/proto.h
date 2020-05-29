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

    typedef simulation::models::PID::Parameters _proto_param;

    double kP;
    double kI;
    double kD;

    double xInt;
    double x0;

    double x;
    double y;

    bool resetFlag;

    constexpr static const double EPS_TIME_STEP_SIZE = 1e-9;

public:

    PID_controller() = default;
    ~PID_controller() = default;

    void create() {

        // set parameters
        this->setParameters(0.0, 0.0, 0.0);

    }

    void reset() {

        xInt = 0.0;
        x0 = 0.0;

        resetFlag = true;

    }



    void setInput(double err, bool reset = false) {

        this->x = err;
        this->resetFlag = reset;

    }


    void step(double simTime, double timeStepSize) {

        // no derivation calculation
        bool r = resetFlag || (timeStepSize <= EPS_TIME_STEP_SIZE);

        // parameters and inputs
        xInt += x * timeStepSize;
        double dx = r ? 0.0 : (x - x0) / timeStepSize;

        // calculation
        this->y = kP * x + kI * xInt + kD * x0;

        // set memory
        x0 = x;
        resetFlag = false;

    }

    void setParameters(double P, double I, double D) {

        // set parameters
        this->kP = P;
        this->kI = I;
        this->kD = D;
    }

};
