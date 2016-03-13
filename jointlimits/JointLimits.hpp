/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef IK_JOINTLIMITS_HPP
#define IK_JOINTLIMITS_HPP

#include "Types.hpp"
/**
 * \mainpage
 * 
 * This is sample code accompanying Chapter 10 "Rotational Joint Limits in Quaternion Space"
 * of "Game Engine Gems 3". The code could be used inside a cyclic coordinate descent CCD IK solver. 
 * In its current form it uses Google Test to demonstrate its functionality.
 * The base class for all types of joint limits is \ref JointLimits.hpp
 *
 */

namespace ik
{
    /**
     * This class serves as an abstract base class for differnt types of joint limits used in the IK solver.
     */
    
    class JointLimits
    {
    public:
        virtual ~JointLimits() {}

        /** 
         * Clamps a relative pose to the closest admissible pose of this joint.
         * @param relPose            relative pose between a bone and its parent 
         */
        virtual void bound(DualQuaternion& relPose) const = 0;  
    };
}

#endif
