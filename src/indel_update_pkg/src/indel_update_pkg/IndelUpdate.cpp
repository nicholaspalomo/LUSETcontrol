/**
 * @file IndelUpdate.cpp
 * @author Nicholas José Palomo (npalomo@student.ethz.ch)
 * @brief This is the source code for the IndelUpdate class. See https://google.github.io/styleguide/cppguide.html for Google Style Guide for C++.
 * @version 0.1
 * @date 2020-02-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "IndelUpdate.hpp"

void indelupdatenamespace::IndelUpdate::update(void){

    /** 
     * Call the Indel functions to populate ArrayValue
     * ulong is the variable given to the indel error messages, specified in errinco.h; ulong = 0 corresponds to no error
     * Comment out up to the lines after the memcpy() for routing simulation data to Gazebo model
     */
    // uint32_t ulong = GetVariable(this->device, this->AddressString, &this->value, 0); ///< Get the address of the data from the low-level controller

    // if(ulong == 0){
    //     uint32 BufferSize = 1000; ///< Specify a large buffer size to store data from low-level controller
    //     uint64 result[BufferSize]; ///< Create an array to hold the information from the data stream
    //     // Cast the address to a 32-bit value
    //     uint32_t addr = (uint32_t)this->value; 

    //     ulong = GetBlock64(this->device, addr, result, BufferSize); ///< Populate result[] array given the supplied device and address member variables
    //     if(ulong == 0){
    //         std::copy(result, result + BufferSize, this->ArrayValue.begin()); ///< Copy the result[] array to the ArrayValue[] member variable
    //     }
    // }

    /**
     * For simulation environment: populate the ArrayValue[] member variable with realistic values.
     */
   int m = 1;
   for(int i = 0; i < 1000; i++){
        if(m < 1000 - 5){
            this->ArrayValue[m] = 0.3; ///< Set the maximum cylinder stroke to 0.3 m, for example (can be changed via the MAX_CYLINDER_STROKE property in the geometry xacro file)
            m += 5;
        }
    }

}