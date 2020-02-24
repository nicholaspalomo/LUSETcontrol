/**
 * @file LusetStateSubPub.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the subscriber/publisher/callback LusetStateSubPub class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "LusetState.hpp"

lusetstatepubsubnamespace::LusetStatePubSub::LusetStatePubSub(ros::NodeHandle& handle) :
node_handle(&handle),
sub(this->node_handle->subscribe("IndelUpdate", 10, &lusetstatepubsubnamespace::LusetStatePubSub::lusetStateArrayParsingCallback, this)), ///< Initialize subscriber member to /IndelUpdate topic
pub(this->node_handle->advertise<luset_state_pkg::LusetState>("LusetState", 10)) ///< Initialize publisher member to /LusetState topic
{
}

void lusetstatepubsubnamespace::LusetStatePubSub::lusetStateArrayParsingCallback(const indel_update_pkg::LusetStateArray::ConstPtr& msgSub){
    
    lusetstatenamespace::LusetState luset_state_obj; ///< Instantiate a LusetState object

    luset_state_obj.update(msgSub); ///< Fill the member variables of the LusetState object with the contents of msgSub, which has the low-level controller measurements published on the /IndelUpdate topic

    luset_state_pkg::LusetState msgPub; ///< Declare a message object to publish to the /LusetState topic

    /**
     * @brief Populate the message contents with the data from the member variables of the LusetState object
     * 
     */
    for(int i = 0; i < 100; i++){
        msgPub.CylinderPosition.at(i) = luset_state_obj.CylinderPosition.at(i);
        msgPub.LoadPinForces.at(i) = luset_state_obj.LoadPinForces.at(i);
    }

    for(int i = 0; i < 20; i++){
        msgPub.PressureA.at(i) = luset_state_obj.PressureA.at(i);
        msgPub.PressureB.at(i) = luset_state_obj.PressureB.at(i);
        msgPub.AngleXZ.at(i) = luset_state_obj.AngleXZ.at(i);
        msgPub.AngleYZ.at(i) = luset_state_obj.AngleYZ.at(i);
        msgPub.AxisPositionIst.at(i) = luset_state_obj.AxisPositionIst.at(i);
        msgPub.AxisPositionSetPoint.at(i) = luset_state_obj.AxisPositionSetPoint.at(i);
        msgPub.AxisForceIst.at(i) = luset_state_obj.AxisForceIst.at(i);
        msgPub.AxisForceSetPoint.at(i) = luset_state_obj.AxisForceSetPoint.at(i);
        msgPub.VCSetPoint.at(i) = luset_state_obj.VCSetPoint.at(i);
        msgPub.VCCurrentIstValue.at(i) = luset_state_obj.VCCurrentIstValue.at(i);
    }

    for(int i = 0; i < 8; i++){
        msgPub.ADC_From328To335.at(i) = luset_state_obj.ADC_From328To335.at(i);
    }

   for(int i = 0; i < 100; i++){
        for(int j = 0; j < 3; j++){
            msgPub.CylinderDirection.at(i).ActuatorOrientation.at(j) = luset_state_obj.CylinderDirection.at(i).at(j);
        }
    }

    for(int i = 0; i < 5; i++){
        /**
         * @brief Bottom yokes
         * 
         */
        msgPub.DisplacementForceB.at(i).TX = luset_state_obj.BY.at(i).TX;
        msgPub.DisplacementForceB.at(i).TY = luset_state_obj.BY.at(i).TY;
        msgPub.DisplacementForceB.at(i).TZ = luset_state_obj.BY.at(i).TZ;
        msgPub.DisplacementForceB.at(i).RX = luset_state_obj.BY.at(i).RX;
        msgPub.DisplacementForceB.at(i).RY = luset_state_obj.BY.at(i).RY;
        msgPub.DisplacementForceB.at(i).RZ = luset_state_obj.BY.at(i).RZ;
        msgPub.DisplacementForceB.at(i).FX = luset_state_obj.BY.at(i).FX;
        msgPub.DisplacementForceB.at(i).FY = luset_state_obj.BY.at(i).FY;
        msgPub.DisplacementForceB.at(i).FZ = luset_state_obj.BY.at(i).FZ;
        msgPub.DisplacementForceB.at(i).MX = luset_state_obj.BY.at(i).MX;
        msgPub.DisplacementForceB.at(i).MY = luset_state_obj.BY.at(i).MY;
        msgPub.DisplacementForceB.at(i).MZ = luset_state_obj.BY.at(i).MZ;

        /**
         * @brief North yokes
         * 
         */
        msgPub.DisplacementForceN.at(i).TX = luset_state_obj.NY.at(i).TX;
        msgPub.DisplacementForceN.at(i).TY = luset_state_obj.NY.at(i).TY;
        msgPub.DisplacementForceN.at(i).TZ = luset_state_obj.NY.at(i).TZ;
        msgPub.DisplacementForceN.at(i).RX = luset_state_obj.NY.at(i).RX;
        msgPub.DisplacementForceN.at(i).RY = luset_state_obj.NY.at(i).RY;
        msgPub.DisplacementForceN.at(i).RZ = luset_state_obj.NY.at(i).RZ;
        msgPub.DisplacementForceN.at(i).FX = luset_state_obj.NY.at(i).FX;
        msgPub.DisplacementForceN.at(i).FY = luset_state_obj.NY.at(i).FY;
        msgPub.DisplacementForceN.at(i).FZ = luset_state_obj.NY.at(i).FZ;
        msgPub.DisplacementForceN.at(i).MX = luset_state_obj.NY.at(i).MX;
        msgPub.DisplacementForceN.at(i).MY = luset_state_obj.NY.at(i).MY;
        msgPub.DisplacementForceN.at(i).MZ = luset_state_obj.NY.at(i).MZ;

        /**
         * @brief Top yokes
         * 
         */
        msgPub.DisplacementForceT.at(i).TX = luset_state_obj.TY.at(i).TX;
        msgPub.DisplacementForceT.at(i).TY = luset_state_obj.TY.at(i).TY;
        msgPub.DisplacementForceT.at(i).TZ = luset_state_obj.TY.at(i).TZ;
        msgPub.DisplacementForceT.at(i).RX = luset_state_obj.TY.at(i).RX;
        msgPub.DisplacementForceT.at(i).RY = luset_state_obj.TY.at(i).RY;
        msgPub.DisplacementForceT.at(i).RZ = luset_state_obj.TY.at(i).RZ;
        msgPub.DisplacementForceT.at(i).FX = luset_state_obj.TY.at(i).FX;
        msgPub.DisplacementForceT.at(i).FY = luset_state_obj.TY.at(i).FY;
        msgPub.DisplacementForceT.at(i).FZ = luset_state_obj.TY.at(i).FZ;
        msgPub.DisplacementForceT.at(i).MX = luset_state_obj.TY.at(i).MX;
        msgPub.DisplacementForceT.at(i).MY = luset_state_obj.TY.at(i).MY;
        msgPub.DisplacementForceT.at(i).MZ = luset_state_obj.TY.at(i).MZ;

        /**
         * @brief South yokes
         * 
         */
        msgPub.DisplacementForceS.at(i).TX = luset_state_obj.SY.at(i).TX;
        msgPub.DisplacementForceS.at(i).TY = luset_state_obj.SY.at(i).TY;
        msgPub.DisplacementForceS.at(i).TZ = luset_state_obj.SY.at(i).TZ;
        msgPub.DisplacementForceS.at(i).RX = luset_state_obj.SY.at(i).RX;
        msgPub.DisplacementForceS.at(i).RY = luset_state_obj.SY.at(i).RY;
        msgPub.DisplacementForceS.at(i).RZ = luset_state_obj.SY.at(i).RZ;
        msgPub.DisplacementForceS.at(i).FX = luset_state_obj.SY.at(i).FX;
        msgPub.DisplacementForceS.at(i).FY = luset_state_obj.SY.at(i).FY;
        msgPub.DisplacementForceS.at(i).FZ = luset_state_obj.SY.at(i).FZ;
        msgPub.DisplacementForceS.at(i).MX = luset_state_obj.SY.at(i).MX;
        msgPub.DisplacementForceS.at(i).MY = luset_state_obj.SY.at(i).MY;
        msgPub.DisplacementForceS.at(i).MZ = luset_state_obj.SY.at(i).MZ;
    }

    this->pub.publish(msgPub); ///< Publish the message to the /LusetState topic
}