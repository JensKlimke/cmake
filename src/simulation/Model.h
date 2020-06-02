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

        //!< Enum to define the model state
        enum class ModelState {INSTANTIATED, CREATED, INITIALIZED, RUNNING, PAUSED, DESTROYED};

    protected:

        bool _isActive = false;                //!< Flag indicating whether the model is active
        double _startExecTime{};               //!< The first sim time point to execute the model
        double _timeStepSize{};                //!< Execution time step size
        double _lastExecTime{};                //!< The next time to execute the model
        double _originTime{};                  //!< The time from which the time tracking shall be done
        unsigned long _noOfExecutionSteps = 0; //!< Execution step counter from the last reset

        TimeTrackingOriginMode _timeTrackingOriginMode
            = TimeTrackingOriginMode::FROM_LAST_STEP; //!< Time tracking mode
        ModelState _state = ModelState::INSTANTIATED; //!< Model state

        constexpr static const double EPS_TIME_STEP_SIZE = 1e-9; //!< The minimum time step size

        simulation::Model _meta{}; //!< The protobuf meta data container of the model
        proto _data{};             //!< The protobuf data container of the model


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
            _meta.set_name(std::move(name));
            _meta.set_id(std::move(id));

        }


        /**
         * Returns the ID of the model
         * @return ID
         */
        const std::string &getID() const {

            return _meta.id();

        }


        /**
         * Returns the name of the model
         * @return Name
         */
        const std::string &getName() const {

            return _meta.name();

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
        virtual bool create() {

            // check state
            if(_state != ModelState::INSTANTIATED)
                throw std::runtime_error("Model was created already.");

            // set state
            _state = ModelState::CREATED;

            // defaults
            _startExecTime = 0.0;
            _timeStepSize = 1.0;

            // success
            return true;

        }


        /**
         * @brief Sets the time tracking origin mode
         *
         * * FROM_START:     The absolute time is tracked from the start of the model. This mode should be used,
         *                   when the exact step count is important or when real-time, pseudo-real-time or accelerated
         *                   real-time simulations are performed. Delayed steps are caught up step by step until the
         *                   times are synchronized. This mode is also called asynchronous mode, because the model does
         *                   not run synchronized to the time server steps.
         * * FROM_LAST_STEP: The relative time is tracked from the last execution step. This mode should be used, when
         *                   the time steps shall be as equal as possible or the time tracking is very exact.
         *                   However, the error between actual simulation time and time step size times no of steps
         *                   might increase due to accumulated error. The mode is also called synchronized mode, because
         *                   the model runs synchronized to the time server steps.
         *
         *
         * @param mode The time tracking origin mode
         */
        virtual void setTimeTrackingOriginMode(TimeTrackingOriginMode mode) {

            // check state
            if(_state != ModelState::CREATED)
                throw std::runtime_error("");

            // set mode
            _timeTrackingOriginMode = mode;

        }


        /**
         * @brief Sets the start execution time.
         *
         * Use this method, if you don't want to start the model to be executed from the very beginning. This setting
         * can be changed before each initialization. The model must be created
         *
         * @param startExecTime Start execution time
         */
        virtual void setStartExecutionTime(double startExecTime) {

            // check state
            if(_state != ModelState::CREATED)
                throw std::runtime_error("Setup only possible before initialization (state = CREATED).");

            // start time
            this->_startExecTime = startExecTime;

        }


        /**
         * @brief Sets the time step size of the model and optionally the first execution time
         *
         * Before this process, the model shall be created (@see create())
         *
         * @param timeStepSize The time step size
         */
        virtual void setTimeStepSize(double timeStepSize) {

            // check state
            if(_state != ModelState::CREATED)
                throw std::runtime_error("The model must be created first.");

            // time step size
            this->_timeStepSize = timeStepSize;

            // set active
            this->_isActive = true;

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

            // check state
            if(_state == ModelState::INSTANTIATED)
                throw std::runtime_error("Model must be created before initialization.");
            else if(_state != ModelState::CREATED)
                throw std::runtime_error("Model must be terminated before initialization.");

            // set state
            _state = ModelState::INITIALIZED;

            // reset states
            this->reset();

            // set last execution time to minus inf
            _lastExecTime = -1.0 * INFINITY;

            // standard
            return true;

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
        virtual bool isStepTime(double simTime) const {

            // dependent on mode
            bool time2run = _timeTrackingOriginMode == TimeTrackingOriginMode::FROM_LAST_STEP
                    ? simTime > _lastExecTime + _timeStepSize - EPS_TIME_STEP_SIZE
                    : simTime > _startExecTime + _noOfExecutionSteps * _timeStepSize - EPS_TIME_STEP_SIZE;

            // check
            return (simTime > _startExecTime - EPS_TIME_STEP_SIZE) && time2run;

        }


        /**
         * Returns true when the model is active
         * @return Active flag
         */
        virtual bool isActive() const {

            return _isActive;

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

            // check state
            if(_state != ModelState::INITIALIZED && _state != ModelState::RUNNING)
                throw std::runtime_error("Model must be initialized before execution.");

            // set state
            _state = ModelState::RUNNING;

            if (isStepTime(simTime) && isActive()) {

                // execute simulation
                this->_noOfExecutionSteps++;
                this->step(simTime, simTime - this->_lastExecTime);

                // save time
                this->_lastExecTime = simTime;

                // step performed
                return true;

            }

            // step not performed
            return false;

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
        void activate() {

            // reset the model
            this->reset();

            // reset time tracking
            _noOfExecutionSteps = 0;

            // activate
            _isActive = true;

        }


        /**
         * @brief Deactivates the model.
         * @return Success flag
         */
        void deactivate() {

            // deactivate
            _isActive = false;

        }


        /**
         * @brief This model terminates the model for the actual simulation.
         *
         * @param simTime Simulation time at termination
         * @return Success flag
         */
        virtual bool terminate(double simTime) {

            // check state
            if(_state != ModelState::INITIALIZED && _state != ModelState::RUNNING)
                throw std::runtime_error("Model cannot be terminated, when not initialized.");

            // set state
            _state = ModelState::CREATED;

            // success
            return true;

        }


        /**
         * @brief This method destroys the model.
         *
         * After conduction the destruction, the model cannot be used in a simulation, even not, when create process is
         * started. The model is removed from all indexes. However the data stored in the model instance is still
         * available and should be accessible.
         *
         * @return Success flag
         */
        virtual bool destroy() {

            // check state
            if(_state != ModelState::CREATED)
                throw std::runtime_error("Model can only be destroyed when terminated or created.");

            // set state
            _state = ModelState::DESTROYED;

            // success
            return true;

        }


    };

}

#endif //DUMMYPROJECT_MODEL_H
