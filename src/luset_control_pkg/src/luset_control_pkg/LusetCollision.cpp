/**
 * @file LusetCollision.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the LusetCollision class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "LusetControl.hpp"


lusetcontrolnamespace::LusetCollision::LusetCollision(ros::NodeHandle& handle) :
node_handle(&handle),
luset_contact_sub(lusetcontrolnamespace::LusetCollision::populateContactStateSubscribers()),
luset_state_sub(this->node_handle->subscribe("LusetState", 10, &lusetcontrolnamespace::LusetCollision::lusetStateMsgCallback, this)),
luset_contact_pub(this->node_handle->advertise<gazebo_msgs::ContactsState>("LusetContacts", 1000)),
valve_config(lusetcontrolnamespace::LusetCollision::readValveConfig())
{
};

void lusetcontrolnamespace::LusetCollision::lusetContactStateCallback(const gazebo_msgs::ContactsStateConstPtr& msgSub){

    /**
     * @brief Check the contacts message and publish it to the LusetContacts topic if a contact has been detected
     * 
     */
    if(!msgSub->states.empty()){
        this->luset_contact_pub.publish(msgSub);
        /** @todo: make the components in contact change color (red?) when in contact, normal color otherwise */
    }

}

void lusetcontrolnamespace::LusetCollision::lusetStateMsgCallback(const luset_state_pkg::LusetState::ConstPtr& msgSub){

    /**
     * @brief Go through all actuators and assign to them their corresponding stroke value from the CylinderPosition field of the /LusetState message (msgSub)
     * 
     */
    std::string actuator_idx;
    int m = 0;
    for(int i = 0; i < this->sides.size(); i++){
        for(int j = 0; j < this->layer.size(); j++){
            for(int k = 0; k < this->index.size(); k++){
                actuator_idx = this->sides[i] + std::to_string(this->layer[j]) + "0" + std::to_string(this->index[k]); ///< Form a string for the actuator name, e.g. ``S503'' where ``S'' is the south side, ``5'' is the layer, and ``3'' is the index of the actuator
                this->actuator_topic_stroke[actuator_idx].actuator_stroke = msgSub->CylinderPosition[m]; ///< Assign the actuator strokes from the CylinderPosition member of the received /LusetState message to the correct actuator in actuator_topic_stroke[].actuator_stroke
                m++;
            }
        }
    }

    std_msgs::Float64 msgPub; ///< Declare a object of Float64 message type
    std::string actuators;
    for(auto it = this->valve_config.begin(); it != this->valve_config.end(); it++){
        for(int i = 0; i < it->second.size(); i++){
            actuator_idx = it->second[i]; ///< Cast char to string using overloaded ''='' operator
            msgPub.data = this->actuator_topic_stroke[actuator_idx].actuator_stroke; ///< Assign the actuator stroke for the given cyinder to the *.data field of the message to be published on the /LusetContacts topic
            this->actuator_topic_stroke[actuator_idx].luset_gazebo_pub.publish(msgPub); ///< Publish the actuator strokes (msgPub) to the correct prismatic joints (/cylinderPiston*0_position_controller/command) in the Gazebo simulation
        }
    }
}

