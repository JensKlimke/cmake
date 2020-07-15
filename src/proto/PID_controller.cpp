// Copyright (c) 2020 Jens Klimke.
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
// Created by Jens Klimke on $date.get('yyyy-M-d').
// Contributors:
//

#include <fstream>
#include <proto/Models.pb.h>
#include "PID_controller.h"

typedef simulation::models::PID pid;


void PID_controller::create() {

    // set parameters
    this->setParameters(0.0, 0.0, 0.0);

}


void PID_controller::reset() {

    xInt = 0.0;
    x0 = 0.0;
    resetFlag = true;

}


void PID_controller::setInput(double err, bool reset) {

    // set error
    this->x = err;

    // reset if desired
    if(reset)
        this->reset();

}


void PID_controller::step(double simTime, double timeStepSize) {

    // no derivation calculation
    bool r = resetFlag || (timeStepSize <= EPS_TIME_STEP_SIZE);

    // parameters and inputs
    xInt += x * timeStepSize;
    double dx = r ? 0.0 : (x - x0) / timeStepSize;

    // calculation
    y = kP * x + kI * xInt + kD * dx;

    // set memory
    x0 = x;

    // unset flag
    resetFlag = false;

}


void PID_controller::setParameters(double P, double I, double D) {

    // set parameters
    this->kP = P;
    this->kI = I;
    this->kD = D;
}


double PID_controller::getOutput() const {

    return y;

}


void PID_controller::save() const {

    // data instance
    pid controller;

    // set parameters
    controller.mutable_parameters()->set_k_p(this->kP);
    controller.mutable_parameters()->set_k_i(this->kI);
    controller.mutable_parameters()->set_k_d(this->kD);

    // set state
    controller.mutable_states()->set_x_0(this->x0);
    controller.mutable_states()->set_x_int(this->xInt);
    controller.mutable_states()->set_reset(this->resetFlag);

    // write
    std::fstream fs("pid.bin", std::ios::out);
    controller.SerializeToOstream(&fs);

}


void PID_controller::load() {

    // data instance
    pid controller;

    // read stream
    std::fstream fs("pid.bin", std::ios::in);
    controller.ParseFromIstream(&fs);

    // set parameters
    this->kP = controller.parameters().k_p();
    this->kI = controller.parameters().k_i();
    this->kD = controller.parameters().k_d();

    // set state
    this->x0 = controller.states().x_0();
    this->xInt = controller.states().x_int();
    this->resetFlag = controller.states().reset();

}