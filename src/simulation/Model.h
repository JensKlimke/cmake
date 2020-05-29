// Copyright (c) 2020 Jens Klimke <jens.klimke@rwth-aachen.de>. All rights reserved.
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
// Created by Jens Klimke on 29.05.2020.
//


#ifndef DUMMYPROJECT_MODEL_H
#define DUMMYPROJECT_MODEL_H

#include <cmath>
#include <string>
#include <simulation.pb.h>

namespace sim {


    /**
     * An interface for the implementation of simulation models
     * @tparam proto Protobuf data type for the data container
     */
    template<typename proto>
    class Model {

    public:

        //!< Time tracking origin
        enum class TimeTrackingOriginMode {FROM_START, FROM_LAST_STEP};


    private:

         simulation::Model _model{}; //!< The protobuf meta data container of the model

        bool _isActive = false;               //!< Flag indicating whether the model is active
        double _startExecTime = 0.0;          //!< The first sim time point to execute the model
        double _timeStepSize = 1.0;           //!< Execution time step size
        double _lastExecTime = INFINITY;      //!< The next time to execute the model
        double _originTime = 0.0;             //!< The time from which the time tracking shall be done
        unsigned int _noOfExecutionSteps = 0; //!< Execution step counter from the last reset
        TimeTrackingOriginMode _timeTrackingOriginMode = TimeTrackingOriginMode::FROM_LAST_STEP; //!< Time tracking mode

        constexpr static const double EPS_TIME_STEP_SIZE = 1e-9; //!< The minimum time step size

    protected:

        proto _data{}; //!< The protobuf data container of the model


    public:


        /**
         * Constructor
         */
        Model() = default;


        /**
         * Sets the ID and the name of the model
         * @param id ID of the model instance
         * @param name Name of the model instance
         */
        void setIDAndName(std::string &&id, std::string &&name) {

            // set name and ID
            _model.set_name(std::move(name));
            _model.set_name(std::move(id));

        }


        /**
         * @brief Implements the creation routine of the model.
         * In the implementation the model shall be created. This function is executed once after the model is instantiated
         * (by constructor) and registered to the simulation process. When multiple simulation are ran with the same model
         * instance, the creation is not done prior to every simulation (@see initialize(double simTime))
         *
         * Before this process the model was instantiated
         * After that process, the time step size should be set
         *
         * @return Success flag
         */
        virtual bool create() = 0;


        /**
         * @brief Sets the time step size of the model and otionally the first execution time
         *
         * Before this process, the model shall be created (@see create())
         *
         * @param timeStepSize The time step size
         * @param startExecTime The first execution time
         */
        virtual void setTimeStepSize(double timeStepSize, double startExecTime = 0.0) {

            // start time
            this->_startExecTime = startExecTime;

            // time step size
            this->_timeStepSize = timeStepSize;

        }


        /**
         * @brief Initializes the model
         * The initialization process is done before the first step of simulation is executed. However, the process might
         * be called also during simulation, when the model is put into operation dynamically. A model is usually only
         * initialized once per simulation. If several simulation are ran with the same instance of the model, the
         * initialization process is called prior to every simulation.
         *
         * @param simTime The simulation time at which the model is initialized
         *
         * @return Success flag
         */
        virtual bool initialize(double simTime) {

            // reset states
            this->reset();

        }


        /**
         * @brief Function to reset the model
         * The implementation should set the model to a state at which a new calculation interval can be started. Especially
         * the memory should be reset. Parameters usually remain over calculation intervals since they are set after
         * creation.
         */
        virtual void reset() = 0;


        /**
         * @brief Checks if the next simulation step of the model shall be performed in the given simulation time.
         *
         * The functions checks if the step size is reached from the last step and if the simulation time reached the
         * first execution simulation time.
         *
         * @param simTime Actual simulation time
         * @return Flag indicating if the step shall be executed
         */
        virtual bool isStepTime(double simTime) {

            return simTime > this->_startExecTime - EPS_TIME_STEP_SIZE
                   && simTime > _lastExecTime + _timeStepSize - EPS_TIME_STEP_SIZE;

        }


        /**
         * @brief Manages the simulation step of the model.
         *
         * This function checks if the model can be ran in the actual simulation step and calculates the time step size from
         * the last simulation step execution of the model
         *
         * @param simTime The actual simulation time
         *
         * @return
         */
        virtual bool simStep(double simTime) {

            if (isStepTime(simTime)) {

                // execute simulation
                this->step(simTime, simTime - this->_lastExecTime);

                // save time
                this->_lastExecTime = simTime;

            }

        }


        /**
         * @Executes the simulation step of the model
         * This process is called if the step time is reached in the simulation. This process is not called in every
         * simulation step of the underlying simulation process (@see simStep())
         * @param simTime
         * @param timeStepSize
         * @return
         */
        virtual bool step(double simTime, double timeStepSize) = 0;


        /**
         * @brief Activates the model.
         * Attention: the process resets the model.
         *
         * @return Success flag
         */
        bool activate() {

            // reset the model
            this->reset();

            // reset time tracking
            _noOfExecutionSteps = 0;

            // activate
            this->_isActive = false;

        }


        /**
         * @brief Deactivates the model.
         * @return Success flag
         */
        bool deactivate() {

            // deactivate
            this->_isActive = false;

        }


    };

}

#endif //DUMMYPROJECT_MODEL_H
