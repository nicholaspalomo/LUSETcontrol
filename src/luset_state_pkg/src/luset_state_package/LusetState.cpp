/**
 * @file LusetState.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the LusetState class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "LusetState.hpp"

lusetstatenamespace::LusetState::LusetState()
    : CylinderDirection(100,std::vector<double>(3,0.0)) ///< In case interested, more details about initialization of a 2D vector in a C++ class can be found at https://stackoverflow.com/questions/5761254/creating-2-dimensional-vector-in-class-c
{
}

void lusetstatenamespace::LusetState::update(const indel_update_pkg::LusetStateArray::ConstPtr& msg){
    
    /**
     * @brief Populate the CylinderPosition and LoadPinForces members
     * 
     */
    for(int i = 0; i < 100; i++){
        this->CylinderPosition.at(i) = msg->ArrayValue.at(1+i);
        this->LoadPinForces.at(i) = msg->ArrayValue.at(101+i);
    }

    /**
     * @brief Populate the PressureA, PressureB, AngleXZ, AngleYZ members
     * 
     */
    for(int i = 0; i < 20; i++){
        this->PressureA.at(i) = msg->ArrayValue.at(201+i);
        this->PressureB.at(i) = msg->ArrayValue.at(221+i);
        this->AngleXZ.at(i) = msg->ArrayValue.at(241+i);
        this->AngleYZ.at(i) = msg->ArrayValue.at(261+i);
    }
    int nBase = 280;

    /**
     * @brief Populate the translation, Euler angles members for the bottom yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->BY.at(kYoke).TX = msg->ArrayValue.at(nBase+1);
        this->BY.at(kYoke).TY = msg->ArrayValue.at(nBase+2);
        this->BY.at(kYoke).TZ = msg->ArrayValue.at(nBase+3);
        this->BY.at(kYoke).RX = -msg->ArrayValue.at(nBase+4);
        this->BY.at(kYoke).RY = msg->ArrayValue.at(nBase+5);
        this->BY.at(kYoke).RZ = -msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the translation, Euler angles members for the north yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->NY.at(kYoke).TX = msg->ArrayValue.at(nBase+1);
        this->NY.at(kYoke).TY = msg->ArrayValue.at(nBase+2);
        this->NY.at(kYoke).TZ = msg->ArrayValue.at(nBase+3);
        this->NY.at(kYoke).RX = -msg->ArrayValue.at(nBase+4);
        this->NY.at(kYoke).RY = msg->ArrayValue.at(nBase+5);
        this->NY.at(kYoke).RZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the translation, Euler angles members for the top yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->TY.at(kYoke).TX = msg->ArrayValue.at(nBase+1);
        this->TY.at(kYoke).TY = msg->ArrayValue.at(nBase+2);
        this->TY.at(kYoke).TZ = msg->ArrayValue.at(nBase+3);
        this->TY.at(kYoke).RX = msg->ArrayValue.at(nBase+4);
        this->TY.at(kYoke).RY = msg->ArrayValue.at(nBase+5);
        this->TY.at(kYoke).RZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the translation, Euler angles members for the south yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->SY.at(kYoke).TX = msg->ArrayValue.at(nBase+1);
        this->SY.at(kYoke).TY = msg->ArrayValue.at(nBase+2);
        this->SY.at(kYoke).TZ = msg->ArrayValue.at(nBase+3);
        this->SY.at(kYoke).RX = msg->ArrayValue.at(nBase+4);
        this->SY.at(kYoke).RY = msg->ArrayValue.at(nBase+5);
        this->SY.at(kYoke).RZ = -msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the force, moment members for the bottom yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->BY.at(kYoke).FX = msg->ArrayValue.at(nBase+1);
        this->BY.at(kYoke).FY = msg->ArrayValue.at(nBase+2);
        this->BY.at(kYoke).FZ = msg->ArrayValue.at(nBase+3);
        this->BY.at(kYoke).MX = msg->ArrayValue.at(nBase+4);
        this->BY.at(kYoke).MY = msg->ArrayValue.at(nBase+5);
        this->BY.at(kYoke).MZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the force, moment members for the north yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->NY.at(kYoke).FX = msg->ArrayValue.at(nBase+1);
        this->NY.at(kYoke).FY = msg->ArrayValue.at(nBase+2);
        this->NY.at(kYoke).FZ = msg->ArrayValue.at(nBase+3);
        this->NY.at(kYoke).MX = msg->ArrayValue.at(nBase+4);
        this->NY.at(kYoke).MY = msg->ArrayValue.at(nBase+5);
        this->NY.at(kYoke).MZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the force, moment members for the top yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->TY.at(kYoke).FX = msg->ArrayValue.at(nBase+1);
        this->TY.at(kYoke).FY = msg->ArrayValue.at(nBase+2);
        this->TY.at(kYoke).FZ = msg->ArrayValue.at(nBase+3);
        this->TY.at(kYoke).MX = msg->ArrayValue.at(nBase+4);
        this->TY.at(kYoke).MY = msg->ArrayValue.at(nBase+5);
        this->TY.at(kYoke).MZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the force, moment members for the south yoke. Yoke kinematics for the rotations changed to local coordinates yokes.
     * 
     */
    for(int kYoke = 0; kYoke < 5; kYoke++){
        this->SY.at(kYoke).FX = msg->ArrayValue.at(nBase+1);
        this->SY.at(kYoke).FY = msg->ArrayValue.at(nBase+2);
        this->SY.at(kYoke).FZ = msg->ArrayValue.at(nBase+3);
        this->SY.at(kYoke).MX = msg->ArrayValue.at(nBase+4);
        this->SY.at(kYoke).MY = msg->ArrayValue.at(nBase+5);
        this->SY.at(kYoke).MZ = msg->ArrayValue.at(nBase+6);
        nBase += 6;
    }

    /**
     * @brief Populate the CylinderDirection member for each actuator
     * 
     */
    for(int iCyl = 0; iCyl < 100; iCyl++){
        for(int iDir = 0; iDir < 3; iDir++){
            this->CylinderDirection.at(iCyl).at(iDir) = msg->ArrayValue.at(nBase+3*(iCyl-1)+iDir);
        }
    }
    nBase += 300;

    /**
     * @brief Populate the AxisPositionIst (actual) member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->AxisPositionIst.at(iAxis) = msg->ArrayValue.at(nBase+iAxis);
    }
    nBase += 20;

    /**
     * @brief Populate the AxisPositionSetPoint member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->AxisPositionSetPoint.at(iAxis) = msg->ArrayValue.at(nBase+iAxis); 
    }
    nBase += 20;

    /**
     * @brief Populate the AxisForceIst member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->AxisForceIst.at(iAxis) = msg->ArrayValue.at(nBase+iAxis); 
    }
    nBase += 20;

    /**
     * @brief Populate the AxisForceSetPoint member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->AxisForceSetPoint.at(iAxis) = msg->ArrayValue.at(nBase+iAxis); 
    }
    nBase += 20;

    /**
     * @brief Populate the VCCurrentIstValue member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->VCCurrentIstValue.at(iAxis) = msg->ArrayValue.at(nBase+iAxis); 
    }
    nBase += 20;

    /**
     * @brief Populate the VCSetPoint member for each axis/valve
     * 
     */
    for(int iAxis = 0; iAxis < 20; iAxis++){
        this->VCSetPoint.at(iAxis) = msg->ArrayValue.at(nBase+iAxis); 
    }
    nBase += 20;

    /**
     * @brief Populate the ADC_From328To335 member
     * 
     */
    for(int iADC = 0; iADC < 8; iADC++){
        this->ADC_From328To335.at(iADC) = msg->ArrayValue.at(nBase+iADC); 
    }
    nBase += 8;
}