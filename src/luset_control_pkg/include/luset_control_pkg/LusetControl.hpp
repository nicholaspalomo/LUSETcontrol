/**
 * @file IndelUpdate.hpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the header file for the LusetControl and LusetCollision classes. The LusetCollision class is responsible for subscribing to the /LusetState topic and for publishing the actuator strokes to the correct actuators in the Gazebo simulation. It also publishes a message to the /LusetContacts topic if a collision between two components in the model is detected. The LusetControl class is not yet implemented, but in the future, it will handle the control algorithm (LQR, PI, MPC, etc.) that computes the axis/valve displacements to send to the low-level controller, which interfaces with the IndelUpdate class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef LUSET_CONTROL_PKG_LUSET_CONTROL_H_
#define LUSET_CONTROL_PKG_LUSET_CONTROL_H_

#include<stdio.h> ///< Standard input-output header
#include<string.h> ///< Perform string manipulation operations like strlen and strcpy
#include<stdlib.h> ///< Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc().
#include<math.h> ///< Perform mathematical operations like sqrt() and pow(). To obtain the square root and the power of a number respectively.
#include<ctype.h> ///< Perform character type functions like isaplha() and isdigit(). To find whether the given character is an alphabet or a digit respectively.
#include<time.h> ///< Perform functions related to date and time like setdate() and getdate(). To modify the system date and get the CPU time respectively.
#include <vector> // To be able to use vectors in C++
#include<iostream> ///< Used as a stream of Input and Output.
// #include<Eigen/Dense> ///< Recommended to install Eigen in root of catkin workspace

/**
 * @brief ROS API headers
 */
#include "ros/ros.h" ///< ROS API header
#include <ros/callback_queue.h> //< For callback queue functionality
#include <ros/subscription_queue.h> //< For setting subsciption queues
#include <ros/spinner.h> //< For access to multi-thread spinners

/**
 * @brief ROS-Gazebo message definitions
 */
#include <sensor_msgs/JointState.h> ///< JointState sensor message definition
#include <gazebo_msgs/ContactsState.h> ///< ContactsState sensor message definition (for determining if any actuators or yokes come in contact)
#include <gazebo_msgs/ContactState.h> ///< ContactState sensor message definition (for determining if any actuators or yokes come in contact)
#include <std_msgs/Float64.h> ///< Standard ROS definition for a message containing a single float

/**
 * @brief Custom message definitions
 */
#include "luset_state_pkg/ActuatorOrientation.h" ///< Custom message header file containing orientation vector for a cylinder
#include "luset_state_pkg/DisplacementForceStruct.h" ///< Custom message header containing translation, rotation, force, and moment measurements for each yoke
#include "luset_state_pkg/LusetState.h" ///< Custom message header containing the definition of the LusetState structure

namespace lusetcontrolnamespace{
    /**
     * @class LusetControl
     * @todo This class is responsible for computing control actions as axis/valve displacements and for passing them to the IndelUpdate node. This class has not yet been implemented. Several things must be included in this or other class definitions, including:
     * - The A matrix needs to be specified somewhere - probably as arrays on the parameter server (i.e. in a YAML file)
     * - Need to also specify the relationships between the information coming from LUSET State and the control variable definitons. From the current values of the control variables, use the A-matrix to compute the current actuator displacements
     * - Have a CMake flag that only includes the proper header corresponding to the test the user wishes to run such that the correct parameters are loaded to the ROS parameter server at runtime
     * - Use some sort of optimization to generate a trajectory; if you can't finish this, have it generate linear trajectories as interpolations and have it pause issuing new commands if certain control variables are lagging
     * - Somewhere the location and orientation of the COM of the yokes should be computed and published.
     */
    class LusetControl{
        public:

            /**
             * @brief Construct a new Luset Control object
             * 
             */
            LusetControl();

        private:

    };

    /**
     * @class LusetCollision 
     * @brief This class subscribes to /LusetState and publishes the cylinder strokes to the correct cylinders in the Gazebo simulation using information from the parameter server regarding which actuators are connected to the corresponding axes/valves. The values on the parameter server are loaded from /luset_control_pkg/config/luset_valve_config_standard.yaml. This class also subscribes to the contact sensors in Gazebo publishing on the sensor_state topics and only publishes a message to /LusetContacts if two components actually collide in the simulation. 
     */
    class LusetCollision{
        public:
            /**
             * @brief Construct a new Luset Collision object
             * @param[in]   handle   ros::NodeHandle& reference to the handle for the /LusetControl node
             */
            LusetCollision(ros::NodeHandle& handle);

