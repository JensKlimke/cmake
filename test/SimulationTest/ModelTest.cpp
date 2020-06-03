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

#include <gtest/gtest.h>
#include <simulation/Model.h>


class TestModel : public sim::Model<double>, public ::testing::Test {

protected:

    bool _reset = false;

    void SetUp() override {

    }

public:

    bool create() override {

        // run creation
        sim::Model<double>::create();

        // set meta data
        this->setIDAndName("model-1", "Model1");

        return true;

    }

    void reset() override {

        // set reset flag
        _reset = true;

    }

    bool step(double simTime, double timeStepSize) override {

        // unset reset flag
        _reset = false;

        return true;

    }


};


TEST_F(TestModel, Process) {

    // check error
    EXPECT_THROW(this->setStartExecutionTime(0.0), std::runtime_error);
    EXPECT_THROW(this->setTimeStepSize(0.1), std::runtime_error);
    EXPECT_THROW(this->initialize(0.0), std::runtime_error);
    EXPECT_THROW(this->simStep(0.0), std::runtime_error);
    EXPECT_THROW(this->terminate(0.0), std::runtime_error);
    EXPECT_THROW(this->destroy(), std::runtime_error);

    // 1. creation
    EXPECT_TRUE(this->create());

    // check data
    EXPECT_EQ(sim::Model<double>::ModelState::CREATED, this->_state);
    EXPECT_EQ(std::string("model-1"), this->getID());
    EXPECT_EQ(std::string("Model1"), this->getName());

    // 2. configuration
    this->setTimeTrackingOriginMode(sim::Model<double>::TimeTrackingOriginMode::FROM_LAST_STEP);
    this->setTimeStepSize(0.1);
    this->setStartExecutionTime(10.0);

    // check data
    EXPECT_DOUBLE_EQ(10.0, this->_startExecTime);
    EXPECT_DOUBLE_EQ( 0.1, this->_timeStepSize);
    EXPECT_TRUE(this->isActive());

    // 3. initialization
    EXPECT_TRUE(this->initialize(0.0));

    // check data
    EXPECT_EQ(sim::Model<double>::ModelState::INITIALIZED, this->_state);
    EXPECT_TRUE(this->_reset);

    // check errors
    EXPECT_THROW(this->initialize(0.0), std::runtime_error);
    EXPECT_THROW(this->create(), std::runtime_error);

    // 4. loop
    unsigned long steps = 0;
    double time = 0.0;
    for(unsigned int i = 0; i < 10000; ++i) {

        // time
        time = 0.01 * i + (i % 2 ? 1e-12 : -1e-12);

        // deactivate
        if(i == 5000)
            this->deactivate();
        else if(i == 6000) {
            this->activate();
            EXPECT_TRUE(this->_reset);
        }

        // 4.1 step
        auto done = this->simStep(0.01 * i - 1e-12);
        auto step = fabs(10.0 * time - std::round(0.1 * i)) < 1e-6;

        // check done flag
        if(i >= 1000 && (i < 5000 || i >= 6000) && step)
            EXPECT_TRUE(done);
        else
            EXPECT_FALSE(done);

        // check steps
        if(i < 1000) {

            // check data
            EXPECT_TRUE(this->_reset);

        } else if(i >= 1000 && i < 5000 && done) {

            // check data
            EXPECT_EQ((i - 1000) / 10 + 1, this->_noOfExecutionSteps);
            EXPECT_FALSE(this->_reset);

        } else if(i >= 5000 && i < 6000) {

            // check data
            EXPECT_EQ(400, this->_noOfExecutionSteps);
            EXPECT_FALSE(this->_reset);

        } else if(i >= 6000) {

            // check data
            EXPECT_EQ((i - 6000) / 10 + 1, this->_noOfExecutionSteps);
            EXPECT_FALSE(this->_reset);

        }

    }

    // 5. terminate
    this->terminate(10.0);

    // 6. destroy
    this->destroy();
    

}