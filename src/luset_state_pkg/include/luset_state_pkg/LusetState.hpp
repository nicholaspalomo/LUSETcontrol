/**
 * @file LusetState.hpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the header file for the LusetState and LusetStatePub classes. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef LUSET_STATE_PKG_LUSET_STATE_H_
#define LUSET_STATE_PKG_LUSET_STATE_H_

#include<stdio.h> ///< Standard input-output header
#include<string.h> ///< Perform string manipulation operations like strlen and strcpy
#include<stdlib.h> ///< Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc().
#include<math.h> ///< Perform mathematical operations like sqrt() and pow(). To obtain the square root and the power of a number respectively.
#include<ctype.h> ///< Perform character type functions like isaplha() and isdigit(). To find whether the given character is an alphabet or a digit respectively.
#include<time.h> ///< Perform functions related to date and time like setdate() and getdate(). To modify the system date and get the CPU time respectively.
#include <vector> ///< To be able to use vectors in C++
#include<iostream> ///< Used as a stream of Input and Output.

// #include<Eigen/Dense> ///< Include Eigen for linear algebra computations

#include "ros/ros.h" ///< For access to ROS-specific functions

#include "luset_state_pkg/ActuatorOrientation.h" ///< Custom message header file containing orientation vector for a cylinder
#include "luset_state_pkg/DisplacementForceStruct.h" ///< Custom message header containing translation, rotation, force, and moment measurements for each yoke
#include "luset_state_pkg/LusetState.h" ///< Custom message header containing the definition of the LusetState structure
#include "indel_update_pkg/LusetStateArray.h" ///< Custom message header for the array of floats received from the low-level controller

namespace lusetstatenamespace{
    /**
     * @class LusetState
     * @brief This class parses the LusetStateArray obtained by subscribing to the /IndelUpdate topic and publishes a message structure containing all the sensor data acquired from the low-level controller. 
     */
    class LusetState{
        public:

        /**
         * @brief Construct a new Luset State object
         */
        LusetState();

        /**
         * @brief This function parses the LusetStateArray message obtained from the /IndelUpdate topic
         * @param[in]   msg     const indel_update_pkg::LusetStateArray::ConstPtr& Reference to a LusetStateArray message pointer
         * @return  void    No output
         */
        void update(const indel_update_pkg::LusetStateArray::ConstPtr& msg);

        std::vector<double> CylinderPosition{std::vector<double>(100,0.0)}; ///< Cylinder stroke (100 x 1 vector)
        std::vector<double> LoadPinForces{std::vector<double>(100,0.0)}; ///< Load pin forces (100 x 1 vector)
        std::vector<double> PressureA{std::vector<double>(20,0.0)}; ///< Valve pressure A (20 x 1 vector)
        std::vector<double> PressureB{std::vector<double>(20,0.0)}; ///< Valve pressure B (20 x 1 vector)
        std::vector<double> AngleXZ{std::vector<double>(20,0.0)}; ///< Yoke angle w.r.t. global X-Z plane (20 x 1 vector)
        std::vector<double> AngleYZ{std::vector<double>(20,0.0)}; ///< Yoke angle w.r.t. global Y-Z plane (20 x 1 vector)
        std::vector<std::vector<double>> CylinderDirection; ///< Cylinder directions (100 x 3 vectors)
        std::vector<double> AxisPositionIst{std::vector<double>(20,0.0)}; ///< Axis/valve current position value (20 x 1 vector)
        std::vector<double> AxisPositionSetPoint{std::vector<double>(20,0.0)}; ///< Axis/valve set point position value (20 x 1 vector)
        std::vector<double> AxisForceIst{std::vector<double>(20,0.0)}; ///< Axis/valve current force value (20 x 1 vector)
        std::vector<double> AxisForceSetPoint{std::vector<double>(20,0.0)}; ///< Axis/valve set point force value (20 x 1 vector)
        std::vector<double> VCSetPoint{std::vector<double>(20,0.0)}; ///< VC set point value (20 x 1 vector)
        std::vector<double> VCCurrentIstValue{std::vector<double>(20,0.0)}; ///< VC current value (20 x 1 vector)
        std::vector<double> ADC_From328To335{std::vector<double>(8,0.0)}; ///< ADC from 328 to 335 value (8 x 1 vector)

        /**
         * The displacement-force struct contains the linear position, Euler angle, force, and moment values for a _single_ yoke.
         */
        struct DisplacementForce {
            double TX;
            double TY;
            double TZ;
            double RX;
            double RY;
            double RZ;
            double FX;
            double FY;
            double FZ;
            double MX;
            double MY;
            double MZ;
        }; // DisplacementForce

        std::vector<DisplacementForce> BY = {DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce()}; ///< Declare for the bottom side of LUSET a vector of 5 DisplacementForce structs (one corresponding to each yoke)
        std::vector<DisplacementForce> NY = {DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce()}; ///< Declare for the north side of LUSET a vector of 5 DisplacementForce structs (one corresponding to each yoke)
        std::vector<DisplacementForce> TY = {DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce()}; ///< Declare for the top side of LUSET a vector of 5 DisplacementForce structs (one corresponding to each yoke)
        std::vector<DisplacementForce> SY = {DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce(), DisplacementForce()}; ///< Declare for the south side of LUSET a vector of 5 DisplacementForce structs (one corresponding to each yoke)
    };
}

namespace lusetstatepubsubnamespace{
    class LusetStatePubSub{
        public:
            /**
             * @brief Construct a new Luset State Pub Sub object
             * @param[in]   handle  ros::NodeHandle& Reference to the handle for the /LusetState node
             */
            LusetStatePubSub(ros::NodeHandle& handle);

        private:

            ros::NodeHandle* node_handle; ///< Pointer to the ROS node handle for /LusetState
            ros::Publisher pub; ///< ROS publisher object for publishing to the /LusetState topic
            ros::Subscriber sub; ///< ROS subscriber object for subscribing to the /IndelUpdate topic

            /**
             * @brief Callback function for the subscriber object. Parces LusetStateArray from /IndelUpdate topic and publishes the resulting structure to the /LusetState topic
             * @param[in]   msgSub     const indel_update_pkg::LusetStateArray::ConstPtr& Reference to a LusetStateArray message pointer
             * @return  void    No output
             */
            void lusetStateArrayParsingCallback(const indel_update_pkg::LusetStateArray::ConstPtr& msgSub);
    };
}

#endif // LUSET_STATE_PKG_LUSET_STATE_H_