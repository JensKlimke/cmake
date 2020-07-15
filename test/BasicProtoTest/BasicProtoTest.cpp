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
#include <ProtoTest/Example.pb.h>
#include <fstream>


TEST(ProtoTest, SaveAndLoadModel) {

    using namespace std;

    // create model
    test::ex::Example pid{};
    test::ex::Example pidIn{};

    // set params
    pid.mutable_parameters()->set_k_p(1.0);
    pid.mutable_parameters()->set_k_i(0.1);
    pid.mutable_parameters()->set_k_d(0.2);

    {

        // Write the new address book back to disk.
        fstream output("test.bin", ios::out | ios::trunc | ios::binary);
        ASSERT_TRUE(pid.SerializeToOstream(&output));

    }

    {

        // Read the existing address book.
        fstream input("test.bin", ios::in | ios::binary);
        ASSERT_TRUE(input);
        ASSERT_TRUE(pidIn.ParseFromIstream(&input));

    }

    // check content
    EXPECT_DOUBLE_EQ(1.0, pidIn.parameters().k_p());
    EXPECT_DOUBLE_EQ(0.1, pidIn.parameters().k_i());
    EXPECT_DOUBLE_EQ(0.2, pidIn.parameters().k_d());

}