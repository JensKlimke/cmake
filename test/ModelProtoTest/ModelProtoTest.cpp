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

#include <cmath>
#include <gtest/gtest.h>
#include <proto/PID_controller.h>
#include <LongitudinalModel/LongitudinalModel.h>

class ModelProtoTest : public testing::Test, public PID_controller, public models::LongitudinalModel {



};

TEST_F(ModelProtoTest, SaveAndLoadModel) {

    // set model
    PID_controller pid{};

    // create controller
    pid.create();
    pid.setParameters(0.01, 0.001, 0.0);

    // reset
    pid.reset();

    // control variable
    double vDesired = 20.0;

    // run steps
    double dt = 0.01;
    for(unsigned long i = 0; i < 10000; ++i) {

        // set input
        pid.setInput(vDesired - state.v);

        // save model
        if(i == 100)
            pid.save();

        // step
        double t = dt * (double) i;
        pid.step(t, dt);

        // calculate system
        this->modelStep(pid.getOutput(), dt);

    }

    // check
    EXPECT_NEAR(vDesired, state.v, 1e-3);
    EXPECT_NEAR(0.0, state.a, 1e-5);


    // reset model
    this->create();
    this->reset();

    // check
    EXPECT_DOUBLE_EQ(0.0, this->kP);
    EXPECT_DOUBLE_EQ(0.0, this->kI);
    EXPECT_DOUBLE_EQ(0.0, this->kD);
    EXPECT_DOUBLE_EQ(0.0, this->x0);
    EXPECT_DOUBLE_EQ(0.0, this->xInt);
    EXPECT_TRUE(this->resetFlag);


    // load
    this->load();

    // check
    EXPECT_DOUBLE_EQ(0.01,  this->kP);
    EXPECT_DOUBLE_EQ(0.001, this->kI);
    EXPECT_DOUBLE_EQ(0.0,   this->kD);
    EXPECT_NEAR(11.664, this->x0, 1e-3);
    EXPECT_NEAR(15.545, this->xInt, 1e-3);
    EXPECT_FALSE(this->resetFlag);


}