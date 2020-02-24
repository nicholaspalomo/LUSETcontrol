/**
 * @file IndelUpdate.hpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the header file for the IndelUpdate class. This class handles communication with the low-level controller by calling functions from the Indel inco_32.so shared library which returns an array of the sensor measurments. This class also publishes the data to the ROS topic, /IndelUpdate. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef INDEL_UPDATE_PKG_INDEL_UPDATE_H_
#define INDEL_UPDATE_PKG_INDEL_UPDATE_H_

#include<stdio.h> ///< Standard input-output header
#include<string.h> ///< Perform string manipulation operations like strlen and strcpy
#include<stdlib.h> ///< Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc().
#include<math.h> ///< Perform mathematical operations like sqrt() and pow(). To obtain the square root and the power of a number respectively.
#include<ctype.h> ///< Perform character type functions like isaplha() and isdigit(). To find whether the given character is an alphabet or a digit respectively.
#include<time.h> ///< Perform functions related to date and time like setdate() and getdate(). To modify the system date and get the CPU time respectively.
#include<iostream> ///< Used as a stream of Input and Output.
// #include<Eigen/Dense> ///< Recommended to install Eigen in root of catkin workspace
#include <dlfcn.h> ///< Dynamic linking function header
#include "inco_32/inco_32.h" ///< Header for Indel inco_32 shared library
#include "ros/ros.h" ///< ROS API header
#include "indel_update_pkg/LusetStateArray.h" ///< Custom message header file for defining message type for /IndelUpdate

namespace indelupdatenamespace{
    
    /**
     * @class IndelUpdate
     * @brief This class provides the interface between the low-level controller and the ROS control system.
     */
    class IndelUpdate{
        public:

        /**
         * @brief This function calls the function from the inco_32.so library that is linked to the indel_update_pkg_node executable.
         * @param[in]   void    Called without inputs
         * @return  void    No output
         * @param[in,out]   N/A   No input-output variables
         */
        void update(void);

        std::vector<double> ArrayValue{std::vector<double>(1000,0)}; ///< Member variable that holds a 1 x 1000 vector of the sensor data coming from the low-level controller. Published as an ArrayValue message to the /IndelUpdate topic

    private:

        double value; ///< Member variable populated with the address of the data from the low-level controller
        const char device[10] = "ETH_Luset"; ///< Name of the target; passed to the low-level controller when inco_32.so function called
        const char AddressString[44] = "PRJ00202.LusetDataStorage.FullArray!Address"; ///< Address string to where data from low-level controller is stored
    }; // end of class IndelUpdate
}

namespace indelupdatepubnamespace{
    /**
     * @class IndelUpdatePub
     * @brief This class handles publishing to the /IndelUpdate topic data acquired from the low-level controller
     */
    class IndelUpdatePub{
        public:

            /**
             * @brief Construct a new Indel Update Pub object. Initializes the publisher on /IndelUpdate topic.
             * @param[in]   handle  ros::NodeHandle& Reference to a ROS node handle
             * @return  object of IndelUpdatePub class
             */
            IndelUpdatePub(ros::NodeHandle& handle);

            /**
             * @brief Handles publishing on /IndelUpdate topic the data from the low-level controller
             * @param[in]   void    Called without inputs
             * @return  void    No output
             */
            void indelUpdatePublishMsg(void);

        private:

            ros::NodeHandle* node_handle; ///< Container for ROS node handle instantiated in ROS node for this package
            ros::Publisher pub; ///< Publisher object for /IndelUpdate topic
    };
}

#endif // INDEL_UPDATE_PKG_INDEL_UPDATE_H_