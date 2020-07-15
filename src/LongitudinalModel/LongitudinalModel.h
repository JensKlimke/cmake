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


#ifndef DUMMYPROJECT_LONGITUDINALMODEL_H
#define DUMMYPROJECT_LONGITUDINALMODEL_H

#include <algorithm>


namespace models {

    struct State {
        double a;
        double v;
        double s;
    };


    class LongitudinalModel {

    protected:

        // system parameters
        double mass = 1300.0;
        double maxTorque = 5000.0;
        double airDragParam = 0.6;
        double rhoAir = 1.2041;

        // system state
        State state;


    public:

        LongitudinalModel() = default;

        virtual ~LongitudinalModel() = default;

        void modelStep(double input, double delta_t) {

            double torque = input * maxTorque;
            double airDrag = 0.5 * rhoAir * airDragParam * state.v * state.v;
            double driveForce = 4.0 * torque / 0.3;

            // calculate dynamics
            state.a = (driveForce - airDrag) / mass;
            double ds = std::max(0.0, 0.5 * state.a * delta_t + state.v * delta_t);

            // update system
            state.s += ds;
            state.v += state.a * delta_t;
            state.v = std::max(0.0, state.v);

        }

        State getState() const {

            return state;

        }

    };

}


#endif //DUMMYPROJECT_LONGITUDINALMODEL_H
