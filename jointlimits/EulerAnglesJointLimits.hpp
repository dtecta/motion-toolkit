/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef IK_EULERANGLESJOINTLIMITS_HPP
#define IK_EULERANGLESJOINTLIMITS_HPP

#include "JointLimits.hpp"

namespace ik
{
    class EulerAnglesJointLimits
        : public JointLimits
    {
    public:
        EulerAnglesJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz);

        void setLocalJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz);


        // JointLimits overrides
        virtual void bound(DualQuaternion& relPose) const OVERRIDE;

    protected:
        Interval mLimits[3];   
    };

   
}

#endif