            /**
             * @brief Destroy the Luset Collision object. Deallocates all objects instantiated via the keyword ``new'' in C++
             */
            ~LusetCollision();

            /**
             * @brief This method starts the Async spinner objects and executes one callback from their queues.
             * @param[in]   void    Method takes no inputs
             * @return  void    Method returns void
             */
            void spinMultithreadSpinners();

        private:

            friend class LusetControl; ///< LusetControl may access the private members of LusetCollision (but not vice versa)

            const std::vector<std::string> sides = {"T", "N", "B", "S"}; ///< Define a vector of strings representing the four sides of LUSET - top, north, bottom, south
            const std::vector<int> index = {1, 2, 3, 4, 5}; ///< Define a vector of integers representing the yoke indices
            const std::vector<int> layer = {1, 2, 3, 4, 5}; ///< Define a vector of integers representing the actuator layers

            ros::NodeHandle* node_handle; ///< Pointer to the ROS node handle for /LusetControl 

            typedef struct{
                std::string topic_name; ///< Name of the topic on which displacement commands are to be published for the prismatic joint between each piston and actuator connected to a yoke 
                ros::Publisher luset_gazebo_pub; ///< Publisher object for the topic given in the actuators.topic_name field
                double actuator_stroke; ///< Actuator stroke to publish to the piston-cylinder prismatic joint
            }actuators;

            std::map<std::string,actuators> actuator_topic_stroke; ///< Map containing the actuator name as the key and an actuators struct as the value

            typedef struct{
                ros::NodeHandle* private_handle; ///< Node on a separate thread for each contact sensor (120 in total)
                ros::CallbackQueue* queue; ///< Queue to which callbacks for the given contact sensor whill be appended
                ros::SubscriptionQueue* sub_queue; ///< Subscription queue
                ros::AsyncSpinner* async_spinner; ///< Asynchronous spinner for multithread applications in ROS; spinner assigned to spin callbacks contained in contacts.queue
                ros::Subscriber sub; ///< Subscriber object to the sensor_state topic
            }contacts;

            std::vector<contacts> luset_contact_sub; ///< Vector of Async spinners and of subscribers to collision messages

            std::map<std::string,std::vector<std::string>> valve_config; ///< Stores the configuration denoting which axes/valves (keys) and connected to which actuators (values)

            ros::Publisher luset_contact_pub; ///< Publisher to /LusetContacts
            ros::Subscriber luset_state_sub; ///< Subscriber to /LusetState messages

            /**
             * @brief This method contains the callback for subscribers to the contact sensors. Checks to see if the contact message that has arrived in the queue is non-empty and only publishes it to /LusetContacts if this is the case.
             * @param[in]   msgSub     const gazebo_msgs::ContactsStateConstPtr& Reference to a Gazebo ContactsState message constant pointer
             * @return  void    Method returns void
             */
            void lusetContactStateCallback(const gazebo_msgs::ContactsStateConstPtr& msgSub);

            /**
             * @brief This method contains the callback for the subscriber to /LusetState messages. It checks the CylinderPosition field of the message and publishes it to the correct piston-cylinder prismatic joint in the Gazebo simulation.
             * @param[in]   msgSub  const luset_state_pkg::LusetState::ConstPtr& Reference to a LusetState message constant pointer 
             * return   void    Method returns void
             */
            void lusetStateMsgCallback(const luset_state_pkg::LusetState::ConstPtr& msgSub);

            /**
             * @brief This method populates a vector of the subscribers that subscribe to the contact sensor topics. It also populates actuator_stroke_topic as a map of publishers that will publish to the correct prismatic joint(s) in the Gazebo simulation.
             * @return std::vector<contacts> 
             */
            std::vector<contacts> populateContactStateSubscribers();

            /**
             * @brief This method gets the valve-actuator configuration from the parameter server
             * @param[in]   void    Method does not take any input arguments
             * @return std::map<std::string,std::vector<std::string>> Map of the valve-actuator configuration
             */
            std::map<std::string,std::vector<std::string>> readValveConfig();
    };

}


#endif // LUSET_CONTROL_PKG_LUSET_CONTROL_H_