std::vector<lusetcontrolnamespace::LusetCollision::contacts> lusetcontrolnamespace::LusetCollision::populateContactStateSubscribers(){

    std::string contact_detect_topic_name; ///< Name of the topic on which to listen for component contacts (e.g. ``/yoke_sensor_state'')
    std::string joint_cmd_topic_name; ///< Name of the topic on which to publish actuator joint commands (e.g. ``/cylinderPiston20_position_controller/command'')
    std::string actuator_str; ///< String for actuator name (e.g. ``T302'')
    lusetcontrolnamespace::LusetCollision::contacts contacts_struct; ///< Declare a struct of type ``contacts''
    std::vector<lusetcontrolnamespace::LusetCollision::contacts> output(120,contacts_struct); ///< Initialize the output vector (which initializes this->luset_contact_sub) with 120 copies of contacts_struct - 100 for the actuators and 20 for the yokes

    int m = 0;
    for(int i = 0; i < this->sides.size(); i++){
        for(int j = 0; j < this->index.size(); j++){
            for(int k = 0; k <= this->layer.size(); k++){
                if(k == this->layer.size()){
                    contact_detect_topic_name = "/" + this->sides[i] + std::to_string(this->index[j]) + "/yoke_sensor_state"; ///< Compose a string of the type /namespace/yoke_sensor_state where ``namespace'' is the yoke name, e.g. ``N2'', ``S3'', etc
                } else {
                    contact_detect_topic_name = "/" + this->sides[i] + std::to_string(this->index[j]) + "/cylinder" + std::to_string(this->layer[k]) + "0_sensor_state"; ///< Compose a string of the type /namespace/cylinder*0_sensor_state where * here corresponds to the layer of the actuator with the same index as the yoke

                    joint_cmd_topic_name = "/" + this->sides[i] + std::to_string(this->index[j]) + "/cylinderPiston" + std::to_string(this->layer[k]) + "0_position_controller/command"; ///< Compose a string of the type /namespace/cylinderPosition*0_position_controller/command where * here corresponds to the layer of the actuator with the same index as the yoke

                    actuator_str = this->sides[i] + std::to_string(this->layer[k]) + "0" + std::to_string(this->index[j]);

                    /**
                     * @brief Add new entry to actuator_topic_stroke map.
                     * Contains:
                     * - topic_name: topic on which to publish actuator joint commands
                     * - luset_gazebo_pub: publisher object corresponding to the topic_name
                     * - actuator_stroke: actuator_stroke to publish to on topic_name (initialized to 0)
                     */
                    this->actuator_topic_stroke.insert(std::make_pair(actuator_str,
                        *(new lusetcontrolnamespace::LusetCollision::actuators(
                            {.topic_name = joint_cmd_topic_name,
                             .luset_gazebo_pub = this->node_handle->advertise<std_msgs::Float64>(joint_cmd_topic_name, 10),
                             .actuator_stroke = 0.0}))));
                }
                /**
                 * @brief Add new entry to output vector.
                 * Contains:
                 * - private_handle: ROS node handle which subscribes to a single contact sensor (contact_detect_topic_name)
                 * - queue: Primary queue serviced by private_handle
                 * - sub_queue: subscription queue for the contact_detect_topic_name on which callbacks are processed
                 * - sub: ROS subscriber object to contact_detect_topic_name
                 * - async_spinner: Asynchronous spinner running on its own thread; processes callbacks found in queue
                 */
                output[m].private_handle = new ros::NodeHandle;
                output[m].queue = new ros::CallbackQueue;
                output[m].sub_queue = new ros::SubscriptionQueue(contact_detect_topic_name, 1000, true);

                output[m].sub = output[m].private_handle->subscribe(contact_detect_topic_name, 1000, &lusetcontrolnamespace::LusetCollision::lusetContactStateCallback, this);

                output[m].private_handle->setCallbackQueue(output[m].queue); ///< Assign queue as the callback queue for the private_handle ROS node handle

                output[m].async_spinner = new ros::AsyncSpinner(0, output[m].queue);

                m++;
            }
        }
    }

    return output;

}

std::map<std::string,std::vector<std::string>> lusetcontrolnamespace::LusetCollision::readValveConfig(){

    /**
     * @brief Read from the parameter server the valve configuration. Note, the user must stop and restart the software if they want to make a change on the parameter server, as this function is only executed once at initialization!
     * 
     */
    std::string ns = "/luset_valve_config/";
    std::string prefix; ///< Valves are named according to their connections to the yokes in the standard configuration, e.g. valve T100 is connected to valves T101, T102, T103, T104, and T105 in the standard configuration, etc.

    std::map<std::string,std::vector<std::string>> output;

    for(int i = 0; i < this->sides.size(); i++){
        for(int j = 0; j < this->index.size(); j++){
            prefix = this->sides[i] + std::to_string(this->index[j]); ///< Name of the valve, e.g. ``T100'', ``B400'', etc
            ros::param::get(ns + prefix + "00", output[prefix + "00"]); ///< Query the valve-actuator configuration from the parameter server. This is defined in luset_valve_config_*.yaml.
        }
    }

    return output;

}

void lusetcontrolnamespace::LusetCollision::spinMultithreadSpinners(){

    /**
     * @brief Spin multithread Async spinners on each thread
     */
    for(int i = 0; i < this->luset_contact_sub.size(); i++){
        this->luset_contact_sub[i].async_spinner->start(); ///< Spin
        this->luset_contact_sub[i].queue->callOne(); ///< Process only the oldest callback in the queue
    }
}

lusetcontrolnamespace::LusetCollision::~LusetCollision(){

    /**
     * @brief Destroy all the variables that were created using the keyword ``new''. When we use this keyword, we take responsibility from the compiler for managing this memory ourselves.
     */
    for(int i = 0; i < this->luset_contact_sub.size(); i++){
        delete this->luset_contact_sub[i].async_spinner;
        delete this->luset_contact_sub[i].sub_queue;
        delete this->luset_contact_sub[i].queue;
        delete this->luset_contact_sub[i].private_handle;
    }
    for(auto it = this->actuator_topic_stroke.begin(); it != this->actuator_topic_stroke.end(); it++){
        this->actuator_topic_stroke.erase(it); ///< Delete actuator_topic_stroke entry at the given iterator
    }
}