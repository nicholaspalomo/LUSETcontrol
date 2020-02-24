/**
 * @file node.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the /LusetState node. This node subscribes to messages coming from the Indel inco_32.so library (or from a simulation model - not yet implemented). See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "LusetState.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "LusetState"); ///< Must call ros::init() before using any other part of the ROS system

    ros::NodeHandle handle; ///< Instantiate a ROS node handle

    ros::Rate loop_rate(10); ///< Set the loop_rate for processing the callbacks

    lusetstatepubsubnamespace::LusetStatePubSub luset_state_pub_sub_obj(handle); ///< Instantiate LusetStateSubPub object

    while(ros::ok()){ ///< Infinite loop until the user shuts down the rosmaster with Ctrl + C
        ros::spinOnce(); ///< ros::spinOnce() processes our callbacks for a single thread.
        loop_rate.sleep(); ///< Sleep for the remainder of the loop once all callbacks have been processed.
    }

    return 0;
}