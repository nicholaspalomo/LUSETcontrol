/**
 * @file node.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the /IndelUpdate node. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "IndelUpdate.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "IndelUpdate"); ///< Must call ros::init() before using any other part of the ROS system

    ros::NodeHandle handle; ///< Instantiate a ROS node handle

    ros::Rate loop_rate(10); ///< Set the loop_rate for processing the callbacks

    indelupdatepubnamespace::IndelUpdatePub indel_update_pub_obj(handle); ///< Instantiate IndelUpdatePub object

    while(ros::ok()){ ///< Infinite loop until the user shuts down the rosmaster with Ctrl + C
        indel_update_pub_obj.indelUpdatePublishMsg(); ///< Call functions to query data from low-level controller and to publish to /IndelUpdate topic
        ros::spinOnce(); ///< ros::spinOnce() processes our callbacks for a single thread; not necessary in this node since there are no subscriber callbacks but added in case functionality added in the future (e.g. sending data from other ROS topics to low-level controller).
        loop_rate.sleep(); ///< Sleep for the remainder of the loop once all callbacks have been processed.
    }

    return 0;
}