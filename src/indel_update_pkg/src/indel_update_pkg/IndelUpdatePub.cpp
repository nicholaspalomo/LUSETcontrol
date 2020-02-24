/**
 * @file IndelUpdatePub.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the IndelUpdatePub class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "IndelUpdate.hpp"

indelupdatepubnamespace::IndelUpdatePub::IndelUpdatePub(ros::NodeHandle& handle) :
node_handle(&handle),
pub(this->node_handle->advertise<indel_update_pkg::LusetStateArray>("IndelUpdate", 10)) ///< Initialize a publisher on the /IndelUpdate topic
{
}

void indelupdatepubnamespace::IndelUpdatePub::indelUpdatePublishMsg(void)
{
    indelupdatenamespace::IndelUpdate indel_update_obj; ///< Instantiate an IndelUpdate object

    indel_update_obj.update(); ///< Update ArrayValue[] member with data from low-level controller

    indel_update_pkg::LusetStateArray msgPub; ///< Create a LusetStateArray message object

    for(int i = 0; i < 1000; i++){
        msgPub.ArrayValue.at(i) = indel_update_obj.ArrayValue.at(i); ///< Copy the ArrayValue[] field of indel_update_obj in to msgPub.ArrayValue[]
    }

    this->pub.publish(msgPub); ///< Publish the message
}