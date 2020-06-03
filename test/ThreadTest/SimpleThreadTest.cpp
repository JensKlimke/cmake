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
// Created by Jens Klimke on 2020-06-02.
// Original source: https://www.geeksforgeeks.org/multithreading-in-cpp/
//

#include <gtest/gtest.h>
#include <thread>
#include <cmath>


double an_intense_calculation(double d) {

    unsigned long n = 10000000;

    double a = 0.0;
    for(unsigned long i = 0; i < n; ++i)
        a += (sin(d * (double) i) - cos(d * (double) i)) / (double) n;

    return a;

}


// A dummy function
void foo(int Z)
{

    for (int i = 0; i < Z; i++) {

        auto res = an_intense_calculation(1.0 * i);
        std::cout << "Thread using function pointer as callable. " << res << std::endl;

    }

}

// A callable object
class thread_obj {

public:

    void operator()(int x)
    {

        for (int i = 0; i < x; i++) {

            auto res = an_intense_calculation(1.0 * i);
            std::cout << "Thread using function object as  callable. " << res << std::endl;

        }

    }

};

TEST(SimpleThreadTest, Join) {

    // Define a Lambda Expression
    auto f = [](int x) {

        for (int i = 0; i < x; i++) {

            auto res = an_intense_calculation(1.0 * i);
            std::cout << "Thread using lambda expression as callable. " << res << std::endl;

        }

    };

    // This thread is launched by using
    // function pointer as callable
    std::thread th1(foo, 3);

    // This thread is launched by using
    // function object as callable
    std::thread th2(thread_obj(), 3);

    // This thread is launched by using
    // lambda expression as callable
    std::thread th3(f, 3);


    // Wait for thread t1 to finish
    th1.join();

    // Wait for thread t2 to finish
    th2.join();

    // Wait for thread t3 to finish
    th3.join();

}
