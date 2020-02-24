/**
 * @file node.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the /LusetControl node. This node subscribes to messages coming from /LusetState and the contact sensors (*sensor_state) and publishes to the /cylinderPiston*0_position_controller/command and /LusetContacts topics. This node is responsible for computing control inputs (axis/valve displacements) to send to the low-level control as well as for preemptively detecting (and notifying) the user of any immenent collisions between LUSET's actuators and/or yokes. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "LusetControl.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "LusetControl"); ///< Must call ros::init() before using any other part of the ROS system

    ros::NodeHandle handle; ///< Instantiate a ROS node handle

    ros::AsyncSpinner async_global_spinner(0); ///< Instantiate an AsyncSpinner object for the global callback queue (where we process the callback for /LusetState messages)

    ros::Rate loop_rate(10); ///< Set the loop_rate for processing the callbacks
    
    lusetcontrolnamespace::LusetCollision luset_collision_obj(handle); ///< Instantiate LusetCollision object
    
    while(ros::ok()){ ///< Infinite loop until the user shuts down the rosmaster with Ctrl + C
        luset_collision_obj.spinMultithreadSpinners(); ///< Spin multithreaded spinners
        async_global_spinner.start(); ///< Spin the multithread spinner for the global callback queue
        ros::getGlobalCallbackQueue()->callOne(); ///< Only process one callback from the global callback queue
        loop_rate.sleep(); ///< Sleep for the remainder of the loop once all callbacks have been processed.
    }

    return 0;
}